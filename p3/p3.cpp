#include <omp.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

//int NUMT = 1; //1,2,4;
//int NUMPAD = 0;// 0, 1, 2, 3, ..., 15
int NUMTRIES = 1; 
//int FIX = 0; //0 FIX#1. 1 FIX#2

struct s
{
	float value;
	int pad[NUMPAD];
} Array[4];


int main(){
	#ifndef _OPENMP
        fprintf( stderr, "OpenMP is not supported here -- sorry.\n" );
        return 1;
	#endif
	omp_set_num_threads( NUMT );
	fprintf( stderr, "Using %d threads\n", NUMT );

	double maxMegaPlus = 0.;

	const int SomeBigNumber = 100000000;	// keep < 2B
	double time0 = omp_get_wtime( );

	for( int t = 0; t < NUMTRIES; t++ )
	{
		if (0 == FIX)
		{
			#pragma omp parallel for
			for( int i = 0; i < 4; i++ )
			{
				unsigned int seed = 0;		// automatically private
				for( unsigned int j = 0; j < SomeBigNumber; j++ )
				{
					Array[ i ].value = Array[ i ].value + (float)rand_r( &seed );
				}
			}
		}else if (1 == FIX)
		{
			#pragma omp parallel for
			for( int i = 0; i < 4; i++ )
			{
				unsigned int seed = 0;		// automatically private
				float tmp = Array[i].value;
				for( unsigned int j = 0; j < SomeBigNumber; j++ )
				{
					tmp = tmp + (float)rand_r( &seed );
				}
				Array[ i ].value = tmp;
			}
		}
		
		double time1 = omp_get_wtime( );
		double MegaPlus = (double)(4*SomeBigNumber)/(time1-time0)/1000000.;

		if( MegaPlus > maxMegaPlus )
        	maxMegaPlus = MegaPlus;
	}

	printf( " Thread = %d, FIX# = %d, NUMPAD = %d, Peak Performance = %8.2lf MegaPlus/Sec\n", NUMT, FIX+1, NUMPAD, maxMegaPlus );

	return 0;
}

