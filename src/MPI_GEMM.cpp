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
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD,&world_size);
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD,&world_rank);
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name,&name_len);
    if(world_rank==0)
    {
        int M_N_K[3];int &M=M_N_K[0];int &N=M_N_K[1];int &K=M_N_K[2];
        if(argc==4)
        {
            M=atoi(argv[1]);
            N=atoi(argv[2]);
            K=atoi(argv[3]);
        }
        else
        {
            printf("please input M N K:");
            scanf("%d %d %d",&M,&N,&K);
        }
        int fix_M=ceil(M/(double)world_size)*world_size; //使得行数是进程数的整数倍，拓展的行用0补充。方便给每个核平均分配行。
        int **A=create_matrix(fix_M,N);
        int **B=create_matrix(N,K);
        int **C=create_matrix(fix_M,K);
        init_matrix(M,N,A);
        memset(A[M],0,sizeof(int)*(fix_M-M)*N);
        init_matrix(N,K,B);
        timer.begin();
        int wn=(fix_M/world_size); // wn是各个进程实际需要计算的行数
        // 发送3个参数以及矩阵A,B
        for(int d=1;d<world_size;d++)
        {
            int temp=M;
            M=wn;
            MPI_Send(M_N_K,3,MPI_INT,d,0,MPI_COMM_WORLD);
            M=temp; // //实际发送到其他核的M值是其他核需要算的行数，不是fix_M,也不是真正的M。
            MPI_Send(A[d*wn],wn*N,MPI_INT,d,1,MPI_COMM_WORLD);
            MPI_Send(B[0],N*K,MPI_INT,d,2,MPI_COMM_WORLD);
        }
        // 计算自己要算的那部分
        for(int i=0;i<wn;i++)
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
        //接收其他进程算的那部分到相应的位置
        for(int d=1;d<world_size;d++)
        {
            MPI_Recv(C[d*wn],wn*K,MPI_INT,d,3,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        }
        auto cost=timer.end_ns();
        
        // cout<<"A"<<endl;
        // print_matrix(A,M,N);
        // cout<<"B"<<endl;
        // print_matrix(B,N,K);
        // cout<<"C"<<endl;
        // print_matrix(C,M,K);
        
        printf("%d %d %lld\n",M,world_size,cost/1000000);
    }
    else
    {
        int M_N_K[3];int &M=M_N_K[0];int &N=M_N_K[1];int &K=M_N_K[2];
        MPI_Recv(M_N_K,3,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        int **A=create_matrix(M,N);
        int **B=create_matrix(N,K);
        int **C=create_matrix(M,K);
        //cout<<"process_rank"<<world_rank<<" mnk:"<<M<<" "<<N<<" "<<K<<endl;
        MPI_Recv(A[0],M*N,MPI_INT,0,1,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        MPI_Recv(B[0],N*K,MPI_INT,0,2,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
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
        MPI_Send(C[0],M*K,MPI_INT,0,3,MPI_COMM_WORLD);
    }
    MPI_Finalize();
    

    
}