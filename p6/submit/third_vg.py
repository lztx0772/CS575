import os
for s in xrange(1,9):# xrange(1, 9): #[ 1, 2, 4, 8 ]: global size
	#print "NUMT = %d" % t
	for t in [32]:#xrange( 8, 256, 1 ): #[ 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192 ]:local size
		#print "NUMNODES = %d" % s
		#cmd = "g++ -DNUMNODES=%d -DNUMT=%d P1.cpp -o prog -lm -fopenmp" % ( s, t )
		cmd = "g++ -DNMB=%d -DLOCAL_SIZE=%d third.cpp -o third /scratch/cuda-7.0/lib64/libOpenCL.so -lm -fopenmp" % ( s, t )
		os.system( cmd )
		cmd = "./third"
		os.system( cmd )