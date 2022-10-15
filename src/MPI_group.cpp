#include"js.h"
#include<mpi.h>
#include"matrix_tool.h"
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cmath>
#include<cstring>
using namespace std;
int main(int argc,char** argv)
{
    MPI_Init(NULL,NULL);
    int world_size;int world_rank;
    MPI_Comm_size(MPI_COMM_WORLD,&world_size);
    MPI_Comm_rank(MPI_COMM_WORLD,&world_rank);
    int **tA;int **B;int **tC;
    int arg[5];int &M=arg[0];int &N=arg[1];int &K=arg[2];int &oM=arg[3];int &fM=arg[4];
    /*
    M是工作进程要计算的矩阵A和C的行数，N是矩阵A的列数，K矩阵B的列数。
    oM是矩阵A本来应该的行数，
    fM是拓展后的矩阵A的行数（拓展矩阵A的行数是为了使得能够平均分给每个进程）
    */
    if(world_rank==0)
    {
        if(argc==4)
        {
            oM=atoi(argv[1]);
            N=atoi(argv[2]);
            K=atoi(argv[3]);
        }
        else
        {
            printf("please input M N K:");
            scanf("%d %d %d",&oM,&N,&K);
        }
        M=ceil(oM/(double)world_size);
        fM=M*world_size;
        
    }
    MPI_Bcast(arg,5,MPI_INT,0,MPI_COMM_WORLD);
    tA=create_matrix(fM,N);
    B=create_matrix(N,K);
    tC=create_matrix(fM,K);
    if(world_rank==0)
    {
        init_matrix(oM,N,tA);
        memset(tA[oM],0,sizeof(int)*(fM-oM)*N);
        init_matrix(N,K,B);
        timer.begin();
    }
    int **A;int **C;
    A=create_matrix(M,N);
    C=create_matrix(M,K);
    MPI_Scatter(tA[0],M*N,MPI_INT,A[0],M*N,MPI_INT,0,MPI_COMM_WORLD);
    MPI_Bcast(B[0],N*K,MPI_INT,0,MPI_COMM_WORLD);
    for(int i=0;i<M;i++)
    {
        for(int j=0;j<K;j++)
        {
            C[i][j]=0;
            for(int k=0;k<N;k++)
            {
                C[i][j]+=A[i][k]*B[k][j];
            }
        }
    }
    MPI_Gather(C[0],M*K,MPI_INT,tC[0],M*K,MPI_INT,0,MPI_COMM_WORLD);
    if(world_rank==0)
    {
        auto cost=timer.end_ns();
        printf("%d %d %lld\n",oM,world_size,cost/1000000);
    }
    MPI_Finalize();    
}