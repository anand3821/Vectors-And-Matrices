/* Java program for Sudoku generator  */

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class SudokuDS
{

    int[] mat[];
    int N; // number of columns/rows.
    int SRN; // square root of N
    int K; // No. Of missing digits

    // Constructor
    SudokuDS(int N, int K)
    {
        this.N = N;
        this.K = K;

        // Compute square root of N
        Double SRNd = Math.sqrt(N);
        SRN = SRNd.intValue();

        mat = new int[N][N];
    }

    // Sudoku Generator
    public void fillValues()
    {
        setUpGUI();
    }


    // Fill the diagonal SRN number of SRN x SRN matrices
    void fillDiagonal()
    {
        for (int i = 0; i<N; i=i+SRN)
            // for diagonal box, start coordinates->i==j
            fillBox(i, i);
    }

    // Returns false if given 3 x 3 block contains num.
    boolean unUsedInBox(int rowStart, int colStart, int num)
    {
        for (int i = 0; i<SRN; i++)
            for (int j = 0; j<SRN; j++)
                if (mat[rowStart+i][colStart+j]==num)
                    return false;
        return true;
    }

    // Fill a 3 x 3 matrix.
    void fillBox(int row,int col) {
        int num;
        for (int i = 0; i < SRN; i++) {
            for (int j = 0; j < SRN; j++) {
                do {
                    num = randomGenerator(N);
                }
                while (!unUsedInBox(row, col, num));

                mat[row + i][col + j] = num;
            }
        }
    }

    // Random generator
    int randomGenerator(int num)
    {
        return (int) Math.floor((Math.random()*num+1));
    }

    // Check if safe to put in cell
    boolean CheckIfSafe(int i,int j,int num)
    {
        return (unUsedInRow(i, num) &&
                unUsedInCol(j, num) &&
                unUsedInBox(i-i%SRN, j-j%SRN, num));
    }

    // check in the row for existence
    boolean unUsedInRow(int i,int num)
    {
        for (int j = 0; j<N; j++)
            if (mat[i][j] == num)
                return false;
        return true;
    }

    // check in the row for existence
    boolean unUsedInCol(int j,int num)
    {
        for (int i = 0; i<N; i++)
            if (mat[i][j] == num)
                return false;
        return true;
    }

    // A recursive function to fill remaining
    // matrix
    boolean fillRemaining(int i, int j)
    {
        //  System.out.println(i+" "+j);
        if (j>=N && i<N-1)
        {
            i = i + 1;
            j = 0;
        }

        if (i>=N && j>=N)
            return true;

        if (i < SRN)
        {
            if (j < SRN)
                j = SRN;
        }

        else if (i < N-SRN)
        {
            if (j==(int)(i/SRN)*SRN)
                j =  j + SRN;
        }

        else
        {
            if (j == N-SRN)
            {
                i = i + 1;
                j = 0;
                if (i>=N)
                    return true;
            }
        }

        for (int num = 1; num<=N; num++)
        {
            if (CheckIfSafe(i, j, num))
            {
                mat[i][j] = num;
                if (fillRemaining(i, j+1))
                    return true;

                mat[i][j] = 0;
            }
        }
        return false;
    }

    // Remove the K no. of digits to
    // complete game
    public void removeKDigits()
    {
        int count = K;
        while (count != 0)
        {
            int cellId = randomGenerator(N*N)-1;
            // System.out.println(cellId);
            // extract coordinates i  and j
            int i = (cellId/N);
            int j = cellId%9;
            if (j != 0)
                j = j - 1;
            // System.out.println(i+" "+j);
            if (mat[i][j] != 0) {
                count--;
                mat[i][j] = 0;
            }
        }
    }

    // Print sudoku
    public void printSudoku()
    {
        for (int i = 0; i<N; i++)
        {
            for (int j = 0; j<N; j++)
                System.out.print(mat[i][j] + " ");
            System.out.println();
        }
        System.out.println();
    }

    JFrame f  = new JFrame();
    static int i=0;
    public void setUpGUI(){
        f.setSize(800,800);
        f.setLayout(null);
        f.setVisible(true);
        JLabel h = new JLabel("Sudoku Generator ");
        h.setBounds(100,100,200,50);
        h.setFont(new Font("",Font.BOLD,20));
        f.add(h);
        JButton b = new JButton("NEXT");
        b.setBounds(100,200,100,20);
        f.add(b);
        JTextArea t = new JTextArea();
        t.setBounds(100,300,300,250);
        t.setBackground(Color.ORANGE);
        f.add(t);
        b.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                if(i==0){
                    t.setText("\n\tAfter Filling Diagonals:\n\t");
                    fillDiagonal();
                    for(int i=0;i<N;i++){
                        for(int j=0;j<N;j++){
                            t.append(String.valueOf(mat[i][j])+"  ");
                        }t.append("\n\t");
                    }
                    i++;
                }
                else if(i==1){
                    t.setText("\n\tAfter Filling remaining\n\t");
                    fillRemaining(0,SRN);
                    for(int i=0;i<N;i++){
                        for(int j=0;j<N;j++){
                            t.append(String.valueOf(mat[i][j])+"  ");
                        }t.append("\n\t");
                    }
                    i++;
                }
                else if(i==2){
                    t.setText("\n\tAfter removing K digits\n\t");
                    removeKDigits();
                    for(int i=0;i<N;i++){
                        for(int j=0;j<N;j++){
                            if(mat[i][j]!=0)
                            t.append(String.valueOf(mat[i][j])+"  ");
                            else t.append("_  ");
                        }t.append("\n\t");
                    }
                    i++;
                }
                else t.setText("\n\tCompleted!");
            }
        });
    }

    // Driver code
    public static void main(String[] args)
    {
        int N = 9, K = 20;
        SudokuDS sudoku = new SudokuDS(N, K);
        sudoku.fillValues();
    }
}