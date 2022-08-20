all: mat1d.x mat2d.x mat3d.x

mat1d.x: mat.c funct.h 
	mpicc -o mat1d.x mat.c funct.h

mat2d.x: mat2d.c funct.h 
	mpicc -o mat2d.x mat2d.c funct.h

mat3d.x: mat3d.c funct.h 
	mpicc -o mat3d.x mat3d.c funct.h

clean: 
	rm mat3d.x mat2d.x mat1d.x