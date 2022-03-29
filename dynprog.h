#ifndef __DYNPROG_H__
#define __DYNPROG_H__

void SW_bottomUp(char*, char*, char**, int**, int, int);
void print_Seq_Align_X(char* X, char** P, int** H, int n, int m);
void print_Seq_Align_Y(char* Y, char** P, int** H, int n, int m);
void find_max_indices(int** H, int &n_ind, int &m_ind, int n, int m);
void print_Seq_Align_X_Callee(char* X, char** P, int** H, int n, int m, int n_ind, int m_ind);
void print_Seq_Align_Y_Callee(char* Y, char** P, int** H, int n, int m, int n_ind, int m_ind);
void SW_bottomUp_callee(char* X, char* Y, char** P, int** H, int n, int m, int n_ind, int m_ind);

void find_max_indices(char** H, int &n_ind, int &m_ind, int n, int m);


int max_p(int p1, int p2, int p3);


void memoized_SW(char*, char*, char**, int**, int, int);
void memoized_SW_AUX(char*, char*, char**, int**, int, int);


#endif
