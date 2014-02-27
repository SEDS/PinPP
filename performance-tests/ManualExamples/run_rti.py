#!/usr/bin/python3

# Times executions of pin++ vs native pin and outputs in a pivot table CSV

import time
import os
import argparse
import sys
import subprocess
import csv
import re

#
# Parse args
#
def parse_args ():
  parser = argparse.ArgumentParser (description='Gathers performance metrics of pin++ vs native pin')

  parser.add_argument ('--outfile', default='results.csv', type=str, help='Output file. Defaults to results.csv')
  parser.add_argument ('--pinppdir', default=os.environ['OASIS_ROOT'] + '/examples/pintools', type=str, help='Pin++ pintool directory. Defaults to $OASIS_ROOT/examples/pintools')
  parser.add_argument ('--pindir', default=os.environ['PIN_ROOT'] + '/source/tools', type=str, help='Native pintool directory.  Defaults to $PIN_ROOT/source/tools')
  parser.add_argument ('--latency', default=False, action='store_true', help='Flag to run the latency performance test')
  parser.add_argument ('--throughput', default=False, action='store_true', help='Flag to run the throughput performance test')
  parser.add_argument ('--arch', default=None, type=str, help='Architecture used to build the tests (rtiddsgen)')
  parser.add_argument ('--iterations', default=10, type=int, help='Number of iterations to time for each pintool')

  return parser.parse_args ()

#
# Find pintools
#
def find_pintools (path):
  pintools = []

  for root, dirs, files in os.walk (path):
    for file in files:
      if file.endswith ('.so') and (os.name == 'posix'):
        pintools.append (os.path.join (root, file))
      elif (os.name == 'nt') and file.endswith ('.dll'):
        pintools.append (os.path.join (root, file))
      elif (os.name == 'mac') and file.endswith ('.dylib'):
        pintools.append (os.path.join (root, file))

    for dir in dirs:
      pintools.extend (find_pintools (dir))

  return pintools

#
# Remove paths
#
def remove_paths (list):
  results = []
  for item in list:
    results.append (os.path.split (item)[-1])
  return results

#
# Match pintools
#
def match_pintools (native, pinpp):
  # Native format: [path]/inscount0.so
  # Pin++ format: [path]/libinscount0.so
  results = []

  # Full paths are in the provided lists, let's remove them
  pruned_native = remove_paths (native)
  pruned_pinpp = remove_paths (pinpp)

  # NOTE: This assumes there aren't two pintools with the same name in
  # different paths.
  for native_tool in pruned_native:
    search = 'lib' + native_tool
    if search in pruned_pinpp:
      # Assumes the pruned lists have matching indexes to the provided lists
      results.append ([native [pruned_native.index (native_tool)],
                       pinpp [pruned_pinpp.index (search)]])

  return results

#
# Run publisher
#
def run_pub (pintool, command):
  cmd = ' '.join ([os.path.join (os.environ['PIN_ROOT'], 'pin'),
                  '-t',
                  pintool,
                  '--',
                  command])

  # DEBUG: Check the command
  #print (repr (cmd))

  # Run the command
  # Had to use shell=True for trailing arguments (i.e. '1>/dev/null &2>1')
  return subprocess.Popen (cmd, shell=True, stdout=subprocess.PIPE)

#
# Run subscriber
#
def run_sub (pintool, command):
  # Build the command
  # Example: $PIN_ROOT/pin -t pintool.so -- ls
  cmd = ' '.join ([os.path.join (os.environ['PIN_ROOT'], 'pin'),
                  '-t',
                  pintool,
                  '--',
                  command])

  # DEBUG: Check the command
  #print (repr (cmd))

  # Run the command
  # Had to use shell=True for trailing arguments (i.e. '1>/dev/null &2>1')
  subprocess.call (cmd, shell=True)

