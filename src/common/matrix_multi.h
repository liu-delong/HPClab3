#ifndef MATRIX_MULTI_H
#define MATRIX_MULTI_H
#include <vector>
using namespace std;
void CoppersmithWinograd(int n,int** A,int **B,int** C);
void loop_expansion(int n,int **A,int **B,int **C);
int Strassen(int N, int **MatrixA, int **MatrixB, int **MatrixC);
void universal(int N, int **A, int **B, int **C);
void init_matrix(vector<vector<int>> &A);
void init_matrix(int N,int** A);
void init_matrix(int M,int N,int **A);
int** create_matrix(int N);
int** create_matrix(int M,int N);
void delete_matrix(int **A);
void print_matrix(vector<vector<int>> &A);
void print_matrix(int **A,int N);
void print_matrix(int **A,int M,int N);
void copy_matrix(int **src,int **dst,int N);
void copy_matrix(int **src,int **dst,int M,int N);
#endif