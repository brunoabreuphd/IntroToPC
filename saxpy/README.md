# saxpy

This is a simple C code that performs SAXPY: Single-precision A\*X Plus Y. The idea here is that we have two arrays X, Y, and one scalar A such that we perform Z = A\*X + Y and update Y with Z. This is a standard [BLAS](http://www.netlib.org/blas/) function and it can be very helpful to implement many other Linear Algebra operatrions.

Differently than in the [matrix multiplication exercise](../matmul), here we have a single, non-nested loop, which makes the computational task conceptually different. As the arrays here are massive (2^28 in the original code), most of the job is not only performing floating point arithmetics, but actually dealing with smart memory management of such a big structure (reads and writes). Therefore, there are no reasons to expect that the compiler optimization flags will provide the same improvements.

We will be using a C code and GCC compilers. I ran this on a Macbook, with GCC 10.2.1 20201220.

## [serial](./serial)
This folder contains the C serial code that performs SAXPY, [saxpy_serial.c](./serial/saxpy_serial.c), and a [Makefile](./serial/Makefile) to help users with no compilation experience (if that is your case, just bring your Terminal session to the [serial](./serial) folder and type *make*). The binary will have the default *a.out* name. Execute the binary and check the output for the execution time.

## [compiler_opt](./compiler_opt)
This folder contains the serial code and supporting Python files. The GCC compilation flags that perform optimization can be found [here](https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html) (there are many). If you do not want to deal with Python, just edit the *LDFLAGS* variable in the [Makefile](./compiler_opt/Makefile) to include some of the flags, compile it and run it to see the optimized run time. If you are okay with Python, you may want to check:
- [gcc_opt_flags.ipynb](./compiler_opt/gcc_opt_flags.ipynb): This is a Jupyter notebook that calls GCC (gcc) with every single compilation flag for optimization listed in the GCC documentation, then plots the times. 
- [gcc_opt_flags.py](./compiler_opt/gcc_opt_flags.ipynb): It does the same as the notebook, but I provided it in case you want to call it from a place where you don't have access to a Jupyter notebook (a remote cluster, for instance). The graphs are saved to *png* files.

These Python codes do not require fancy imports: pretty much any base Anaconda distribution that I am aware of should have the necessary packages already installed. However, in case it does not work for you, the environment is specified in [conda_env.yml](./compiler_opt/conda_env.yml).

### Conclusions
- None of the flags listed in the Optimize Options of the GNU Compiler documentation changes the execution time of SAXPY significantly.
- Instead of trying individual options, one should always first use the bundled options (-Ox)
- For this simple code, level 2 and 3 optimizations reduce execution time by a good factor
- Compiler optimizations can be obscure. Make sure your code runs without errors before using them (writing a simple test is a good practice)

### Further exercises
There are several things that you can do to improve your experience and bring it closer to your target situation. Here are a few suggestions:
- Change the array data type (go larger -- double precision, complex). How does the compiler optimization work?
- Re-write this code in a different language (such as Fortran). What happens?
- Try to use different compilers (Intel, for instance). What are the flags available for optimization? How do they work?

If you do these changes or any others that you wish, let me know about your results!

### Additional information
You may be curious about what kind of optimization the compiler has performed when using -Ox flags, or even for individual, specific flags, you may wonder why they did not do anything. It is possible to obtain some information about that with GCC using the *-fopt-info* options. The exact syntax can be found [here](https://gcc.gnu.org/onlinedocs/gcc/Developer-Options.html). As an example, if you want to list all information about a level 3 optimization for the SAXPY code, you would use:

`gcc -O3 -fopt-info-all=opt.info saxpy.c`

and that would dump the information in file *opt.info*. For this particular SAXPY code, at least using GCC 10.2.1 20201220, it looks to me that optimization is largely performed by vectorizing the *for* loop declared in the function (line 56 of the code). If you want to know more about vectorization, [here's an excellent article](https://objectcomputing.com/resources/publications/sett/december-2016-performance-optimization-on-modern-processor-architecture-through-vectorization). 


## [openmp](./openmp)
This folder contains the code with OpenMP directives [saxpy_openmp.c](./openmp/saxpy_openmp.c) and supporting Python files. The GCC compilation flag to enable OpenMP is *-fopenmp*. If you do not want to deal with Python, just make sure this flag is listed in the *LDFLAGS* variable in the [Makefile](./openmp/Makefile), compile it and run it to see the execution time. To cast a different number of OpenMP threads, before executing the *a.out* binary, set the *OMP_NUM_THREADS* environment variable. For example,

`export OMP_NUM_THREADS=4`

will use 4 threads.

If you are okay with Python, you may want to check:
- [openmp_scaling.ipynb](./openmp/openmp_scaling.ipynb): This is a Jupyter notebook that calls GCC (gcc) to compile *saxpy_openmp.c* and run it with a varying number of threads. It then plots the resulting scaling.
- [openmp_scaling.py](./openmp/openmp_scaling.py): It does the same as the notebook, but I provided it in case you want to call it from a place where you don't have access to a Jupyter notebook (a remote cluster, for instance). The graphs are saved to *png* files.

These Python codes do not require fancy imports: pretty much any base Anaconda distribution that I am aware of should have the necessary packages already installed. However, in case it does not work for you, the environment is specified in [conda_env.yml](./compiler_opt/conda_env.yml).

### Conclusions
- OpenMP is an easy approach to parallelize loop-intensive computation in an incremental fashion.
- Speedup can be quite linear, but it tends to saturate.
- Make sure the number of threads you are calling is compatible to your system.


### Further exercises
- There is another loop in this program (line 42). Try parallelizing that one as well. Measure the performance by timing that part of the code.
- Write a Fortran version of this code. Is there any performance difference?
- Compare this exercise to the results of [compiler_opt](./compiler_opt). How does OpenMP compare to compiler vectorization?


### Additional information
OpenMP is not a language itself, and it finds its ways through C compilers by the use of *pragma*s. If you are not familiar with these, [here is a good description of how they work](https://www.geeksforgeeks.org/pragma-directive-in-c-c/).

*Threads* and *cores* can be confusing. If you want to know better what a thread actually is, [check out this article](https://blog.logicalincrements.com/2019/10/cpu-what-are-threads/).
