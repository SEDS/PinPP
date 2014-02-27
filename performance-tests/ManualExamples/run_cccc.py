#!/usr/bin/python3

# Executes CCCC and gathers results into a csv

import os
import argparse
import sys
import subprocess
import csv
import xml.etree.ElementTree

#
# Parse args
#
def parse_args ():
  parser = argparse.ArgumentParser (description='Gathers performance metrics of pin++ vs native pin')

  parser.add_argument ('--outfile', default='results.csv', type=str, help='Output file. Defaults to results.csv')
  parser.add_argument ('--directory', default=None, type=str, nargs='+', help='Directories to search for cpp files to run through cccc (recursive)')

  return parser.parse_args ()

#
# Find files
#
def find_files (path):
  pintools = []

  for root, dirs, files in os.walk (path):
    for file in files:
      if file.endswith ('.cpp'):
        pintools.append (os.path.join (root, file))

    for dir in dirs:
      pintools.extend (find_files (dir))

  return pintools

#
# Run cccc
#
def run_cccc (cpp_file, xml_outfile):
  # Build the command
  # Example: cccc --xml_outfile=results.xml foo.cpp
  cmd = ['cccc',
         '--xml_outfile=%s' % xml_outfile,
         cpp_file]

  # DEBUG: Check the command
  #print (repr (cmd))

  # Run the command
  print ('INFO: Running cccc against <%s>' % cpp_file)
  subprocess.call (cmd)

#
# Parse xml
#
def parse_xml (filename, translation, results):
  tree = xml.etree.ElementTree.parse (filename)
  root = tree.getroot ()

  # All elements we are looking for are in the project summary section
  proj_summary = root.find ('project_summary')

  for metric_label in translation.values ():
    value = proj_summary.find (metric_label).get ('value')
    if ('-' in value) or ('*' in value):
      value = float ('nan')
    results.append (value)

  return results

#
# Main entry point for the application
#
def main ():
  # Parse the arguments
  args = parse_args ()

  # Check for binaries
  if not args.directory:
    print ("ERROR: No directories specified")
    sys.exit (1)

  cpp_files = []

  # Find all the cpp files
  for directory in args.directory: 
    print ('INFO: Finding cpp files in <%s>' % (directory))
    cpp_files.extend (find_files (directory))

  if not cpp_files:
    print ("ERROR: No cpp files found in the provided directories")
    sys.exit (1)

  # Define a map between csv labels and xml element names
  cccc_map = {'Modules': 'number_of_modules',
              'Lines of Code': 'lines_of_code',
              'Lines of Code per Module': 'lines_of_code_per_module',
              'Cyclomatic Complexity': 'McCabes_cyclomatic_complexity',
              'Cyclomatic Complexity per Module': 'McCabes_cyclomatic_complexity_per_module',
              'Lines of Comments': 'lines_of_comment',
              'Lines of Comments per Module': 'lines_of_comment_per_module',
              'Cyclomatic Complexity per Line of Comment': 'McCabes_cyclomatic_complexity_per_line_of_comment',
              'Information Flow (inclusive)': 'IF4',
              'Information Flow (inclusive) per Module': 'IF4_per_module',
              'Information Flow (visibile)': 'IF4_visible',
              'Information Flow (visibile) per Module': 'IF4_visible_per_module',
              'Information Flow (concrete)': 'IF4_concrete',
              # 'Information Flow (concrete) per Module' : 'IF4_concrete', # Invalid XML structure, duplicate element name
              'Rejected Lines of Code': 'rejected_lines_of_code'
             }

  # Open the file and write the header
  outfile = open (args.outfile, 'w')
  writer = csv.writer (outfile)
  header = ['Filename']
  for field_header in cccc_map.keys ():
    header.append (field_header)
  writer.writerow (header)

  # Execute cccc on each file
  for target in cpp_files:
    cccc_xml = 'cccc.xml'
    run_cccc (target, cccc_xml)
    results = [target]
    parse_xml (cccc_xml, cccc_map, results)
    writer.writerow (results)

main ()
