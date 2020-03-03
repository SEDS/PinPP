# Standards-based Distributed Middleware Monitor (SDMM)

# Pre-requisites
1. A Perl compiler
2. Makefile Project Creator (MPC)
  - After MPC is installed, make sure *MPC_ROOT* is set to the MPC home directory

# Compile & Installation Instructions
After cloning the Pin++ Repo and setting the *PINPP_ROOT* environment variable to
the Pin++ home directory, you need to create the Makefiles with the following command:
`$MPC_ROOT/mwc.pl -type make -features pin=1,[ia32=0|1],intel64=[0|1],cpp11=1 pin++.mwc`

To compile SDMM, run from *PINPP_ROOT*:
`make sdmm`

_SDMM was only tested on Linux Ubuntu 14.04 with kernel._

# Usage Instructions
To run SDMM, invoke the pintool with a configuration file:
`$PIN_ROOT/pin.sh -t $PINPP_ROOT/lib/libsdmm.so -conf <config file> -out <output file> -- <executable>`

An example of the config file is in $PINPP_ROOT/examples/SDMM/config.sdmm

# Supported Middleware
Currently, SDMM supports the following standards-based distributed middleware.
1. CORBA
2. [DDS](https://www.omg.org/spec/DDS/1.4/PDF)
  - We tested SDMM with [OpenDDS v3.13.3](https://opendds.org/)
3. [gRPC v1.20.x](https://github.com/grpc/grpc/tree/v1.20.x)
  - SDMM was not tested on the latest version of gRPC.