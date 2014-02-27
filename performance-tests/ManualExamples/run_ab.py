#!/usr/bin/python3

# Uses Apache Benchmark (ab) to time executions of pin++ vs native pin

import time
import os
import argparse
import sys
import subprocess
import csv
import signal
import re

#
# Parse args
#
def parse_args ():
  parser = argparse.ArgumentParser (description='Gathers performance metrics of pin++ vs native pin')

  parser.add_argument ('--outfile', default='results.csv', type=str, help='Output file. Defaults to results.csv')
  parser.add_argument ('--pinppdir', default=os.environ['OASIS_ROOT'] + '/examples/pintools', type=str, help='Pin++ pintool directory. Defaults to $OASIS_ROOT/examples/pintools')
  parser.add_argument ('--pindir', default=os.environ['PIN_ROOT'] + '/source/tools', type=str, help='Native pintool directory.  Defaults to $PIN_ROOT/source/tools')
  parser.add_argument ('--url', default=None, type=str, help='URL to test with apache benchmark.')
  parser.add_argument ('--requests', default=[1, 10, 100, 1000, 10000, 100000], type=int, nargs='+', help='Space-separated list of the number of requests to test.')
  parser.add_argument ('--concurrency', default=[1, 10, 100, 1000], type =int, nargs='+', help='Space-separated list of the number of clients to test.')
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
# apache running
#
def apache_running ():
  # Run apachectl to see if apache is running
  cmd = 'apachectl status'
  dead_text = 'w3m: Can\'t load http://localhost:80/server-status.\n'
  output = subprocess.check_output (cmd, shell=True, stderr=subprocess.STDOUT)
  return dead_text != output 

#
# Start apache
#
def start_apache (pintool):
  print ('INFO: Starting apache')
  cmd = ' '.join ([os.path.join (os.environ['PIN_ROOT'], 'pin'),
                   '-follow_execv',
                   '-t',
                   pintool,
                   '--',
                   'apachectl start 1>/dev/null 2>&1'])

  # Check that apache is responding prior to returning
  while (apache_running () == False):
    subprocess.call (cmd, shell=True)

#
# Stop apache
#
def stop_apache ():
  print ('INFO: Stopping apache')
  while (apache_running () == True):
    subprocess.call ('apachectl stop 1>/dev/null 2>&1', shell=True)

#
# Run ab
#
def run_ab (url, concurrency, requests):
  # Build the command
  # Example: ab -c 10 -r 10 localhost/index.html
  cmd = ' '.join (['ab',
                   '-c',
                   '%s' % concurrency,
                   '-n',
                   '%s' % requests,
                   url])

  # DEBUG: Check the command
#  print (repr (cmd))

  # Run the command
  output = subprocess.check_output (cmd, shell=True)

  # If the output has a warning (i.e. unreliable results, redo the test)
  if ('WARNING' in output):
    print ('WARN: Unreliable results found, redoing test')
    return run_ab (url, concurrency, requests)

  return output
#
# Main entry point for the application
#
def main ():
  # Parse the arguments
  args = parse_args ()

  # Check for URL
  if (not args.url):
    print ("Error: No URL specified")
    sys.exit (1)

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
  writer.writerow (['Pintool', 'Concurrency', 'Requests', 'Iteration', 'Native', 'Pin++', 'Difference', 'Difference_Percent']) 

  # Compiled regex to get the average time per request across
  # all concurrent requests
  time_per_request = re.compile ('Time per request:\s+(\d+\.\d+) \[.*\] \(mean, across')

  # Execute the test
  for concurrency in args.concurrency:
    for requests in args.requests:
      if (concurrency > requests):
        continue

      for native, pinpp in pintools:
        for iteration in range (1, args.iterations + 1):
          tool_name = os.path.split (native)[-1]
          print ('INFO: Executing pintool <%s>, iteration <%s>'
                 % (tool_name, iteration))

          # Get native results
          start_apache (native)
          run_ab (args.url, 1, 1)
          native_output = run_ab (args.url, concurrency, requests)
          stop_apache ()

          # Get pin++ results
          start_apache (pinpp)
          run_ab (args.url, 1, 1)
          pinpp_output = run_ab (args.url, concurrency, requests)
          stop_apache ()

          # Find the average time per request
          native_time = float (time_per_request.search (native_output).group (1))
          pinpp_time = float (time_per_request.search (pinpp_output).group (1))

          # Write the results
          writer.writerow ([tool_name,
                            concurrency,
                            requests,
                            iteration,
                            native_time,
                            pinpp_time,
                            pinpp_time - native_time,
                            pinpp_time * 100 / native_time - 100])

main ()
