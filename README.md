Pin++
========

A C++ template meta-programmable framework for authoring Pintools

System Requirements
-------------------------

The following is the minumum system requirements needed to build and
use Pin++:

* Perl, on Windows we suggest [ActivePerl](http://www.activestate.com/activeperl)
* [GIT] (http://git-scm.com/downloads)
* [Pin](http://software.intel.com/en-us/articles/pintool) (build 61206, 62141) 
* [Makefile, Project, Workspace Creator](http://www.ociweb.com/products/mpc) (trunk) from its [Subversion](https://svn.dre.vanderbilt.edu/DOC/MPC/trunk) repo

To build the examples:

* C++11 compliant compiler

### Tested Compilers

We have physically tested Pin++ with the following compilers:

* Clang 5.0
* GCC 4.7
* Visual Studio 2008* (vc9), 2010 (vc10), 2012 (vc11)

If a compiler you use is not on the list above and Pin++ compiles
correctly, please let us know so we can update the list with the compiler
you have tested and/or are using.

\* Does not support compiling the examples.

Environment Setup
-------------------

Set ```PIN_ROOT``` environment variable to the location of Pin
since we will be building Pintools outside of the normal distribution 
of Pin. We also assume that you have your ```PATH``` (and ```LD_LIBRARY_PATH```
or ```DYLD_LIBRARY_PATH```) configured correctly for Pin. Next, clone the 
Pin++ repo and configure the environment variables:

**Windows**

    set PINPP_ROOT=[location of Pin++]
    set PATH=%PATH%;%PINPP_ROOT%\bin;%PINPP_ROOT%\lib

**Linux**

    export PINPP_ROOT=[location of Pin++]
    export PATH=$PATH:$PINPP_ROOT/bin
    export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$PINPP_ROOT/lib

**MacOS X**

    export PINPP_ROOT=[location of Pin++]
    export PATH=$PATH:$PINPP_ROOT/bin
    export DYLD_LIBRARY_PATH=$DYLD_LIBRARY_PATH:$PINPP_ROOT/lib

Quick Build
----------------

Generate the Pin++ workspace: 

    cd $PINPP_ROOT
    $MPC_ROOT/mwc.pl -type [build type] -features pin=1,[ia32=0|1],intel64=[0|1] pin++.mwc

If you are building Pin++ for a 32-bit architecture, then select 
```ia32=1```. If you are building Pin++ for a 64-bit architecture,
then select ```intel64=1```. You can not set both features to 1.

Lastly, build the generated workspace. The Pin++ library (i.e., ```pin++[.a|.lib]```) 
will be placed in ```$PINPP_ROOT/lib```.

Contact
-----------------

Send all questions to [hillj@cs.iupui.edu](mailto:hillj@cs.iupui.edu). Please make
sure to include ```Pin++``` in the subject.

Happy Coding!
