/* C++ program for Sudoku generator */
// Part 1 : Generating a Base Matrix with all zero entries

#include <bits/stdc++.h>
using namespace std;

class Sudoku
{
public:
      int **mat;
      int N;   // number of columns/rows.
      int SRN; // square root of N
      int K;   // No. Of missing digits

      // Constructor
      Sudoku(int N, int K)
      {
            this->N = N;
            this->K = K;

            // Compute square root of N
            double SRNd = sqrt(N);
            SRN = (int)SRNd;
            mat = new int *[N];

            // Create a row for every pointer
            for (int i = 0; i < N; i++)
            {

                  // Note : Rows may not be contiguous
                  mat[i] = new int[N];

                  // Initialize all entries as false to indicate
                  // that there are no edges initially
                  memset(mat[i], 0, N * sizeof(int));
            }
      }

      // Print sudoku
      void printSudoku()
      {
            for (int i = 0; i < N; i++)
            {
                  for (int j = 0; j < N; j++)
                  {
                        cout << to_string(mat[i][j]) + " ";
                  }
                  cout << endl;
            }
            cout << endl;
      }
};

// Driver code
int main()
{
      int N = 9;
      int K = 20;
      Sudoku *sudoku = new Sudoku(N, K);
      sudoku->printSudoku();
      return 0;
}
