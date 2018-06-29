#include <omp.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>  

const float GRAIN_GROWS_PER_MONTH =		8.0;
const float ONE_DEER_EATS_PER_MONTH =	0.5;

const float AVG_PRECIP_PER_MONTH =		6.0;	// average
const float AMP_PRECIP_PER_MONTH =		6.0;	// plus or minus
const float RANDOM_PRECIP =				2.0;	// plus or minus noise

const float AVG_TEMP =					50.0;	// average
const float AMP_TEMP =					20.0;	// plus or minus
const float RANDOM_TEMP =				10.0;	// plus or minus noise

const float MIDTEMP =					40.0;
const float MIDPRECIP =					10.0;

int	NowYear;		// 2017 - 2022
int	NowMonth;		// 0 - 11

float	NowPrecip;		// inches of rain per month
float	NowTemp;		// temperature this month
float	NowHeight;		// grain height in inches
int	NowNumDeer;		// number of deer in the current population
unsigned int seed;

int DeerHunting;

float SQR( float x );
float Ranf( unsigned int *seedp,  float low, float high );
void calTmpPrecip();
void GrainDeer();
void Grain();
void Watcher();
void MyAgent();

int 
main(){
	#ifndef _OPENMP
        fprintf( stderr, "OpenMP is not supported here -- sorry.\n" );
        return 1;
	#endif
	//omp_set_num_threads( NUMT );
//Starting values
    // starting date and time:
	NowMonth =    0;
	NowYear  = 2017;
	seed = 0;//(unsigned)time(NULL);
	calTmpPrecip();

	// starting state (feel free to change this if you want):
	NowNumDeer = 1;
	DeerHunting = 0;
	NowHeight =  1.;

	omp_set_num_threads( 4 );	// same as # of sections
	//fprintf( stderr, "Using %d threads\n", NUMT );


	#pragma omp parallel sections
	{
		#pragma omp section
		{
			GrainDeer( );
		}

		#pragma omp section
		{
			Grain( );
		}

		#pragma omp section
		{
			Watcher( );
		}

		#pragma omp section
		{
			MyAgent( );	// your own
		}
	}       // implied barrier -- all functions must return in order
	// to allow any of them to get past here
}

//float tempFactor = exp(   -SQR(  ( NowTemp - MIDTEMP ) / 10.  )   );

//float precipFactor = exp(   -SQR(  ( NowPrecip - MIDPRECIP ) / 10.  )   );

// NowHeight += tempFactor * precipFactor * GRAIN_GROWS_PER_MONTH;
// NowHeight -= (float)NowNumDeer * ONE_DEER_EATS_PER_MONTH;
void
GrainDeer()
{
	while( NowYear < 2023 )
	{
		// compute a temporary next-value for this quantity
		// based on the current state of the simulation:
		//float tempFactor = exp(   -SQR(  ( NowTemp - MIDTEMP ) / 10.  )   );
		//float precipFactor = exp(   -SQR(  ( NowPrecip - MIDPRECIP ) / 10.  )   );
		int tmpdeer = NowNumDeer;
		if(NowHeight > NowNumDeer)
			tmpdeer++;
		else if (NowHeight < NowNumDeer)
			tmpdeer--;

		// DoneComputing barrier:
		#pragma omp barrier
		//. . .
		if(tmpdeer - DeerHunting < 0)
			NowNumDeer = 0;
		else
			NowNumDeer = tmpdeer - DeerHunting;
		//		printf("deer  barrier #1\n");

		// DoneAssigning barrier:
		#pragma omp barrier
		//. . .

		// DonePrinting barrier:
		#pragma omp barrier
		//. . .
	}
}

