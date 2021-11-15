# hello

This is a simple C++ *Hello, World* code.

We have a call to the standard output to print the Hello message, and we want to parallelize it and make several threads print the same message independently.

We will be using GCC compilers. I ran this on a 2020 Macbook Pro with M1 chip, with GCC 10.2.1 20201220.

## [serial](./serial)
This folder contains the C++ serial code that performs Hello, [hello_serial.cpp](./serial/hello_serial.cpp), and a [Makefile](./serial/Makefile) to help users with no compilation experience (if that is your case, just bring your Terminal session to the [serial](./serial) folder and type *make*). The binary will be named *hello_serial.exe*. Execute the binary and check the output.
 

## [omp](./omp)
This folder contains the code with OpenMP directives [hello_omp.cpp](./omp/hello_omp.cpp). The GCC compilation flag to enable OpenMP is *-fopenmp*, which is included in the [Makefile](./omp/Makefile), compile it and run it to see the execution time.

After compilation, you can run this code on one of Expanse's compute nodes by issuing the command
```
sbatch hello.jobscript
```

which will send the [hello.jobscript](./omp/hello.jobscript) to the scheduler and run it with 8 threads. The output will be placed in a file named *hello-YourJobID.out*.

### Conclusions
- Threads can execute their tasks independently
- Some threads can be a little slower or faster than the others.



### Additional information
OpenMP is not a language itself, and it finds its ways through C compilers by the use of *pragma*s. If you are not familiar with these, [here is a good description of how they work](https://www.geeksforgeeks.org/pragma-directive-in-c-c/).

*Threads* and *cores* can be confusing. If you want to know better what a thread actually is, [check out this article](https://blog.logicalincrements.com/2019/10/cpu-what-are-threads/).

