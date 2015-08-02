#ifndef SUDOKUSOLVER_H
#define SUDOKUSOLVER_H

#include <vector>
#include <unordered_set>

using namespace std;

class SudokuSolver
{
    bool FillNextCell(vector<vector<char>>& board,
                      vector<unordered_set<char>>& rowDigits,
                      vector<unordered_set<char>>& columnDigits,
                      vector<unordered_set<char>>& subsquareDigits,
                      vector<pair<int, int>>& tbds,
                      int tbdIndex)
    {
        if (tbdIndex < tbds.size())
        {
            int i = tbds[tbdIndex].first;
            int j = tbds[tbdIndex].second;
            
            // Calculate the available digits for nextCell.
            unordered_set<char> availableDigits({'1', '2', '3', '4', '5', '6', '7', '8', '9'});
            for (auto it = rowDigits[i].begin(); it != rowDigits[i].end(); it++)
            {
                availableDigits.erase(*it);
            }
            
            for (auto it = columnDigits[j].begin(); it != columnDigits[j].end(); it++)
            {
                availableDigits.erase(*it);
            }
            
            for (auto it = subsquareDigits[i/3*3 + j/3].begin(); it != subsquareDigits[i/3*3 + j/3].end(); it++)
            {
                availableDigits.erase(*it);
            }
            
            for (auto it = availableDigits.begin(); it != availableDigits.end(); it++)
            {
                // Assume that we set board[i][j] = *it and see whether it works.
                board[i][j] = *it;
                
                // Update rowDigits, columnDigits, and subsquareDigits.
                rowDigits[i].insert(*it);
                columnDigits[j].insert(*it);
                subsquareDigits[i/3*3 + j/3].insert(*it);
                if (FillNextCell(board, rowDigits, columnDigits, subsquareDigits, tbds, tbdIndex + 1))
                {
                    return true;
                }
                
                // Revert rowDigits, columnDigits, and subsquareDigits if *it doesn't work.
                rowDigits[i].erase(*it);
                columnDigits[j].erase(*it);
                subsquareDigits[i/3*3 + j/3].erase(*it);
            }
            
            board[i][j] = '.';
            return false;
        }
        
        return true;
    }
    
public:
    SudokuSolver()
    {
        
    }
    
    ~SudokuSolver()
    {
        
    }

    void solveSudoku(vector<vector<char>> &board) 
    {
        vector<unordered_set<char>> rowDigits(9);
        vector<unordered_set<char>> columnDigits(9);
        vector<unordered_set<char>> subsquareDigits(9);
        vector<pair<int, int>> tbds;
        
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                char ch = board[i][j];
                if ((ch >= '1') && (ch <= '9'))
                {
                    rowDigits[i].insert(ch);
                    columnDigits[j].insert(ch);
                    subsquareDigits[i/3*3 + j/3].insert(ch);
                }
                else
                {
                    tbds.push_back(move(pair<int, int>(i, j)));
                }
            }
        }
        
        FillNextCell(board, rowDigits, columnDigits, subsquareDigits, tbds, 0);
    }
};

#endif // SUDOKUSOLVER_H