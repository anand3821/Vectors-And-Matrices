/* C++ program for Sudoku generator */
// Part 2 : Filling Diagonal Elements

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

      // Fill the diagonal SRN number of SRN x SRN matrices
      void fillDiagonal()
      {
            for (int i = 0; i < N; i = i + SRN)
            {

                  // for diagonal box, start coordinates->i==j
                  fillBox(i, i);
            }
      }

      // Returns false if given 3 x 3 block contains num.
      bool unUsedInBox(int rowStart, int colStart, int num)
      {
            for (int i = 0; i < SRN; i++)
            {
                  for (int j = 0; j < SRN; j++)
                  {
                        if (mat[rowStart + i][colStart + j] == num)
                        {
                              return false;
                        }
                  }
            }
            return true;
      }

      // Fill a 3 x 3 matrix.
      void fillBox(int row, int col)
      {
            int num;
            for (int i = 0; i < SRN; i++)
            {
                  for (int j = 0; j < SRN; j++)
                  {
                        do
                        {
                              num = randomGenerator(N);
                        } while (!unUsedInBox(row, col, num));
                        mat[row + i][col + j] = num;
                  }
            }
      }
      // Random generator
      int randomGenerator(int num)
      {

            int r = 1 + (rand() % num);
            return r;
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
      sudoku->fillDiagonal();
      sudoku->printSudoku();
      return 0;
}