void
Grain()
{
	while( NowYear < 2023 )
	{
		// compute a temporary next-value for this quantity
		// based on the current state of the simulation:
		float tempFactor = exp(   -SQR(  ( NowTemp - MIDTEMP ) / 10.  )   );
		float precipFactor = exp(   -SQR(  ( NowPrecip - MIDPRECIP ) / 10.  )   );
		// DoneComputing barrier:
		float tmpHeight;
		tmpHeight += tempFactor * precipFactor * GRAIN_GROWS_PER_MONTH;
		tmpHeight -= (float)NowNumDeer * ONE_DEER_EATS_PER_MONTH;

		if( tmpHeight < 0 )
			tmpHeight = 0;

		#pragma omp barrier
		//. . .
		//NowHeight += tempFactor * precipFactor * GRAIN_GROWS_PER_MONTH;
 		//NowHeight -= (float)NowNumDeer * ONE_DEER_EATS_PER_MONTH;
		NowHeight = tmpHeight;

		// DoneAssigning barrier:
		#pragma omp barrier
		//. . .

		// DonePrinting barrier:
		#pragma omp barrier
		//. . .
	}
}
void
Watcher()
{
	while( NowYear < 2023 )
	{
		// compute a temporary next-value for this quantity
		// based on the current state of the simulation:

		// DoneComputing barrier:
		#pragma omp barrier

		// DoneAssigning barrier:
		#pragma omp barrier
		// get new temp and precip
		printf("Year:%d,Month: %d,Height:%8.2lf,NumDeer: %d,Temp:%8.2lf,precip:%8.2lf,DeerHunting:%d \n", NowYear, NowMonth,NowHeight, NowNumDeer, NowTemp, NowPrecip, DeerHunting);
		if(NowMonth == 11){
			NowMonth = 0;
			NowYear++;
		}else
		{
			NowMonth++;
		}
		calTmpPrecip();
		// DonePrinting barrier:
		#pragma omp barrier
		//. . .
	}
}

void 
MyAgent(){
	while( NowYear < 2023 )
	{
		// compute a temporary next-value for this quantity
		// based on the current state of the simulation:
		int tmp = Ranf( &seed, 0, 100 );
		DeerHunting = 0;
		if(tmp % 3 == 0)
			DeerHunting = 1;
		if(tmp % 9 == 0)
			DeerHunting = 2;
		//int tmpNumDeer = NowNumDeer;

		//tmpNumDeer = tmpNumDeer - DeerHunting;
		
		//if(tmpNumDeer < 0)
		//	tmpNumDeer = 0;
		// DoneComputing barrier:
		#pragma omp barrier
		//printf("watcher  barrier #1\n");
		//NowNumDeer = tmpNumDeer;
		// DoneAssigning barrier:
		#pragma omp barrier
		// get new temp and precip

		// DonePrinting barrier:
		#pragma omp barrier
		//. . .
	}
}

void
calTmpPrecip()
{
	float ang = (  30.*(float)NowMonth + 15.  ) * ( M_PI / 180. );

	float temp = AVG_TEMP - AMP_TEMP * cos( ang );
	//unsigned int seed = 0;//(unsigned)time(NULL);
	NowTemp = temp + Ranf( &seed, -RANDOM_TEMP, RANDOM_TEMP );

	float precip = AVG_PRECIP_PER_MONTH + AMP_PRECIP_PER_MONTH * sin( ang );
	NowPrecip = precip + Ranf( &seed,  -RANDOM_PRECIP, RANDOM_PRECIP );
	if( NowPrecip < 0. )
		NowPrecip = 0.;
}

float
SQR( float x )
{
        return x*x;
}

float
Ranf( unsigned int *seedp,  float low, float high )
{
        float r = (float) rand_r( seedp );              // 0 - RAND_MAX

        return(   low  +  r * ( high - low ) / (float)RAND_MAX   );
}

/*
int
Ranf( unsigned int *seedp, int ilow, int ihigh )
{
        float low = (float)ilow;
        float high = (float)ihigh + 0.9999f;

        return (int)(  Ranf(seedp, low,high) );
}
*/