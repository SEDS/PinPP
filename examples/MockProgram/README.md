# Mock program

This is a mock program for testing the pin tool Dynamic Event Monitor and Reservoir Sampling.

## How to Use
- Run the `MPC` tool at the `PIN++` root directory `%MPC_ROOT%/mwc.pl -type <type> -features <features> pin++.mwc`;
- Build `my_shared_lib` in `debug` mode, a `my_shared_libd.dll` library will be generated;
- Build `mock_program` in `debug` mode, a `mock_program.exe` executable will be generated;
- When executing `mock_program.exe`, the library must be in the same directory with the executable.
