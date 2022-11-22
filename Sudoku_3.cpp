/* C++ program for Sudoku generator */
// Part 3 : Filling Remaining Entries

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

      // Check if safe to put in cell
      bool CheckIfSafe(int i, int j, int num)
      {
            return (
                unUsedInRow(i, num) && unUsedInCol(j, num) && unUsedInBox(i - i % SRN, j - j % SRN, num));
      }

      // check in the row for existence
      bool unUsedInRow(int i, int num)
      {
            for (int j = 0; j < N; j++)
            {
                  if (mat[i][j] == num)
                  {
                        return false;
                  }
            }
            return true;
      }

      // check in the col for existence
      bool unUsedInCol(int j, int num)
      {
            for (int i = 0; i < N; i++)
            {
                  if (mat[i][j] == num)
                  {
                        return false;
                  }
            }
            return true;
      }

      // A recursive function to fill remaining matrix
      bool fillRemaining(int i, int j)
      {

            // To Jump to Next row if the row is filled
            if (j >= N && i < N - 1)
            {
                  i = i + 1;
                  j = 0;
            }

            // Completely Filled
            if (i >= N && j >= N)
            {
                  return true;
            }

            // Ignoring the Diagonal Boxes as they are filled
            if (i < SRN)
            {
                  if (j < SRN)
                  {
                        j = SRN;
                  }
            }

            else if (i < N - SRN)
            {
                  if (j == (int)(i / SRN) * SRN)
                  {
                        j = j + SRN;
                  }
            }

            else
            {
                  if (j == N - SRN)
                  {
                        i = i + 1;
                        j = 0;
                        if (i >= N)
                        {
                              return true;
                        }
                  }
            }

            // Filling the Boxes and Moving to next Box
            for (int num = 1; num <= N; num++)
            {
                  if (CheckIfSafe(i, j, num))
                  {
                        mat[i][j] = num;
                        if (fillRemaining(i, j + 1))
                        {
                              return true;
                        }
                        mat[i][j] = 0;
                  }
            }
            return false;
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
      sudoku->fillRemaining(0, 3);
      sudoku->printSudoku();
      return 0;
}
