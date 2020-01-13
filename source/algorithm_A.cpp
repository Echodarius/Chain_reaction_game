#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "../include/algorithm.h"
#include "../include/player.h"

using namespace std;

/******************************************************
 * In your algorithm, you can just use the the funcitons
 * listed by TA to get the board information.(functions 
 * 1. ~ 4. are listed in next block)
 * 
 * The STL library functions is not allowed to use.
******************************************************/

/*************************************************************************
 * 1. int board.get_orbs_num(int row_index, int col_index)
 * 2. int board.get_capacity(int row_index, int col_index)
 * 3. char board.get_cell_color(int row_index, int col_index)
 * 4. void board.print_current_board(int row_index, int col_index, int round)
 * 
 * 1. The function that return the number of orbs in cell(row, col)
 * 2. The function that return the orb capacity of the cell(row, col)
 * 3. The function that return the color fo the cell(row, col)
 * 4. The function that print out the current board statement
*************************************************************************/

int dirs[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
int evaluate_board(Board board, char player_color, char my_color);
int** get_legal_moves(Board board, char player_color, int &move_number);
void Minimax(Board board, char player_color, char my_color,
    int index[], int depth, int alpha, int beta, int score);

void algorithm_A(Board board, Player player, int index[])
{

    // cout << board.get_capacity(0, 0) << endl;
    // cout << board.get_orbs_num(0, 0) << endl;
    // cout << board.get_cell_color(0, 0) << endl;
    // board.print_current_board(0, 0, 0);

    //////////// Random Algorithm ////////////
    // Here is the random algorithm for your reference, you can delete or comment it.

    int row, col;
    int mycolor = player.get_color();
    cin >> index[0];
    cin >> index[1];
    cin.get();
}

int evaluate_board(Board board, char player_color, char my_color)
{
    int sc = 0;
    int player_cell = 0, enemy_cell = 0;
    int nb_row = 0, nb_col = 0;
    int player_critical_cell = 0;
    int player_n_cont_cri_cell = 0; //my not contiguous critial cell

    if (player_color == my_color)
    {
        for (int i = 0; i < ROW; ++i)
        {
            for (int j = 0; j < COL; ++j)
            {
                if (board.get_cell_color(i, j) == my_color)
                {
                    player_cell += 1;
                    bool vulnerable = false;
                    //neighbor cell
                    for (int k = 0; k < 4; ++k)
                    {
                        nb_row = i + dirs[k][0];
                        nb_col = j + dirs[k][1];
                        if (0 <= nb_row && nb_row < ROW &&
                            0 <= nb_col && nb_col < COL)
                        {
                            if (board.get_cell_color(nb_row, nb_col) != my_color &&
                                board.get_capacity(nb_row, nb_col) == board.get_orbs_num(nb_row, nb_col) + 1)
                            {
                                sc -= 5 - board.get_orbs_num(nb_row, nb_col);
                                vulnerable = true;
                            }
                        }
                    }

                    if (!vulnerable)
                    {
                        if (board.get_capacity(i, j) == 2)
                            sc += 3;
                        else if (board.get_capacity(i, j) == 3)
                            sc += 2;
                        if (board.get_capacity(i, j) == board.get_orbs_num(i, j) + 1)
                            sc += 2;
                    }
                    if (board.get_capacity(i, j) == board.get_orbs_num(i, j) + 1)
                    {
                        ++player_critical_cell;
                        bool contiguous = false;
                        for (int k = 0; k < 4; ++k)
                        {
                            nb_row = i + dirs[k][0];
                            nb_col = j + dirs[k][1];
                            if (0 <= nb_row && nb_row < ROW && 0 <= nb_col && nb_col < COL &&
                                board.get_cell_color(nb_row, nb_col) == my_color &&
                                board.get_capacity(nb_row, nb_col) == board.get_orbs_num(nb_row, nb_col) + 1)
                            {
                                contiguous = true;
                                break;
                            }
                        }
                        if (contiguous == false)
                        {
                            ++player_n_cont_cri_cell;
                        }
                    }
                }
                else
                {
                    enemy_cell += 1;
                }
            }
        }
        sc += player_cell;
        if (enemy_cell == 0 && player_cell > 1)
            return 10000;
        if (player_cell == 0 && enemy_cell > 1)
            return -10000;
        sc += 2 * (player_critical_cell - player_n_cont_cri_cell);
        return sc;
    }
    else
    {
        for (int i = 0; i < ROW; ++i)
        {
            for (int j = 0; j < COL; ++j)
            {
                if (board.get_cell_color(i, j) == 'V')
                {
                    player_cell += 1;
                    bool vulnerable = false;
                    //neighbor cell
                    for (int k = 0; k < 4; ++k)
                    {
                        nb_row = i + dirs[k][0];
                        nb_col = j + dirs[k][1];
                        if (0 <= nb_row && nb_row < ROW &&
                            0 <= nb_col && nb_col < COL)
                        {
                            if (board.get_cell_color(nb_row, nb_col) != my_color &&
                                board.get_capacity(nb_row, nb_col) == board.get_orbs_num(nb_row, nb_col) + 1)
                            {
                                sc += 5 - board.get_orbs_num(nb_row, nb_col);
                                vulnerable = true;
                            }
                        }
                    }

                    if (!vulnerable)
                    {
                        if (board.get_capacity(i, j) == 2)
                            sc -= 3;
                        else if (board.get_capacity(i, j) == 3)
                            sc -= 2;
                        if (board.get_capacity(i, j) == board.get_orbs_num(i, j) + 1)
                            sc -= 2;
                    }
                    if (board.get_capacity(i, j) == board.get_orbs_num(i, j) + 1)
                    {
                        ++player_critical_cell;
                        bool contiguous = false;
                        for (int k = 0; k < 4; ++k)
                        {
                            nb_row = i + dirs[k][0];
                            nb_col = j + dirs[k][1];
                            if (0 <= nb_row && nb_row < ROW && 0 <= nb_col && nb_col < COL &&
                                board.get_cell_color(nb_row, nb_col) == my_color &&
                                board.get_capacity(nb_row, nb_col) == board.get_orbs_num(nb_row, nb_col) + 1)
                            {
                                contiguous = true;
                                break;
                            }
                        }
                        if (contiguous == false)
                        {
                            ++player_n_cont_cri_cell;
                        }
                    }
                }
                else
                {
                    enemy_cell += 1;
                }
            }
        }
        sc += player_cell;
        if (enemy_cell == 0 && player_cell > 1)
            return -10000;
        if (player_cell == 0 && enemy_cell > 1)
            return 10000;
        sc -= 2 * (player_critical_cell - player_n_cont_cri_cell);
        return sc;
    }
}

int** get_legal_moves(Board board, Player player, int &move_number)
{
    for(int i = 0; i < ROW; ++i)
    {
        for(int j = 0; j < COL; ++j)
        {
            if(board.get_cell_color(i,j) == player.get_color() ||
                board.get_cell_color(i,j) == 'w')
            {
                ++move_number;
            }
        }
    }

    if(move_number == 0)
        return nullptr;
    
    int** legal = new int*[move_number];
    for(int i = 0; i < move_number; ++i)
    {
        legal[i] = new int[2];
    }
    int k = 0;
    for(int i = 0; i < ROW; ++i)
    {
        for(int j = 0; j < COL; ++j)
        {
            if(board.get_cell_color(i,j) == player.get_color ||
                board.get_cell_color(i,j) == 'w')
            {
                legal[k][0] = i;
                legal[k][1] = j;
                if(k == move_number)
                {
                    return legal;
                }
                ++k;
            }
        }
    }
    return legal;
}

void Minimax(Board board, Player player, Player me, 
    int index[], int depth, int alpha, int beta, int score)
{

    int best_score = (player.get_color == me.get_color()) ? 10000 : -10000;

    if(depth == 3 || score == 10000 || score == -10000)
    {
        best_score = score;
        return;
    }

    int legal_move_number = 0;  
    int** legal = get_legal_moves(board, player, legal_move_number);

    int cur_pos[2];
    for(int i = 0; i < legal_move_number; ++i)
    {
        cur_pos[0] = legal[i][0];
        cur_pos[1] = legal[i][1];
        board.place_orb(cur_pos[0], cur_pos[1], &player);
        
        //Maximizer
        if(player.get_color() == me.get_color())
        {

        }
        //minimizer
        else
        {

        }

    }
}