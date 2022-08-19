#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 #include <mpi.h>
#include<time.h>
#include "funct.h"

int main(int argc, char *argv[]) {

  int dimy, dimz, dimx,num_proc,num_proc1;
  int * arr;
  int * arr1;
  unsigned int count=0;
  // MPI_Comm vu;
  /* getting dimension from input */
  dimx = atoi(argv[1]);
  dimy = atoi(argv[2]);
  dimz = atoi(argv[3]);
  num_proc = atoi(argv[4]);
  num_proc1 = atoi(argv[5]);
  int size = dimx*dimy*dimz;
  int ***mat2;
  int ***mat1;
  /* num processer for each dimension */;
  struct coord * mycoord0;
  mycoord0 = (struct coord *)malloc(sizeof(coord)*(num_proc*num_proc1));
  /* arr initialization */
  arr = (int *)malloc(sizeof(int)*(num_proc+2));
  arr1 = (int *)malloc(sizeof(int)*(num_proc1+2));
  /* end arr initialization */
  /* getting indexes */
  indecs(arr, dimx, num_proc);
  indecs(arr1, dimy, num_proc1);
  int dimension=dimz*arr1[1]*arr[1]; 
  printf("funziono!");
  /* Start MPI */
  MPI_Init(NULL,NULL);
  double startime = MPI_Wtime();
  int rank; int csize;
  MPI_Comm_rank(MPI_COMM_WORLD,&rank);
  MPI_Comm_size(MPI_COMM_WORLD, &csize);
  printf("ola!!");
  int scattermsg[size];
  int scattermsg1[size];

  if(rank==0){
    count=0;
    /* mat1 initialization */
    mat1 = (int ***)malloc(sizeof(int**)*dimx);
    for (int i = 0; i < dimx; i++){
      mat1[i] = (int**)malloc(dimy*sizeof(int*));
      for (int j = 0; j < dimy; j++){
	mat1[i][j] = (int*)malloc(dimz*sizeof(int));
      }
    }
    for(int i = 0; i<dimx; i++){
      for(int k = 0; k<dimy; k++){
	for(int j = 0; j<dimz; j++){
	  mat1[i][k][j]= count ; //rand()%100;
	  count++;
	}
      }
    }
    /* end mat1 initialization */
    /* mat2 initialization */
    mat2 = (int ***)malloc(sizeof(int**)*dimx);
    count=0;
    for (int i = 0; i < dimx; i++){
      mat2[i] = (int**)malloc(dimy*sizeof(int*));
      for (int j = 0; j < dimy; j++){
	mat2[i][j] = (int*)malloc(dimz*sizeof(int));
      }
    }
    for(int i = 0; i<dimx; i++){
      for(int k = 0; k<dimy; k++){
	for(int j = 0; j<dimz; j++){
	  mat2[i][k][j]= count ; //rand()%100;
	  count++;
	}
      }
    }
    /* end mat2 initialization */
    /* slicing mat1 */
    unsigned int offset = 0;
    int *locarr0;
    locarr0 = (int *)malloc(sizeof(int)*(dimension+2));
    int locarrind=0;
    coordgen2d(mycoord0, arr,arr1, num_proc,num_proc1, dimz);
     for(int i=0; i<(num_proc*num_proc1); i++){
      mapping(mycoord0[i],locarr0, mat1);
      for(int k=offset; k<(offset+(dimz*arr1[1]*arr[1])); k++){
	if(k!=0) locarrind = k%dimension;
	else locarrind =k; 
	scattermsg[k]=locarr0[locarrind];
      }
      offset += dimz*arr1[1]*arr[1];
    }
    
     /* slicing mat2 */
    offset = 0;
    locarrind=0;
    for(int i=0; i< (num_proc*num_proc1); i++){
      mapping(mycoord0[i],locarr0, mat2);
      for(int k=offset; k<(offset+(arr1[1]*dimz*arr[1])); k++){
	if(k!=0) locarrind = k%dimension;
	else locarrind =k; 
	scattermsg1[k]=locarr0[locarrind];
      }
      offset += arr1[1]*dimz*arr[1];
    } 
    free(mat1);
    free(mat2);
  }
  int * loc = (int *)malloc(sizeof(int)*dimension);
  int * loc1 = (int *)malloc(sizeof(int)*dimension);
  int * result = (int *)malloc(sizeof(int)*dimension);
  MPI_Scatter(scattermsg,dimension,MPI_INT,loc,dimension,MPI_INT,0, MPI_COMM_WORLD);
  MPI_Scatter(scattermsg1,dimension,MPI_INT,loc1,dimension,MPI_INT,0, MPI_COMM_WORLD);
  MPI_Barrier(MPI_COMM_WORLD);
    for(int i= 0; i<dimension; i++){
      printf("elem %d of rank %d LOC: %d\n",i,rank, loc[i]);
      printf("elem %d of rank %d LOC1: %d\n",i,rank, loc1[i]);
      result[i]=loc[i]+loc1[i];
      printf("elem %d of rank %d RES: %d\n",i,rank, result[i]);
    }
    MPI_Barrier(MPI_COMM_WORLD);
    int * gathermsg;
    int ***resmat;
    if(rank==0)  gathermsg = (int *)malloc(sizeof(int)*(size+1));
    MPI_Gather(result,dimension, MPI_INT, gathermsg,dimension,MPI_INT,0,MPI_COMM_WORLD);
    MPI_Barrier(MPI_COMM_WORLD);
    if(rank==0){
      resmat = (int ***)malloc(sizeof(int**)*dimx);
      for (int i = 0; i < dimx; i++){
	resmat[i] = (int**)malloc(dimy*sizeof(int*));
	for (int j = 0; j < dimy; j++){
	  resmat[i][j] = (int*)malloc(dimz*sizeof(int));
	}
      }

      for(int i=0; i<size; i++)  printf("elem %d: %d\n",i,gathermsg[i]);
            for(int k=0; k<(num_proc*num_proc1); k++) {
	inverse_mapping(mycoord0[k], gathermsg,resmat, k ,dimension);
      }
	    for(int i=0; i<dimx; i++) { 
	      for(int k=0; k<dimy; k++){
		for(int t=0; t<dimz; t++){
		  printf("elem %d %d %d: %d\n",i,k,t,resmat[i][k][t]);
		}
	      }
	    }
    }

    double endtime= MPI_Wtime();
    double timelapsed= endtime-startime;
    printf("&Elapsed time is: %lf\n", timelapsed);
  MPI_Finalize();
  //  free(locarr0);
  // free(locarr);
  //  free(locarr1);
  return 0;
}
