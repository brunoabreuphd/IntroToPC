/***
* File: saxpy_omp.cpp
* Description: OpenMP parallelized version of C++ SAXPY
* Author: Bruno R. de Abreu  |  babreu at illinois dot edu
* National Center for Supercomputing Applications (NCSA)
*  
* Creation Date: Thursday, 4th November 2021, 10:18:40 am
* Last Modified: Thursday, 4th November 2021, 10:29:31 am
*  
* Copyright (c) 2021, Bruno R. de Abreu, National Center for Supercomputing Applications.
* All rights reserved.
* License: This program and the accompanying materials are made available to any individual
*          under the citation condition that follows: On the event that the software is
*          used to generate data that is used implicitly or explicitly for research
*          purposes, proper acknowledgment must be provided in the citations section of
*          publications. This includes both the author's name and the National Center
*          for Supercomputing Applications. If you are uncertain about how to do
*          so, please check this page: https://github.com/babreu-ncsa/cite-me.
*          This software cannot be used for commercial purposes in any way whatsoever.
*          Omitting this license when redistributing the code is strongly disencouraged.
*          The software is provided without warranty of any kind. In no event shall the
*          author or copyright holders be liable for any kind of claim in connection to
*          the software and its usage.
***/

#include <iostream>
#include <vector>
#include <sys/time.h>
#include "omp.h"

#define ORD 1 << 27 // size of array

using namespace std;

void saxpy(float a, const vector<float> &x, vector<float> &y);

int main()
{
    // instantiate vectors and attribute values
    vector<float> x, y;
    float r, elmnt;
    srand(time(NULL));
    for (int i = 0; i < ORD; i++)
    {
        r = rand() % RAND_MAX;
        elmnt = float(r) / (RAND_MAX);
        x.push_back(elmnt); // x is noise
        y.push_back(1.0);   // y is just ones
    }

    float a = 2.0; // scalar multiplier (y -> a*x + y)

    // stopwatch variables
    struct timeval start_time, stop_time, elapsed_time;

    // now call saxpy
    gettimeofday(&start_time, NULL);
    #pragma omp parallel
    {
        saxpy(a, x, y);
    }
    gettimeofday(&stop_time, NULL);

    timersub(&stop_time, &start_time, &elapsed_time);
    cout << "Elapsed time (s): " << elapsed_time.tv_sec + elapsed_time.tv_usec / 1000000.0 << endl;

    return 0;
}

void saxpy(float a, const vector<float> &x, vector<float> &y)
{
    #pragma omp for
    for (int i = 0; i < x.size(); i++)
    {
        y[i] = a * x[i] + y[i];
    }
}
