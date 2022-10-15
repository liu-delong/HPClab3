#ifndef MATRIX_TOOL_H
#define MATRIX_TOOL_H
#include<vector>
using namespace std;
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