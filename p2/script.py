import os
for t in [ 1,2,4,6,8,10,12,14,16 ]:
	print "NUMT = %d" % t
	for s in [ 1, 4096 ]:
		print "CHUNKSIZE = %d" % s
		for k in [0, 1]:
			if(k == 0):
				print "STYPE = static"
			else:
				print "STYPE = dynamic"
			cmd = "g++ -DCHUNKSIZE=%d -DNUMT=%d -DNTYPE=%d p2.cpp -o prog -lm -fopenmp" % ( s, t, k )
			os.system( cmd )
			cmd = "./prog"
			os.system( cmd )