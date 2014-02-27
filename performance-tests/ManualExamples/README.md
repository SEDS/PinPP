This script is used to compare the performance of a native Pintool
and a Pin++ Pintool. The script works by locating the native Pintool
that matches the corresponding Pin++ implementation, and executing
the instrumenting the specified binary.

Basic Usage
------------

Use the script as follows:

    %> python3 run_test.py [arguments]
    
Example:    

    %> python3 run_test.py --binary ls

### Command-line Arguments

The command-line arguments for the script are:

* outfile - Result output filename
* pinppdir - Pin++ pintool directory
* pindir - Native pintool directory
* binary - The binary to use for the test
* binary\_file - File with one binary per line to test
* iterations - Number of times to test the pintools

### Output Format

The output file is a CSV format.  Each row contains:

* pintool - Name of the pintool
* command - The binary used for the test
* iteration - The iteration number
* native - Execution time of the native pintool
* pin++ - Execution time of the pin++ pintool
* difference - Time difference (pin++ - native)
* difference\_percent - difference as a percentage

Running in Emulab
------------------

There is an experiment named **pinpp** in the OASIS project. This 
experiment can be used to run this script. Most of the configuration 
has been automated.  After swapping the experiment in, do the 
following:

    %> sudo bash /proj/OASIS/exp/pinpp/bin/install_packages.sh
    %> sudo chown -R [userid]:OASIS /opt
    %> source /proj/OASIS/exp/pinpp/bin/deploy.sh

At this time, all dependencies for Pin will be installed. Assuming you
have already built the examples, you can run the script as stated above.
