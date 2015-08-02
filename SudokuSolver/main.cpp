#include <iostream>
#include <vector>
#include <string>
#include "SudokuSolver.h"

using namespace std;

void PrintSudokuBoard(vector<vector<char>>& board)
{
    cout << " ----------------------------------- " << endl;
    
    for (int i = 0; i < 9; i++)
    {
        cout << "| ";
        for (int j = 0; j < 9; j++)
        {
            cout.put(board[i][j]);
            cout << " | ";
        }
        cout << endl << " ----------------------------------- " << endl;
    }
}

int main()
{
	vector<string> strBoard({"..9748...","7........",".2.1.9...","..7...24.",".64.1.59.",".98...3..","...8.3.2.","........6","...2759.."});
    vector<vector<char>> board(9);
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            board[i].push_back(strBoard[i][j]);
        }
    }
    
    cout << "The unsolved Sudoku board is as below: " << endl;
    PrintSudokuBoard(board);
    
    SudokuSolver solution;
    solution.solveSudoku(board);
    
    cout << "The solution is as below: " << endl;
    PrintSudokuBoard(board);
    
	return 0;
}
