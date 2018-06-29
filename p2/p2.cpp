#include <stdlib.h>
#include <string.h>

int ARRAYSIZE 32*1024;
int NUMT 4; // 1,2,4,6,8,10,12,14,16
int CHUNKSIZE = 4096; // 1, 4096
char STYPE[20] = "dynamic";
float Ranf( float low, float high );

int 
main()
{
	#ifndef _OPENMP
        fprintf( stderr, "OpenMP is not supported here -- sorry.\n" );
        return 1;
	#endif
    omp_set_num_threads( NUMT );
    strcat(STYPE, ",");
    strcat(STYPE, CHUNKSIZE);
    omp_set_schedule(STYPE);

    fprintf( stderr, "Using %d threads\n", NUMT );
	float *Array;
	Array = (float*)malloc(ARRAYSIZE*sizeof(float));
	Array[i] = Ranf( -1.f, 1.f ); 

	double time0 = omp_get_wtime( );
	
    #pragma omp parallel for schedule(runtime)
    for( int i = 0; i < ARRAYSIZE; i++ )
    {
    	float prod = 1;
    	for( int j = 0; j < i+1; j++)
    		prod*=Array[j];
	}

	double time1 = omp_get_wtime( );

	long int numMuled = (long int)ARRAYSIZE * (long int)(ARRAYSIZE+1) / 2;  // count of how many multiplications were done:
	fprintf( stderr, "Threads = %2d; ChunkSize = %5d; Scheduling=static ; MegaMults/sec = %10.2lf\n", NUMT, CHUNKSIZE, (double)numMuled/(time1-time0)/1000000. );

	return 0;
}

float
Ranf( float low, float high )
{
	float r = (float) rand();		// 0 - RAND_MAX

	return(   low  +  r * ( high - low ) / (float)RAND_MAX   );
}