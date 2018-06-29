#include <omp.h>
#include <stdio.h>
#include <math.h>
#include "simd.p5.h"

//#define ARRAYSIZE       1000  // 1K to 32K
#define NUMTRIES        10  // you decide
#define NUMT    1

float* A;
float* B;
float* C;

int
main()
{

    #ifndef _OPENMP
        fprintf( stderr, "OpenMP is not supported here -- sorry.\n" );
        return 1;
    #endif

        omp_set_num_threads( NUMT );
        fprintf( stderr, "Using %d threads\n", NUMT );

        for(int iter = 0; iter < 16; iter++){
            int ARRAYSIZE = pow(2, iter) *1000;
            A = (float*)malloc(ARRAYSIZE*sizeof(float));
            B = (float*)malloc(ARRAYSIZE*sizeof(float));
            C = (float*)malloc(ARRAYSIZE*sizeof(float));

            double maxMegaMults = 0.;
            double sumMegaMults = 0.;
            for( int t = 0; t < NUMTRIES; t++ )
            {
                    double time0 = omp_get_wtime( );
                    double sum = 0;

                    #pragma omp parallel
                    {
                    for( int i = 0; i < ARRAYSIZE; i++ )
                    {
                           sum += A[i] * B[i];
                            //SimdMul(    A, B,  C, ARRAYSIZE );
                    }
                    }
                    
                    double time1 = omp_get_wtime( );
                    double megaMults = (double)ARRAYSIZE/(time1-time0)/1000000.;
                    sumMegaMults += megaMults;
                    if( megaMults > maxMegaMults )
                            maxMegaMults = megaMults;
            }

            double avgMegaMults = sumMegaMults/(double)NUMTRIES;
            printf( "ARRAYSIZE: %d   Peak Performance = %8.2lf MegaMults/Sec\n", ARRAYSIZE, maxMegaMults );
            printf( "ARRAYSIZE: %d Average Performance = %8.2lf MegaMults/Sec\n", ARRAYSIZE, avgMegaMults );

    // note: %lf stands for "long float", which is what printf calls a "double"
    //        %d stands for "decimal integer", not "double"

    }
        return 0;
}

