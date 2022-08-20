# HPC 2020/21 Assignement-01
This repository contains the work produced for the first assignement of  FHPC course 2021-2022 @ DSSC, Units. The main topic of the homework was to benchmark several application and perform some basic analysis over the performance of the mainframe Orfeo at Area Science Park in Trieste.
## Ring
This benchmark consisted in a message-passaging between processes disposed in a ring topology
## PingPong
The Intel pingpong benchmark. We used to observe the behavior of the message passagging as the size of the messages were increasing and testing several topologies of the processes. 
## Jacobi
Study of the performance of a program which solve the Jacobi equation over a lattice.
## Matrix
In this case the task was to write a program that generates randomly two matrix of equal dimension and sum them in parallell, the tricky part was that only collective operations could be used. My approach to the problem was to generate a set of coordinates for each of the subdomains and use them as key to map the matrix over a 1d dimensional array, the master process would then scatter it to the slave processes. Once the computations has been completed the result will be gathered in a receive buffer by the master process and the remapped in a 3d dimensional matrix.
In order to simplify the calculations I've assumed that the dimension of the matrix in each dimension was a multiple of number of process at disposal, a possible way to overcome this limitation could be adding a padding to each dimension in order to require a suitable dimension.
### Compile and Run
The /matrix folder contains a makefile, as regards running the code each program takes as input the number of process employed for each dimension.
More details and the analysis of the results of the benchmark can be found in the /report section.

