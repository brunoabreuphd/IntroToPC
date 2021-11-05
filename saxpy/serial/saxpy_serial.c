/*!!!!
!! File: saxpy_serial.c
!! Description: SAXPY code
!! Author: Bruno R. de Abreu  |  babreu at illinois dot edu
!! National Center for Supercomputing Applications (NCSA)
!!  
!! Creation Date: Thursday, 19th August 2021, 9:29:08 am
!! Last Modified: Thursday, 19th August 2021, 9:29:21 am
!!  
!! Copyright (c) 2021, Bruno R. de Abreu, National Center for Supercomputing Applications.
!! All rights reserved.
!! License: This program and the accompanying materials are made available to any individual
!!          under the citation condition that follows: On the event that the software is
!!          used to generate data that is used implicitly or explicitly for research
!!          purposes, proper acknowledgment must be provided in the citations section of
!!          publications. This includes both the author's name and the National Center
!!          for Supercomputing Applications. If you are uncertain about how to do
!!          so, please check this page: https://github.com/babreu-ncsa/cite-me.
!!          This software cannot be used for commercial purposes in any way whatsoever.
!!          Omitting this license when redistributing the code is strongly disencouraged.
!!          The software is provided without warranty of any kind. In no event shall the
!!          author or copyright holders be liable for any kind of claim in connection to
!!          the software and its usage.
!!!!*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define ORD 1 << 27 // size of array

float x[ORD];
float y[ORD];
float a = 2.0;

void saxpy(int n, float a, float *x, float *y);

int main()
{
    struct timeval start_time, stop_time, elapsed_time;

    for (int i = 0; i < ORD; ++i)
    {
        y[i] = 1.0;
        x[i] = (float)rand() / RAND_MAX; // x is just noise
    }
    gettimeofday(&start_time, NULL); // start clock
    saxpy(ORD, a, x, y);
    gettimeofday(&stop_time, NULL);                   // stop clock
    timersub(&stop_time, &start_time, &elapsed_time); // run time
    printf("Time for SAXPY: %f s\n", elapsed_time.tv_sec + elapsed_time.tv_usec / 1000000.0);
    return 0;
}

void saxpy(int n, float a, float *restrict x, float *restrict y)
{
    for (int i = 0; i < n; ++i)
        y[i] = a * x[i] + y[i];
}
