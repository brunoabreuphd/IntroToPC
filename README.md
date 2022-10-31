# IntroToPC

### Exercises for Intro to Parallel Computing Workshop using SDSC's Expanse.
The last version of this workshop was on 2021-11-17.
This workshop is offered by the [National Center for Supercomputing Applications](https://www.ncsa.illinois.edu/).
Each exercise is comprised of a serial code and the OpenMP-parallelized version of it. Makefiles are available for compilation with GCC, as well as batch job scripts with specific configurations to run the code on [SDSC's Expanse](https://www.sdsc.edu/services/hpc/expanse/).

## 1. [hello](https://github.com/babreu-ncsa/IntroToPC/tree/main/hello)
This exercise is the classic *Hello, World!* code. It serves as an introduction to how threads can execute tasks independently and asynchronously. 


## 2. [stats](https://github.com/babreu-ncsa/IntroToPC/tree/main/stats)
The *STATS* application calculates simples statistical problems of a large collection of real numbers extracted from a uniform probability distribution and organized into an array. It serves as an introduction to the concept of Task Parallelism.


## 3. [saxpy](https://github.com/babreu-ncsa/IntroToPC/tree/main/saxpy)
The *SAXPY* application performs a very common operation in Linear Algebra-related packages. It serves as an introduction to the concept of Data Parallelism.


# Contributing
This repository is intended to be used during live training sessions. More exercises can be found in the [Parallelization](https://github.com/babreu-ncsa/parallelization) GitHub repo.
If you would to contribute with a different exercise, I would be delighted to hear from you! 
