# HPC-2020-21-Assignement-01

### Matrix
In this case the task was to write a program that generates randomly two matrix of equal dimension and sum them in parallell, the tricky part was that only collective operations could be used. My approach to the problem was to generate a set of coordinates for each of the subdomains and use them as key to map the matrix over a 1d dimensional array, the master process would then scatter the
