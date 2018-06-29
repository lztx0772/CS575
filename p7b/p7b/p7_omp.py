import os
for t in [ 1, 2, 4, 8 ]:
	#print "NUMT = %d" % t
	cmd = "g++ -DNUMT=%d p7_omp.cpp -o p7_omp -lm -fopenmp" % ( t )
	os.system( cmd )
	cmd = "./p7_omp"
	os.system( cmd )