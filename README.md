Pin++
========

A C++ template meta-programmable framework for authoring Pintools

Publications
-------------------------
* [Pin++: an object-oriented framework for writing pintools](http://dl.acm.org/citation.cfm?id=2658777)

System Requirements
-------------------------

The following is the minumum system requirements needed to build and
use Pin++:

* Perl, on Windows we suggest [ActivePerl](http://www.activestate.com/activeperl)
* [GIT] (http://git-scm.com/downloads)
* [Pin](http://software.intel.com/en-us/articles/pintool) (build 61206, or greater) 
* [Makefile, Project, Workspace Creator](http://www.ociweb.com/products/mpc) (trunk) 
  from its [Subversion](https://svn.dre.vanderbilt.edu/DOC/MPC/trunk) repo. The 
  username/password for read-only access is anonymous/anonymous.

To build the examples:

* C++11 compliant compiler

If you building only the Pin++ library, then you do not have to worry
about the requirements for building the examples.

Tested Compilers
-------------------

We have physically tested Pin++ with the following compilers:

* GCC 4.2\*, 4.6\*, 4.7, 4.8, 4.9
* Visual Studio 2008 (vc9)\*, 2010 (vc10)\*, 2012 (vc11)

\* Does not support compiling the examples.

If a compiler you use is not on the list above and Pin++ compiles
correctly, please let us know so we can update the list with the compiler
you have tested and/or are using.

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

### Compiling on MacOS X

The default compiler on MacOS X (distributed via XCode) can sometimes be an 
outdated version of GCC. If you need to use a newer version of GCC than what 
is provided when installing XCode, we recommend installing your version of 
choice via [MacPorts](http://www.macports.org).

To use the different version of GCC, make sure set the ```CC``` and 
```CXX``` macros to the corresponding version of ```gcc``` and ```g++```
that you want to you. 

Here is an example:

    make CC=gcc-mp-4.9 CXX=g++-mp-4.9

Thanks to [Kenneth Miller](https://github.com/KennethAdamMiller) for the 
suggestion.

### Compiling the C++11 examples

When building the Pin++ examples, you must enable the C++11 feature ```cpp11=1```. 
Here is the command-line for building the Pin++ library, and the examples:

    $MPC_ROOT/mwc.pl -type [build type] -features pin=1,[ia32=0|1],intel64=[0|1],cpp11=1 pin++.mwc
    
If you do not have a C++11 compliant compiler, then you will get a LOT of 
compile and link errors build you try to build the workspace.


Contact
-----------------

Send all questions to [hillj@cs.iupui.edu](mailto:hillj@cs.iupui.edu). Please make
sure to include ```Pin++``` in the subject.

Happy Coding!
