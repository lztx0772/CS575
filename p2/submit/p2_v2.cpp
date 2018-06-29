#include <omp.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

int ARRAYSIZE = 32*1024;
int NUMTRIES = 10;
//int NUMT = 4; // 1,2,4,6,8,10,12,14,16
//int CHUNKSIZE = 1; // 1, 4096
//int NTYPE = 1;//0 static; 1 dynamic
//omp_sched_t STYPE = omp_sched_static; // omp_sched_static
									//omp_sched_dynamic 
float Ranf( float low, float high );

int 
main()
{
	#ifndef _OPENMP
        fprintf( stderr, "OpenMP is not supported here -- sorry.\n" );
        return 1;
	#endif
    omp_set_num_threads( NUMT );
	omp_sched_t STYPE; // omp_sched_static
	
	/*					//omp_sched_dynamic
	if(NTYPE == 0)
		STYPE = omp_sched_static;
	else 
		STYPE = omp_sched_dynamic;
	*/
	//printf("DS:%d\n", NTYPE);
   // omp_set_schedule(STYPE, CHUNKSIZE);

    fprintf( stderr, "Using %d threads\n", NUMT );

    double maxMegaMults = 0.;
    float* Array;
	Array = (float*)malloc(ARRAYSIZE*sizeof(float));
	for(int i = 0; i < ARRAYSIZE; i++)
		Array[i] = Ranf( -1.f, 1.f );
    
    for( int t = 0; t < NUMTRIES; t++ ) //10 times tries
    {
		double time0 = omp_get_wtime( );
		float prod;

	if(NTYPE == 0){
	    #pragma omp parallel for shared(Array),private(prod),schedule(static, CHUNKSIZE)
	    for( int i = 0; i < ARRAYSIZE; i++ )
	    {
	    	prod = 1.;
	    	for( int j = 0; j < i+1; j++ )
	    		prod*=Array[j];
		}
	}else
	{
		#pragma omp parallel for shared(Array),private(prod),schedule(dynamic, CHUNKSIZE)
	    for( int i = 0; i < ARRAYSIZE; i++ )
	    {
	    	prod = 1.;
	    	for( int j = 0; j < i+1; j++ )
	    		prod*=Array[j];
		}
	}

		double time1 = omp_get_wtime( );
		long int numMuled = (long int)ARRAYSIZE * (long int)(ARRAYSIZE+1) / 2;  // count of how many multiplications were done:
		//fprintf( stderr, "Threads = %2d; ChunkSize = %5d; Scheduling = %s ; MegaMults/sec = %10.2lf\n", NUMT, CHUNKSIZE, (STYPE==omp_sched_static?"static":"dynamic"), (double)numMuled/(time1-time0)/1000000. );
		double MegaMults = (double)numMuled/(time1-time0)/1000000.;
		//printf( " %10.2lf ,\t", MegaMults );
		if( MegaMults > maxMegaMults )
	            maxMegaMults = MegaMults;
	}
	//printf("\n");
	printf( "Threads = %2d; ChunkSize = %5d; Scheduling = %s ; MegaMults/sec = %10.2lf\n", NUMT, CHUNKSIZE, (NTYPE == 0?"static":"dynamic"), maxMegaMults );

	return 0;
}

float
Ranf( float low, float high )
{
	float r = (float) rand();		// 0 - RAND_MAX

	return(   low  +  r * ( high - low ) / (float)RAND_MAX   );
}
