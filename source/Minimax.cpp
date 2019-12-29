#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "../include/algorithm.h"

using namespace std;

class HeuristicBoard;
void Judge_Whose_Cell(char&, char&, int&, int&, int&);

void Minimax(Board board, Player player, int index[])
{
    /*
    1. If the board is a won game, the value is 10000.
    2. If the board is a lost game, the value is -10000.
    3. For every orb, for every enemy critical cell surrounding the orb, subtract 5 minus the critical mass of that cell from the value.
    4. In case that the orb has no critical enemy cells in its adjacent cells at all, add 2 to the value if it is an edge cell or 3 if it is a corner cell.
    5. In case that the orb has no critical enemy cells in its adjacent cells at all, add 2 to the value if the cell is critical.
    6. For every orb of the player's color, add 1 to the value.
    7. For every contiguous blocks of critical cells of the player's color, add twice the number of cells in the block to the score.
    */
    int best_row, best_col;
    char color = player.get_color();
    
    index[0] = best_row;
    index[1] = best_col;
}

int score(Board, Player);
Board pseudo_place_orb(Board,Player, int, int);
int* best_node(Board, Player, int);
void QuickSort(int array[], int left, int right);

Board pseudo_place_orb(Board board, Player player, int row, int col)
{
    board.place_orb(row,col, &player);
    return board;
}

int* best_node(Board board, Player player, int breadth)
{
    int* array = new int [ROW*COL];
    int array_idx = 0;
    for(int i = 0; i < ROW; ++i)
    {
        for(int j = 0; j < COL; ++j)
        {
            if(board.get_cell_color(i,j) == 'w' || 
                board.get_cell_color(i,j) == player.get_color())
            {
                int cur_score = score(pseudo_place_orb(board,player,i,j), player);
                array[array_idx] = cur_score;
                if(cur_score == 10000)
                    return array;
                ++array_idx;
            }
        }
    }

}


int score(Board board, Player me)
{
    if(board.win_the_game(me))
        return 10000;
    int sc = 0;
    int my_cell = 0, enemy_cell = 0;
    int nb_row = 0, nb_col = 0;
    for(int i = 0; i < ROW; ++i)
    {
        for(int j = 0; j < COL; ++j)
        {
            if(board.get_cell_color(i,j) == me.get_color())
            {
                my_cell += 1;
                bool vulnerable = false;
                //neighbor cell
                for(int k = 0; k < 4; ++k)
                {
                    nb_row = i + k;
                    nb_col = j + k;
                    if(0 <= nb_row && nb_row < ROW && 
                        0 <= nb_col && nb_col < COL)
                    {
                        if(board.get_cell_color(nb_row, nb_col) != me.get_color() &&
                        board.get_capacity(nb_row,nb_col) == board.get_orbs_num(nb_row,nb_col))
                        {
                            sc -= 5 - board.get_orbs_num(nb_row,nb_col);
                            vulnerable = true;
                        }
                    }
                }

                if(!vulnerable)
                {
                    if(board.get_capacity(i,j) == 2)
                        sc += 3;
                    else if(board.get_capacity(i,j) == 3)
                        sc += 2;
                    if(board.get_capacity(i,j) == board.get_orbs_num(i,j) + 1)
                        sc += 2;
                }

            }
            else
            {
                enemy_cell += 1;
            }
        }
    }
    sc += my_cell;

    if(my_cell == 0 && enemy_cell > 1)
        return -10000;
    

    
    return sc;

}

int abs(int a)
{
    if(a < 0)
    {
        return -a;
    }
    return a;
}
