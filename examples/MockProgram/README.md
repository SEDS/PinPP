# Mock program

This is a mock program for testing the pin tool Dynamic Event Monitor and Reservoir Sampling.

## How to Build
- Run the `MPC` tool at the `PIN++` root directory `%MPC_ROOT%/mwc.pl -type <type> -features <features> pin++.mwc`;
- Build `my_shared_lib` in `debug` mode, a `my_shared_libd.dll` library will be generated;
- Build `mock_program` in `debug` mode, a `mock_program.exe` executable will be generated;
- When executing `mock_program.exe`, the library must be in the same directory with the executable.

## How to Use
- `mock_program.exe` transmit objects; used for pintool `dynamic_event_monitor`;
- `mock_program.exe <n>` compute the first 100 fibonacci numbers for `n` times; used for testing reservoir sampling.
