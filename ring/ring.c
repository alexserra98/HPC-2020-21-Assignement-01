#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int module(int n, int mod);
int main(int argc, char** argv) {
  // Initialize the MPI environment
  int msg1, msg2;
  int flag=0;
  int count =0;
  int clock=0;
  double t1,t2;
  double tsum=0;
  MPI_Init(NULL, NULL);
  // Find out rank, size
  t1 = MPI_Wtime();
  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);
  /************************** start of the loop********************* */
  while(count<1000*world_size){
     int tag = 10*count;
     int mcount = count%world_size;
    // Receiving from rx sending to lx
    if (world_rank != mcount) {
      MPI_Recv(&msg1, 1, MPI_INT, module(world_rank+1,world_size),tag , MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      // printf("Process %d received token1 %d  from process %d \n", world_rank, msg1,
      //	      module(world_rank+1,world_size) );
      msg1 += world_rank;  
    }
    else  msg1 = mcount;
    MPI_Send(&msg1, 1, MPI_INT, module(world_rank-1,world_size), tag, MPI_COMM_WORLD);
    if (world_rank ==mcount) {
      MPI_Recv(&msg1, 1, MPI_INT,module(world_rank+1,world_size) ,tag , MPI_COMM_WORLD,
	       MPI_STATUS_IGNORE);
      // printf("Process %d received  token1 %d from process %d\n", world_rank,msg1, module(world_rank+1,world_size));
    }   
    // Receiving from lx to rx
    if(world_rank !=mcount){
      MPI_Recv(&msg2, 1, MPI_INT, module(world_rank-1,world_size),tag , MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      // printf("Process %d received token2 %d from process %d \n", world_rank,msg2,
      //       module(world_rank-1,world_size) );
    msg2 -= world_rank;      
    }
    else  msg2= -mcount;
    MPI_Send(&msg2, 1, MPI_INT, module(world_rank+1,world_size), tag, MPI_COMM_WORLD);
    if (world_rank == mcount) {
    MPI_Recv(&msg2, 1, MPI_INT,module(world_rank-1,world_size) ,tag , MPI_COMM_WORLD,
           MPI_STATUS_IGNORE);
    // printf("Process %d received  token2 %d from process %d\n", world_rank,msg2, module(world_rank-1,world_size));
  }
    count++;
    MPI_Barrier(MPI_COMM_WORLD);
    if(world_rank==(mcount)) printf(" I am process %d and I have received np %d messages. My final messages have tag %d  and value msg-left %d, msg-right %d\n",world_rank,2*world_size,tag,msg1, msg2);
}
  /*********************** end of the loop *************************/
  MPI_Barrier(MPI_COMM_WORLD);
  t2=MPI_Wtime();
  tsum += t2-t1;
  printf("time elapsed is \n$%lf \n",tsum);
  MPI_Finalize();
  
}
int module(int n, int mod){
  int ret;
  if(n<0) ret=(n%(mod)) + mod;
  else ret = n%mod;
  return ret;
}
