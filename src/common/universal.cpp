#include<vector>
#include<cstdio>
using namespace std;
void universal(vector<vector<int>> &A,vector<vector<int>> &B,
               vector<vector<int>> &C)
{
    int m=A.size();
    int n=B.size();
    int k=C[0].size();
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<k;j++)
        {
            C[i][j]=0;
            for(int s=0;s<n;s++)
            {
                C[i][j]+=A[i][s]+B[s][j];
            }
        }
    }
}
void universal(int N, int **A, int **B, int **C)
{
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            C[i][j]=0;
            for(int s=0;s<N;s++)
            {
                C[i][j]+=A[i][s]+B[s][j];
            }
        }
    }
}

