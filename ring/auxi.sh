#! /bin/bash
module load openmpi-4.0.5+gnu-9.3.0 
module load openmpi-4.1.1+gnu-9.3.0 
 cd /u/dssc/zenocosini/assignement/1_ex
touch data.txt
for n in {3..90..1}
do
    mpirun -np $n ring_2.x 2>/dev/null | grep '\$' |  cut -c2- > tmp.txt
   
    ./aux.x $n
done

