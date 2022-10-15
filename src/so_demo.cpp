#include"matrix_multi.h"
int main()
{
    int **A=create_matrix(3,3);
    int **B=create_matrix(3,3);
    int **C=create_matrix(3,3);
    universal(3,A,B,C);
    Strassen(3,A,B,C);
    loop_expansion(3,A,B,C);
    CoppersmithWinograd(3,A,B,C);
}