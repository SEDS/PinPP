Pin++
========

A C++ template meta-programmable framework for authoring Pintools.

System Requirements
-------------------------

* [Perl](http://www.activestate.com/activeperl)
* [GIT] (http://git-scm.com/downloads)
* [Pin](http://software.intel.com/en-us/articles/pintool) (ver 2.13, or greater) 
* [Makefile, Project, Workspace Creator](http://www.ociweb.com/products/mpc) from its [Subversion](https://svn.dre.vanderbilt.edu/DOC/MPC/trunk) repo

To build the examples:

* C++11 compliant compiler

Setup
-----------

Set ```PIN_ROOT``` environment variable to the location of Pin
since we will be building Pintools outside of the normal distribution 
of Pin. Next, clone the Pin++ repo and configure the environment variables:

**Windows**

    set PINPP_ROOT=[location of Pin++]
    set PATH=%PATH%;%PINPP_ROOT%\bin;%PINPP_ROOT%\lib

**Linux**

    export PINPP_ROOT=[location of OASIS]
    export PATH=$PATH:$PINPP_ROOT/bin
    export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$PINPP_ROOT/lib

**MacOS X**

    export PINPP_ROOT=[location of OASIS]
    export PATH=$PATH:$PINPP_ROOT/bin
    export DYLD_LIBRARY_PATH=$DYLD_LIBRARY_PATH:$PINPP_ROOT/lib

Generate the Pin++ workspace: 

    cd $PINPP_ROOT/pin++
    $MPC_ROOT/mwc.pl -type [build type] -features pin=1,[ia32=0|1],intel64=[0|1] pin++.mwc

If you are building Pin++ for a 32-bit architecture, then select 
```ia32=1```. If you are building Pin++ for a 64-bit architecture,
then select ```intel64=1```. You can not set both features to 1.

Lastly, build the generated workspace. The Pin++ library (i.e., ```pin++[.a|.lib]```) 
will be placed in ```$PINPP_ROOT/lib```.

Happy Coding!
