import os
for t in [ 1 ]:
	#print "NUMT = %d" % t
	cmd = "g++ -DNUMT=%d p7_simd2.cpp -o p7_simd2 -lm -fopenmp" % ( t )
	os.system( cmd )
	cmd = "./p7_simd2"
	os.system( cmd )