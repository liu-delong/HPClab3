#include<iostream>
#include<algorithm>
#include<vector>
#include<cstdlib>
#include<ctime>
#include<cstdio>
using namespace std;
void init_matrix(vector<vector<int>> &A)
{
    srand(time(0));
    int m=A.size();
    int n=A[0].size();
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            A[i][j]=rand()%(1<<16);
        }
    }
}
static bool is_srand=false;
void init_matrix(int N,int** A)
{
    if(!is_srand)
    {
        srand(time(0));
        is_srand=true;
    }
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            A[i][j]=rand()%(1<<16);
        }
    }
}
void init_matrix(int M,int N,int **A)
{
    if(!is_srand)
    {
        srand(time(0));
        is_srand=true;
    }
    for(int i=0;i<M;i++)
    {
        for(int j=0;j<N;j++)
        {
            A[i][j]=rand()%(1<<4);
        }
    }
}
int** create_matrix(int N)
{
    int **A=new int*[N];
    int *matrix=new int[N*N];
    for(int i=0;i<N;i++)
    {
        A[i]=matrix+i*N;
    }
    return A;
}
int** create_matrix(int M,int N)
{
    int **A=new int*[M];
    int *matrix=new int[M*N];
    for(int i=0;i<M;i++)
    {
        A[i]=matrix+i*N;
    }
    return A;
}
void delete_matrix(int **A)
{
    delete A[0];
    delete A;
}

void print_matrix(vector<vector<int>> &A)
{
    int m=A.size();
    int n=A[0].size();
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            printf("%10d ",A[i][j]);
        }
        cout<<endl;
    }
}
void print_matrix(int **A,int N)
{
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            printf("%10d ",A[i][j]);
        }
        printf("\n");
    }
}
void print_matrix(int **A,int M,int N)
{
    for(int i=0;i<M;i++)
    {
        for(int j=0;j<N;j++)
        {
            printf("%10d ",A[i][j]);
        }
        printf("\n");
    }
}
void copy_matrix(int **src,int **dst,int N)
{
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            dst[i][j]=src[i][j];
        }
    }
}
void copy_matrix(int **src,int **dst,int M,int N)
{
    for(int i=0;i<M;i++)
    {
        for(int j=0;j<N;j++)
        {
            dst[i][j]=src[i][j];
        }
    }
}