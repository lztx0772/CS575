#include <stdio.h>

#define SIZE   32768
float Array[2*SIZE];
float  Sums[1*SIZE];

//. . .
int     Size;
//float * Array;
//float * Sums;
FILE *  fp;
int     i;
//. . .
fp = fopen( "signal.txt", "r" );
if( fp == NULL )
{
	fprintf( stderr, "Cannot open file 'signal.txt'\n" );
	exit( 1 );
}
fscanf( fp, "%d", &Size );
Size = SIZE;
//Array = (float *)malloc( 2 * Size * sizeof(float) );
//Sums  = (float *)malloc( 1 * Size * sizeof(float) );
for( i = 0; i < Size; i++ )
{
	fscanf( fp, "%f", &Array[i] );
	Array[i+Size] = Array[i];		// duplicate the array
}
fclose( fp );
