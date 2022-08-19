# HPC-2020-21-Assignement-01
### Ring
This benchmark consisted in a message-passaging between processes disposed in a ring topology
### PingPong
The standard ping pong benchmark
### Jacobi

### Matrix
In this case the task was to write a program that generates randomly two matrix of equal dimension and sum them in parallell, the tricky part was that only collective operations could be used. My approach to the problem was to generate a set of coordinates for each of the subdomains and use them as key to map the matrix over a 1d dimensional array, the master process would then scatter it to the slave processes. Once the computations has been completed the result will be gathered in a receive buffer by the master process and the remapped in a 3d dimensional matrix.
In order to simplify the calculations I've assumed that the dimension of the matrix in each dimension was a multiple of number of process at disposal, a possible way to overcome this limitation could be adding a padding to each dimension in order to require a suitable dimension.