#
# Parse the provided output from the publisher to get the average execution time
#
def get_time (output, regex):
  # DEBUG: Check the output
  #print (output)
  results = []

  for line in output.splitlines ():
    match = regex.match (line)
    if match:
      results.append (float (match.group (1)))

  # Average all results
  return float (sum (results))/len (results) if len (results) > 0 else float ('nan')

#
# Main entry point for the application
#
def main ():
  # Parse the arguments
  args = parse_args ()

  # Check for pub and sub commands
  if (not args.latency and not args.throughput):
    print ("Error: No performance test provided, must set --latency or --throughput")
    sys.exit (1)

  # Check for arch
  if (not args.arch):
    print ("Error: --arch required")
    sys.exit (1)

  # Build the commands to run
  commands = []
  rti_dir = os.path.join (os.environ['NDDSHOME'], 'example', 'CPP', 'performance')

  if (args.latency):
    bins = (os.path.join (rti_dir, 'latency', 'objs', args.arch,
            'Latency_publisher -domainId 88 -nic 127.0.0.1 -transport 1 -peer 127.0.0.1  -subscribers 1 -numIter 10000 -minSize 1024 -maxSize 1024 2>/dev/null'),
            os.path.join (rti_dir, 'latency', 'objs', args.arch,
            'Latency_subscriber -domainId 88 -cookie 1 -nic 127.0.0.1 -transport 1 -peer 127.0.0.1 1>/dev/null 2>&1'),
            re.compile ('\s*\d+,\s*\d+\.\d,\s*(\d+\.\d)'),
            'latency')
    commands.append (bins)

  if (args.throughput):
    bins = (os.path.join (rti_dir, 'throughput', 'objs', args.arch,
            'Throughput_publisher -domainId 88 -nic 127.0.0.1 -transport 1 -peer 127.0.0.1  -subscribers 1 -duration 30 -size 1024 -demand 5000:1000:5000 2>/dev/null'),
            os.path.join (rti_dir, 'throughput', 'objs', args.arch,
            'Throughput_subscriber -domainId 88 -participantId 1 -nic 127.0.0.1 -transport 1 -peer 127.0.0.1 1>/dev/null 2>&1'),
            re.compile ('\s*\d+,\s*\d+,\s*\d+,\s*(\d+\.\d)'),
            'throughput')
    commands.append (bins)

  # Find all the pintools which have been compiled in the pin directory
  print ('INFO: Finding native pintools in <%s>' % (args.pindir))
  native_pintools = find_pintools (args.pindir)

  # Find all the pintools which have been compiled in the pin++ directory
  print ('INFO: Finding pin++ pintools in <%s>' % (args.pinppdir))
  pinpp_pintools = find_pintools (args.pinppdir)

  # Match the pin++ pintools to the native pintools, since pintool names are different
  pintools = match_pintools (native_pintools, pinpp_pintools)
  if not pintools:
    print ('ERROR: No matching native and pin++ pintools found, are they compiled?')
    sys.exit (1)

  # Open the file and write the header
  outfile = open (args.outfile, 'w')
  writer = csv.writer (outfile)
  writer.writerow (['Pintool', 'Command', 'Iteration', 'Native', 'Pin++', 'Difference', 'Difference_Percent']) 

  # Execute the test
  for native, pinpp in pintools:
    for (pub_cmd, sub_cmd, result_col, label) in commands:
      for iteration in range (1, args.iterations + 1):
        tool_name = os.path.split (native)[-1]
        print ('INFO: Executing pintool <%s>, iteration <%s>'
               % (tool_name, iteration))

        # Run native
        pub = run_pub (native, pub_cmd)
        run_sub (native, sub_cmd)
        native_time = get_time (pub.communicate ()[0], result_col)

        # Run pinpp
        pub = run_pub (pinpp, pub_cmd)
        run_sub (pinpp, sub_cmd)
        pinpp_time = get_time (pub.communicate ()[0], result_col)

        # Write the results
        writer.writerow ([tool_name,
                          label,
                          iteration,
                          native_time,
                          pinpp_time,
                          pinpp_time - native_time,
                          pinpp_time * 100 / native_time - 100])
main ()
