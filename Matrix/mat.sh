module load openmpi-4.0.5+gnu-9.3.0 
cd $PBS_O_WORKDIR
echo "Starting"
mpirun -np 24 mat2d.x 800 300 100 8 3 | grep "&" | cut -c19- > tmp.txt
./aux.x 1
echo " 1 completed"
mpirun -np 24 mat2d.x 1200 200 100 12 2 | grep "&" | cut -c19- > tmp.txt
./aux.x 2
echo "2 completed"
mpirun -np 24 mat2d.x 2400 100 100 12 2 | grep "&" | cut -c19- > tmp.txt
./aux.x 3
echo "3 completed"
mpirun -np 24 mat2d.x 1200 200 100 6 4 | grep "&" | cut -c19- > tmp.txt
./aux.x 4
echo "4 completed"
mpirun -np 24 mat2d.x 2400 100 100 6 4 | grep "&" | cut -c19- > tmp.txt
./aux.x 5
echo "5 completed"
mpirun -np 24 mat2d.x 800 300 100 4 6 | grep "&" | cut -c19- > tmp.txt
./aux.x 6
echo "6 completed"
mpirun -np 24 mat.x 2400 100 100 24  | grep "&" | cut -c19- > tmp.txt
./aux.x 7
echo "7 completed"
mpirun -np 24 mat3d.x 800 300 100 4 3 2 | grep "&" | cut -c19- > tmp.txt
./aux.x 8
echo "8 completed"
mpirun -np 24 mat3d.x  1200 200 100 6 2 2 | grep "&" | cut -c19- > tmp.txt
./aux.x 9
echo "9 completed"
mpirun -np 24 mat3d.x  2400 100 100 6 2 2 | grep "&" | cut -c19- > tmp.txt
./aux.x 10
echo "10 completed"
mpirun -np 24 mat3d.x  1200 100 100 3 4 2 | grep "&" | cut -c19- > tmp.txt
./aux.x 11
echo "11 completed"
mpirun -np 24 mat3d.x  2400 100 100 3 4 2 | grep "&" | cut -c19- > tmp.txt
./aux.x 12
echo "12 Completed"

echo "closing"
