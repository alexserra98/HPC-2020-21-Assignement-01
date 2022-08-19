#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <mpi.h>
#include<time.h>
#define nproc 5
struct coord{
  int x[2];
  int y[2];
  int z[2];
}coord;
/* Function Implementation*/
void indecs(int* arr, const int n, const int num_proc){
    int div = n/num_proc;
    int rem = n%num_proc;
    arr[0]=0;
    int i=1;
    for(int i = 1; i <= (num_proc); i++) arr[i]= arr[i-1]+div;
    arr[num_proc] += rem;
}
void coordgen1d(struct coord  my_coords[100], int* arr, int np, int dimz, int dimy){
  unsigned int count=0;
  for(unsigned int i=0; i< np; i++){
    my_coords[count].z[0]=0;
    my_coords[count].z[1]=dimz;
    my_coords[count].x[0]=arr[i];
    my_coords[count].x[1]=arr[i+1];
    my_coords[count].y[0]=0;
    my_coords[count].y[1]=dimy;
    count++;
  }
}
void coordgen2d(struct coord  my_coords[100], int* arr, int* arr1, int nx,int ny, int dimz){
  unsigned int count=0;
  for(unsigned int i=0; i< ny; i++){
    for (unsigned int k=0; k<nx; k++) {
      my_coords[count].z[0]=0;
      my_coords[count].z[1]=dimz;
      my_coords[count].x[0]=arr[k];
      my_coords[count].x[1]=arr[k+1];
      my_coords[count].y[0]=arr1[i];
      my_coords[count].y[1]=arr1[i+1];
      count++;
    }
  }
}
void coordgen3d(struct coord  my_coords[500], int* arr, int* arr1,int* arr2, int nx, int ny, int nz){
  unsigned int count=0;
  for(unsigned int j=0; j<nx; j++){
    for(unsigned int i=0; i< ny; i++){
      for (unsigned int k=0; k<nz; k++) {
        my_coords[count].z[0]=arr2[j];
        my_coords[count].z[1]=arr2[j+1];
        my_coords[count].x[0]=arr[k];
        my_coords[count].x[1]=arr[k+1];
        my_coords[count].y[0]=arr1[i];
        my_coords[count].y[1]=arr1[i+1];
        count++;
      }
    }
  }
}
void mapping( struct coord  my_coords, int * arr, int ***mat){
  int x0 = my_coords.x[0]; int x1 = my_coords.x[1];
  int y0 = my_coords.y[0]; int y1 = my_coords.y[1];
  int z0 = my_coords.z[0]; int z1 = my_coords.z[1];
  unsigned int count = 0;
  for(int i=x0;i<x1; i++){
    for (int k=y0;k<y1; k++){
      for (int j=z0;j<z1; j++){
	arr[count]=mat[i][k][j];
	count++;
      }
    }
  }
}
void inverse_mapping( struct coord  my_coords, int * arr, int ***mat, int k, int dimension){
  int x0 = my_coords.x[0]; int x1 = my_coords.x[1];
  int y0 = my_coords.y[0]; int y1 = my_coords.y[1];
  int z0 = my_coords.z[0]; int z1 = my_coords.z[1];
  unsigned int count = k*dimension;
  for(int i=x0;i<x1; i++){
    for (int k=y0;k<y1; k++){
      for (int j=z0;j<z1; j++){
	mat[i][k][j]=arr[count];
	count++;
      }
    }
  }
}
