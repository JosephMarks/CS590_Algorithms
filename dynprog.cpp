#include <cstring>
#include <iostream>
#include <limits.h>

#include "dynprog.h"

using namespace std;


void find_max_indices(int** H, int &n_ind, int &m_ind, int n, int m) {
  //Set the max value initially to the first value we look at
  int maxVal = H[0][0];
  int max_n = 0;
  int max_m = 0;
  // For loops to iterate and set max values for indexes
  for (int i=0; i<n; i++) {
   for (int j=0; j<m; j++) {
     if (H[i][j] > maxVal) {
       maxVal = H[i][j];
       max_n = i;
       max_m = j;
     }
   }
  }
  n_ind = max_n;
  m_ind = max_m;
}
// Function to return maximum p value
int max_p(int p1, int p2, int p3) {
  // Initalize the maximum value to p1 initially
  int maxVal = p1;
  // create list of the three values to evaluate
  int numList[3] = {p1, p2, p3};
  // For loop to iterate through our list
  for (int i=1; i<3; i++) {
   // Conditional - if value is greater than current max, update
   if (numList[i] > maxVal) {
    maxVal = numList[i];
   }
  }
  //return the maximum value determined, integer
  return maxVal;
}

/*
 * Bottom up implementation of Smith-Waterman algorithm
 */

void SW_bottomUp(char* X, char* Y, char** P, int** H, int n, int m){
   // initialize 0s and '\0'
    for (int row = 0; row < n; row++) {
         for (int col = 0; col < m; col++) {
           H[row][col] = 0;
           P[row][col] = '\0';
         }
     }
     // Call the callee function from this caller helper function
     SW_bottomUp_callee(X, Y, P, H, n, m, n-1, m-1);
}
//Bottom up callee function for Smith-Waterman Algorithm
void SW_bottomUp_callee(char* X, char* Y, char** P, int** H, int n, int m, int n_ind, int m_ind) {
  //base case number 1
  if (n_ind == 0 || m_ind == 0) {
      return;
  }
    //recursive calls
    SW_bottomUp_callee(X, Y, P, H, n, m, n_ind -1, m_ind);
    SW_bottomUp_callee(X, Y, P, H, n, m, n_ind, m_ind -1);
    //initialize p values
    int P1 = 0;
    int P2 = 0;
    int P3 = 0;
  //conditional to check if equal, reward
  if (X[n_ind] == Y[m_ind]) {
      P1 = H[n_ind-1][m_ind-1]+2;  // hyperparamaters
      }
      else {
             P1 = H[n_ind-1][m_ind-1]-1;
      }
      P2 = H[n_ind-1][m_ind]-1;
      P3 = H[n_ind][m_ind-1]-1;
  //determine the maximum value, assign variable
  int maxP =  max_p(P1, P2, P3);
  //assign in matrix
  H[n_ind][m_ind] = maxP;
  
   if (H[n_ind][m_ind] == P1) {
     P[n_ind][m_ind] = 'd'; // top left (diagonal)
   } else if (H[n_ind][m_ind] == P2) {
         P[n_ind][m_ind] = 'u'; //up
   } else {
        P[n_ind][m_ind] = 'l'; // left
   }
}
/*
 * Top-down with memoization implementation of Smith-Waterman algorithm
 */
void memoized_SW(char* X, char* Y, char** P, int** H, int n, int m)
{
    //initialize p values
    int P1 = 0;
    int P2 = 0;
    int P3 = 0;
    // Initialize H and P Matrices
     for (int row = 0; row < n; row++) {
         for (int col = 0; col < m; col++) {
           H[row][col] = 0;
           P[row][col] = '\0';
         }
     }
     //for loop to iterate and compare values
     for (int i = 1; i < n; i++) {
       for (int j = 1; j < m; j++) {
         if (X[i] == Y[j]) {
         P1 = H[i-1][j-1]+2;  // hyperparamaters
         }
         else {
                P1 = H[i-1][j-1]-1;
         }
         P2 = H[i-1][j]-1;
         P3 = H[i][j-1]-1;
          
         H[i][j] = max_p(P1, P2, P3);

         if (H[i][j] == P1) {
          P[i][j] = 'd'; // top left (diagonal)

         } else if (H[i][j] == P2) {
          P[i][j] = 'u'; //up
         } else {
           P[i][j] = 'l'; //left
         }
       }
     }
}

// Print sequence X callee function - called by the caller
void print_Seq_Align_X_Callee(char* X, char** P, int** H, int n, int m, int n_ind, int m_ind){
       //Base case will go here
       
       if (n_ind < 0 || m_ind < 0) {
         return;
       }
       // Conditional if emopty
       if (P[n_ind][m_ind] == '\0') {
        return;
       }
        //If diagonal
        if (P[n_ind][m_ind] == 'd') {
         print_Seq_Align_X_Callee(X, P, H, n, m, n_ind-1, m_ind-1) ;
         cout << X[n_ind];
        }
        //if left
       else if (P[n_ind][m_ind] == 'l') {
         print_Seq_Align_X_Callee(X, P, H, n, m, n_ind, m_ind-1) ;
         cout << '-';
        }
       else {
         print_Seq_Align_X_Callee(X, P, H, n, m, n_ind-1, m_ind) ;
         cout << X[n_ind];
       }
    }
    //print sequence Y callee - called by caller
    void print_Seq_Align_Y_Callee(char* Y, char** P, int** H, int n, int m, int n_ind, int m_ind){
           //Base case will go here
           
           if (n_ind < 0 || m_ind < 0) {
             return;
           }
           // blank value
           if (P[n_ind][m_ind] == '\0') {
            return;
           }
            // Diagonal
            if (P[n_ind][m_ind] == 'd') {
             print_Seq_Align_Y_Callee(Y, P, H, n, m, n_ind-1, m_ind-1) ;
             cout << Y[n_ind];
            }
            //Left
           else if (P[n_ind][m_ind] == 'l') {
             print_Seq_Align_Y_Callee(Y, P, H, n, m, n_ind-1, m_ind) ;
               cout << Y[n_ind];

            }
           else {
             print_Seq_Align_Y_Callee(Y, P, H, n, m, n_ind, m_ind-1) ;
               cout << '-';
           }
        }
/*
 * Print X'
 */
void print_Seq_Align_X(char* X, char** P, int** H, int n, int m){
	
    //initialize
    int n_ind = 0;
    int m_ind = 0;
    //Let's get the max value
    find_max_indices(H, n_ind, m_ind, n, m);
    //Now we will print the X sequence
    print_Seq_Align_X_Callee(X,P,H,n,m,n_ind,m_ind);

    cout << endl;
}

/*
 * Print Y'
 */
void print_Seq_Align_Y(char* Y, char** P, int** H, int n, int m){
	
    //initialize
    int n_ind = 0;
    int m_ind = 0;
    //Let's get the max value
    find_max_indices(H, n_ind, m_ind, n, m);
    //Now lets print the Y sequence
    print_Seq_Align_Y_Callee(Y,P,H,n,m,n_ind,m_ind);

    cout << endl;
}
