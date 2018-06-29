import os
for t in [ 1, 2, 4, 8, 16 ]:
	print "NUMT = %d" % t
	for s in [ 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192 ]:
		print "NUMNODES = %d" % s
		cmd = "g++ -DNUMNODES=%d -DNUMT=%d P1.cpp -o prog -lm -fopenmp" % ( s, t )
		os.system( cmd )
		cmd = "./prog"
		os.system( cmd )