import os
for s in [ 1, 2, 4, 8, 16, 32 ]: 
	#print "NUMT = %d" % t
	for t in [ 8, 16, 32, 64, 128, 256, 512 ]: #[ 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192 ]:local size
		#print "NUMNODES = %d" % s
		#cmd = "g++ -DNUMNODES=%d -DNUMT=%d P1.cpp -o prog -lm -fopenmp" % ( s, t )
		cmd = "g++ -DNMB=%d -DLOCAL_SIZE=%d first.cpp -o first /scratch/cuda-7.0/lib64/libOpenCL.so -lm -fopenmp" % ( s, t )
		os.system( cmd )
		cmd = "./first"
		os.system( cmd )