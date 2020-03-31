# Standards-based Distributed Middleware Monitor (SDMM)

# System Requirements
The requirements are the same for Pin++. Please follow the instructions @ [Pin++ README.md](https://github.iu.edu/SEDS/PinPP/blob/master/README.md).

* Make sure *MPC_ROOT* is set to the MPC home directory.
* Make sure *PIN_ROOT* is set to the Pin home directory.
* Make sure *PINPP_ROOT* is set to the Pin++ home directory.

To use SDMM, we assume you also have one of the [supported distributed middleware](#Supported-Middleware) installed on your system.

# Compile & Installation Instructions
After cloning the Pin++ Repo and setting the *PINPP_ROOT* environment variable to
the Pin++ home directory, you need to create the Makefiles with the following command:
`$MPC_ROOT/mwc.pl -type make -features pin=1,ia32=[0|1],intel64=[0|1],cpp11=1 pin++.mwc`

For example, on a 64-bit system run: `$MPC_ROOT/mwc.pl -type make -features pin=1,ia32=0,intel64=1,cpp11=1 pin++.mwc`

To compile SDMM, run from *PINPP_ROOT*: `make sdmm`

_SDMM was only tested on Ubuntu 14.04 with kernel 3.13.0._

# Usage Instructions
To run SDMM, invoke the pintool with a configuration file:
* `$PIN_ROOT/pin.sh -t $PINPP_ROOT/lib/libsdmm.so -conf <config file> -out <output file> -- <executable>`

Running SDMM with [gRPC HelloWorld Example](https://github.com/grpc/grpc/tree/master/examples/cpp/helloworld):
* In terminal 1: `$PIN_ROOT/pin.sh -t $PINPP_ROOT/lib/libsdmm.so -conf $PINPP_ROOT/examples/SDMM/gRPC-config.sdmm -out server.log -- /path/to/greeter_server`
* In terminal 2: `$PIN_ROOT/pin.sh -t $PINPP_ROOT/lib/libsdmm.so -conf $PINPP_ROOT/examples/SDMM/gRPC-config.sdmm -out client.log -- /path/to/greeter_client`

Running SDMM with [OpenDDS StockQuoter Example](https://github.com/objectcomputing/OpenDDS/tree/master/examples/DCPS/IntroductionToOpenDDS):
* In terminal 1: `$PIN_ROOT/pin.sh -t $PINPP_ROOT/lib/libsdmm.so -conf $PINPP_ROOT/examples/SDMM/DDS-config.sdmm -out pub.log -- /path/to/publisher -DCPSConfigFile /path/to/dds_tcp_conf.ini`
* In terminal 2: `$PIN_ROOT/pin.sh -t $PINPP_ROOT/lib/libsdmm.so -conf $PINPP_ROOT/examples/SDMM/DDS-config.sdmm -out sub.log -- /path/to/subscriber -DCPSConfigFile /path/to/dds_tcp_conf.ini`

# Supported Middleware
Currently, SDMM supports the following standards-based distributed middleware.
1. CORBA
2. [DDS](https://www.omg.org/spec/DDS/1.4/PDF) and was tested with [OpenDDS v3.13.3](https://opendds.org/)
3. [gRPC v1.20.x](https://github.com/grpc/grpc/tree/v1.20.x). SDMM was not tested on the latest version of gRPC.

# Config File Explanation
The SDMM config file has three flags:
* *MIDDLEWARE* - which defines the distributed middleware used in the system
* *INCLUDE* - is a list of binary files that contain the communication methods. SDMM will search for the communication methods specific to each middleware in these binaries.
* *HELPER* - sometimes communication methods will invoke methods defined in other binaries, list those binaries here. For gRPC and OpenDDS applications, this line is identical to the *INCLUDE* flag.