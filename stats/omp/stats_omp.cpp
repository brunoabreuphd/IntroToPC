/***
* File: stats_omp.cpp
* Description: OpenMP parallelized version of C++ code for simple vector stats
* Author: Bruno R. de Abreu  |  babreu at illinois dot edu
* National Center for Supercomputing Applications (NCSA)
*  
* Creation Date: Tuesday, 2nd November 2021, 10:57:10 am
* Last Modified: Tuesday, 2nd November 2021, 12:08:16 pm
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

#define ORD 1 << 27 // array size

using namespace std;
void get_vec_min(const vector<double> &v);
void get_vec_max(const vector<double> &v);
void get_vec_avg(const vector<double> &v);

int main()
{
    // create a vector with random noise
    vector<double> vec;
    double elmnt, r;
    srand(time(NULL));
    for (int i = 0; i < ORD; i++)
    {
        r = rand() % RAND_MAX;
        elmnt = double(r) / (RAND_MAX);
        vec.push_back(elmnt);
    }

    // variables for timing
    struct timeval start_time, stop_time, elapsed_time;
    
    gettimeofday(&start_time, NULL); // start clock
    #pragma omp parallel
    {
        #pragma omp sections
        {
            #pragma omp section
            {
                // find vector min
                get_vec_min(vec);
            }
            #pragma omp section
            {
                // find vec max
                get_vec_max(vec);
            }
            #pragma omp section
            {
                // find vec avg
                get_vec_avg(vec);
            }
        }
    }
    gettimeofday(&stop_time, NULL);                   // stop clock
    timersub(&stop_time, &start_time, &elapsed_time); // time diff
    cout << "Elapsed time: " << elapsed_time.tv_sec + elapsed_time.tv_usec / 1000000.0 << endl;

    return 0;
}

void get_vec_min(const vector<double> &v)
{
    double min;
    min = v[0];
    for (int i = 1; i < v.size(); i++)
    {
        if (v[i] < min)
            min = v[i];
    }
    cout << scientific;
    cout << "Min of vector: " << min << endl;
}

void get_vec_max(const vector<double> &v)
{
    double max;
    max = v[0];
    for (int i = 1; i < v.size(); i++)
    {
        if (v[i] > max)
            max = v[i];
    }
    cout << scientific;
    cout << "Max of vector: " << max << endl;
}

void get_vec_avg(const vector<double> &v)
{
    double sum;
    sum = v[0];
    for (int i = 1; i < v.size(); i++)
    {
        sum += v[i];
    }
    cout << scientific;
    cout << "Avg of vector: " << sum / v.size() << endl;
}
