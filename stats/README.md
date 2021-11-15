# stats

This is a simple C++ code that calculates basic statistical properties of a set of numbers extracted from a uniform probability distribution and organized into an array. 

We have a three different functions that involve single, non-nested loops, and we want to parallelize calls to these functions so each one can be executed independently.

We will be using GCC compilers. I ran this on a 2020 Macbook Pro with M1 chip, with GCC 10.2.1 20201220.

## [serial](./serial)
This folder contains the C++ serial code that performs STATS, [stats_serial.cpp](./serial/stats_serial.cpp), and a [Makefile](./serial/Makefile) to help users with no compilation experience (if that is your case, just bring your Terminal session to the [serial](./serial) folder and type *make*). The binary will be named *stats_serial.exe*. Execute the binary and check the output for the execution time.
 

## [omp](./omp)
This folder contains the code with OpenMP directives [stats_omp.cpp](./omp/stats_omp.cpp). The GCC compilation flag to enable OpenMP is *-fopenmp*, which is included in the [Makefile](./omp/Makefile), compile it and run it to see the execution time.

After compilation, you can run this code on one of Expanse's compute nodes by issuing the command
```
sbatch stats.jobscript
```

which will send the [stats.jobscript](./omp/stats.jobscript) to the scheduler and run it with varying number of threads (1 to 6). The output will be placed in a file named *stats-YourJobID.out*.

### Conclusions
- OpenMP is an easy approach to parallelize tasks.
- Speedup can be quite linear, but scaling is constrained by the number of tasks, and performance is dominated by the slowest/busiest thread.


### Further exercises
- Try parallelizing the loops as well. This would be an example of mixed Data and Task parallelism.



### Additional information
OpenMP is not a language itself, and it finds its ways through C compilers by the use of *pragma*s. If you are not familiar with these, [here is a good description of how they work](https://www.geeksforgeeks.org/pragma-directive-in-c-c/).

*Threads* and *cores* can be confusing. If you want to know better what a thread actually is, [check out this article](https://blog.logicalincrements.com/2019/10/cpu-what-are-threads/).
