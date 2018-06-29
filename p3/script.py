import os
for t in [ 1, 2, 4 ]:
#	print "NUMT = %d" % t
	for f in [ 0, 1 ]:
		#if f == 1:
		#	p = 0
		#	cmd = "g++ -DNUMPAD=%d -DNUMT=%d -DFIX=%d p3.cpp -o p3 -lm -fopenmp" % ( p, t, f )
		#	os.system( cmd )
		#	cmd = "./p3"
		#	os.system( cmd )
		#else :
		for p in range( 16 ):
		#		print "NUMPAD = %d" % p
			if f == 1: p = 0
			cmd = "g++ -DNUMPAD=%d -DNUMT=%d -DFIX=%d p3.cpp -o p3 -lm -fopenmp" % ( p, t, f )
			os.system( cmd )
			cmd = "./p3"
			os.system( cmd )