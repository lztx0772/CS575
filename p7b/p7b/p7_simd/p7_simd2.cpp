#include <omp.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "simd.p5.h"

#define NUMT 1
#define SIZE 32768
#define NUMTRIES 2 

float Array[2*SIZE];
float  Sums[1*SIZE];

int
main()
{//read signal.txt 
        int Size;
        FILE* fp;
        int i;
        fp = fopen( "signal.txt", "r" );
        if( fp == NULL )
        {
                fprintf( stderr, "Cannot open file 'signal.txt'\n" );
                exit( 1 );
        }
        fscanf( fp, "%d", &Size );
        Size = SIZE;
        for( i = 0; i < Size; i++ )
        {
                fscanf( fp, "%f", &Array[i] );
                Array[i+Size] = Array[i];               // duplicate the array
        }
        fclose( fp );

//openmp
#ifndef _OPENMP
        fprintf( stderr, "OpenMP is not supported here -- sorry.\n" );
        return 1;
#endif

        omp_set_num_threads( NUMT );
        fprintf( stderr, "Using %d threads\n", NUMT );

        double maxMegaMults = 0.;
        double sumMegaMults = 0.;

        for( int t = 0; t < NUMTRIES; t++ )
        {
                double time0 = omp_get_wtime( );

                for( int shift = 0; shift < Size; shift++ )
                {
                        #pragma omp parallel
                        {
                            Sums[shift] = SimdMulSum( &Array[0], &Array[0+shift], Size );
                        }
                }

                double time1 = omp_get_wtime( );
                double megaMults = (double)Size*Size/(time1-time0)/1000000.;
                sumMegaMults += megaMults;
                if( megaMults > maxMegaMults )
                        maxMegaMults = megaMults;
        }

        double avgMegaMults = sumMegaMults/(double)NUMTRIES;
        printf( "   Peak Performance = %8.2lf MegaMults/Sec\n", maxMegaMults );
        printf( "Average Performance = %8.2lf MegaMults/Sec\n", avgMegaMults );

	// note: %lf stands for "long float", which is what printf calls a "double"
	//        %d stands for "decimal integer", not "double"

        for(int j = 1; j < 513; j++)
                printf("Sum[%d] = %f\n", j, Sums[j] );

        return 0;
}

