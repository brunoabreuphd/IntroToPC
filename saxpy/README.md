# saxpy

This is a simple C++ code that performs SAXPY: Single-precision A\*X Plus Y. The idea here is that we have two arrays X, Y, and one scalar A such that we perform Z = A\*X + Y and update Y with Z. This is a standard [BLAS](http://www.netlib.org/blas/) function and it can be very helpful to implement many other Linear Algebra operatrions.

We have a single, non-nested loop that we want to parallelize. As the arrays are quite big are (2^27 in the original code), most of the job is not only performing floating point arithmetics, but actually dealing with smart memory (cache) management (reads and writes).

We will be using GCC compilers. I ran this on a 2020 Macbook Pro with M1 chip, with GCC 10.2.1 20201220.

## [serial](./serial)
This folder contains the C++ serial code that performs SAXPY, [saxpy_serial.cpp](./serial/saxpy_serial.cpp), and a [Makefile](./serial/Makefile) to help users with no compilation experience (if that is your case, just bring your Terminal session to the [serial](./serial) folder and type *make*). The binary will be named *saxpy_serial.exe*. Execute the binary and check the output for the execution time.
 

## [omp](./omp)
This folder contains the code with OpenMP directives [saxpy_omp.cpp](./omp/saxpy_omp.cpp). The GCC compilation flag to enable OpenMP is *-fopenmp*, which is included in the [Makefile](./omp/Makefile), compile it and run it to see the execution time.

After compilation, you can run this code on one of Expanse's compute nodes by issuing the command
```
sbatch saxpy.jobscript
```

which will send the [saxpy.jobscript](./omp/saxpy.jobscript) to the scheduler and run it with varying number of threads (1 to 32). The output will be placed in a file named *saxpy-YourJobID.out*.

### Conclusions
- OpenMP is an easy approach to parallelize loop-intensive computation in an incremental fashion.
- Speedup can be quite linear, but it tends to saturate.
- Make sure the number of threads you are calling is compatible to your system.


### Further exercises
- There is another loop in this program (line 42). Try parallelizing that one as well. Measure the performance by timing that part of the code.
- Write a Fortran version of this code. Is there any performance difference?


### Additional information
OpenMP is not a language itself, and it finds its ways through C compilers by the use of *pragma*s. If you are not familiar with these, [here is a good description of how they work](https://www.geeksforgeeks.org/pragma-directive-in-c-c/).

*Threads* and *cores* can be confusing. If you want to know better what a thread actually is, [check out this article](https://blog.logicalincrements.com/2019/10/cpu-what-are-threads/).
