import os
for g in [ 1, 2, 4, 8, 16 ]:
	#print "NUMT = %d" % t
	for l in [ 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192 ]:
		#print "NUMNODES = %d" % s
		#cmd = "g++ -DNUMNODES=%d -DNUMT=%d P1.cpp -o prog -lm -fopenmp" % ( s, t )
		cmd = "g++ -DNMB=%g -DLOCAL_SIZE=%l -o first first.cpp /scratch/cuda-7.0/lib64/libOpenCL.so -lm -fopenmp" % (g, l)
		os.system( cmd )
		cmd = "./first"
		os.system( cmd )