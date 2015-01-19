# Runtime Sampling

## Introduction
- This pintool performs routine sampling. The sampling is for either return address or runtime.
- Three different sampling algorithms are implemented:
  - Naive: For every routine during the run, compare a random number and the desired sampling percentage to determine that routine should be sampled. This algorithm will result in under- or over-sampling.
  - Constant: Skip constant number of routines between sampling. This algorithm usually gives exact sampling, with at most one missing or extra sample.
  - Reservoir: Implements the reservoir sampling algorithm.
  
## Refactor History
- The three alogrithms are first implemented as three individual pintools.
  - MPC file `simple_sampling.mpc`;
  - Pintool files `simple_sampling_constant.cpp`, `simple_sampling_naive.cpp` and `simple_sampling_reservoir.cpp`.
  - The three pintools sample the return addresses;
  - Syntax: `%PIN_ROOT%/pin -t PINPP_ROOT%/lib/simple_sampling_<algorithm>.dll -p <percentage> -f <output_filename> -- <program>`.
- Since the reservoir sampling algorithm is fairly complicated and there are three different stages, I applied the state pattern for that implementation, and refactored into a new pintool `sampling_reservoir`.
  - MPC file `sampling_reservoir.mpc`;
  - Pintool file `sampling_reservoir.cpp`;
  - Supporting files include context, state, and state implementation;
  - This pintool also samples the return addresses;
  - Syntax: `%PIN_ROOT%/pin -t PINPP_ROOT%/lib/sampling_reservoir.dll -p <percentage> -f <output_filename> -- <program>`.
- I tried to merge the three tools into one that can select the algorithm by a parameter, but was not very successful. The tools that implemented constant and naive sampling were merged, but not the reservoir.
  - MPC file `runtime_sampling.mpc`;
  - Pintool file `runtime_sampling.cpp`;
  - Supporting files: runtime sampling instrument (`RT_Smp_Instr`), sampling (`RT_Smp_Analysis`) and analysis (`RT_Smp_Sampling`) files;
  - This pintool samples the runtime.
  - Syntax: `%PIN_ROOT%/pin -t %PINPP_ROOT%/lib/runtime_sampling.dll -p <percentage> -f <output_filename> -a <algorithm> -- <program>`
  
## How to Use
- Build the pintool;
- Test with the `mock_program.exe` with integer argument. E.g. `%PIN_ROOT%/pin -t %PINPP_ROOT%/lib/<pintool_name>.dll <pintool_arguments> -- mock_program.exe 1000`, this would calculate the first 100 fibonacci number 1000 times.
- Please note that for reservoir sampling, the `TOTAL_TO_DISTINCT_RATIO` greatly affects the runtime and whether there will be significant under- or over-sampling.

## Potential Future Improvements
- The reservoir sampling implementation should be merged into the runtime sampling tool as the constant and naive implementations.
- The runtime sampling tools should also record the routine name instead of just the runtime.
- The reservoir sampling requires an estimation of the total number of routines. Currently I use the number of distinct routines to estimate total number of routines. But this is far from desirable, as you can see in the `mock_program`, the fibonacci routine is executed `n` times, so the total routine counts can vary significantly from any estimation based on the number of distinct routines. One solution is to recursively apply reservoir sampling for every `k` routines. That is, we reset all the states for after `k` routines, and states are accumulated at the end. In this way, except for the last `k` routines, the estimation of total routines is always accurate, and the bias is confined only in the last `k` routines. If the value of `k` is small enough, the bias can be negligible.
