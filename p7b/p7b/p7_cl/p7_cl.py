import os
cmd = "g++ p7_cl.cpp -o p7_cl /scratch/cuda-7.0/lib64/libOpenCL.so -lm -fopenmp"
os.system( cmd )
cmd = "./p7_cl"
os.system( cmd )