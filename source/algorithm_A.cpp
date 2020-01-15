#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "../include/algorithm.h"

using namespace std;

int dirs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
int corner[4][2] = {{0, 0}, {0, COL - 1}, {ROW - 1, 0}, {ROW - 1, COL - 1}};
Player opponent(Board board, Player me);
Board psuedo_place_orb(Board board, Player &player, int i, int j);
int evaluate_board(Board board, char my_color, char enemy_color);
int **get_legal_moves(Board board, char player_color, int &move_number);
int Minimax(Board board, bool maximizer, Player me, Player enemy,
            int index[], int depth, int alpha, int beta);

void algorithm_A(Board board, Player player, int index[])
{
    Player enemy = opponent(board, player);
    int best_score = evaluate_board(board, player.get_color(), enemy.get_color());
    if (best_score == -10000 || best_score == 0)
    {
        for (int i = 0; i < 4; ++i)
        {
            if (board.get_cell_color(corner[i][0], corner[i][1]) == 'w')
            {
                index[0] = corner[i][0];
                index[1] = corner[i][1];
                //cin.get();
                return;
            }
        }
    }
    int legal_move_number = 0;
    int **legal = get_legal_moves(board, player.get_color(), legal_move_number);
    if (legal_move_number > 27)
    {
        if (board.get_capacity(index[0], index[1]) != board.get_orbs_num(index[0], index[1]) + 1)
        {
            for (int i = 0; i < 4; ++i)
            {
                if (board.get_cell_color(corner[i][0], corner[i][1]) == 'w')
                {
                    index[0] = corner[i][0];
                    index[1] = corner[i][1];
                    //cin.get();
                    return;
                }
            }
        }
        else
        {
            int nb_row, nb_col;
            for (int k = 0; k < 4; ++k)
            {
                nb_row = index[0] + dirs[k][0];
                nb_col = index[1] + dirs[k][1];
                if (0 <= nb_row && nb_row < ROW &&
                    0 <= nb_col && nb_col < COL)
                {
                    if (board.get_cell_color(nb_row, nb_col) == player.get_color() &&
                        board.get_capacity(nb_row, nb_col) == board.get_orbs_num(nb_row, nb_col) + 1)
                    {
                        index[0] = nb_row;
                        index[1] = nb_col;
                        //cin.get();
                        return;
                    }
                }
            }
        }
    }

    Minimax(board, true, player, enemy, index, 0, -10000, 10000);
    //cin.get();
}

Player opponent(Board board, Player me)
{
    char op_color = 'v';
    bool found = false;
    for (int i = 0; i < ROW; ++i)
    {
        for (int j = 0; j < COL; ++j)
        {
            if (board.get_cell_color(i, j) != 'w' && board.get_cell_color(i, j) != me.get_color())
            {
                op_color = board.get_cell_color(i, j);
                found = true;
                break;
            }
        }
        if (found == true)
        {
            break;
        }
    }
    Player op(op_color);
    return op;
}

int evaluate_board(Board board, char my_color, char enemy_color)
{
    int sc = 0;
    int my_cell = 0, enemy_cell = 0;
    int nb_row = 0, nb_col = 0;
    int my_critical_cell = 0;
    int my_n_cont_cri_cell = 0; //my not contiguous critial cell

    for (int i = 0; i < ROW; ++i)
    {
        for (int j = 0; j < COL; ++j)
        {
            if (board.get_cell_color(i, j) == my_color)
            {
                my_cell += 1;
                bool vulnerable = false;
                //neighbor cell
                for (int k = 0; k < 4; ++k)
                {
                    nb_row = i + dirs[k][0];
                    nb_col = j + dirs[k][1];
                    if (0 <= nb_row && nb_row < ROW &&
                        0 <= nb_col && nb_col < COL)
                    {
                        if (board.get_cell_color(nb_row, nb_col) == enemy_color &&
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
                    ++my_critical_cell;
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
                        ++my_n_cont_cri_cell;
                    }
                }
            }
            else if (board.get_cell_color(i, j) == enemy_color)
            {
                enemy_cell += 1;
            }
        }
    }
    sc += my_cell;
    if (enemy_cell == 0 && my_cell > 1)
        return 10000;
    if (my_cell == 0 && enemy_cell > 1)
        return -10000;
    sc += 2 * (my_critical_cell - my_n_cont_cri_cell);
    return sc;
}

int **get_legal_moves(Board board, char player_color, int &move_number)
{
    for (int i = 0; i < ROW; ++i)
    {
        for (int j = 0; j < COL; ++j)
        {
            if (board.get_cell_color(i, j) == player_color ||
                board.get_cell_color(i, j) == 'w')
            {
                ++move_number;
            }
        }
    }

    if (move_number == 0)
        return nullptr;

    int **legal = new int *[move_number];
    for (int i = 0; i < move_number; ++i)
    {
        legal[i] = new int[2];
    }
    int k = 0;
    for (int i = 0; i < ROW; ++i)
    {
        for (int j = 0; j < COL; ++j)
        {
            if (board.get_cell_color(i, j) == player_color ||
                board.get_cell_color(i, j) == 'w')
            {
                legal[k][0] = i;
                legal[k][1] = j;
                if (k == move_number)
                {
                    return legal;
                }
                ++k;
            }
        }
    }
    return legal;
}

Board psuedo_place_orb(Board board, Player &player, int i, int j)
{
    board.place_orb(i, j, &player);
    return board;
}

int Minimax(Board board, bool maximizer, Player me, Player enemy,
            int index[], int depth, int alpha, int beta)
{

    int best_score = evaluate_board(board, me.get_color(), enemy.get_color());

    if (depth == 3 || best_score == 10000 || best_score == -10000)
    {
        return best_score;
    }

    int legal_move_number = 0;
    int **legal;
    Board cur_board;

    //Maximizer turn = my turn
    if (maximizer)
    {
        legal = get_legal_moves(board, me.get_color(), legal_move_number);
        for (int i = 0; i < legal_move_number; ++i)
        {
            cur_board = psuedo_place_orb(board, me, legal[i][0], legal[i][1]);
            int score = Minimax(cur_board, false, me, enemy, index, depth + 1, alpha, beta);
            best_score = max(best_score, score);
            index[0] = legal[i][0];
            index[1] = legal[i][1];
            alpha = max(best_score, alpha);
            if (beta <= alpha)
            {
                break;
            }
        }
    }
    //minimizer, enemy turn
    else
    {
        legal = get_legal_moves(board, enemy.get_color(), legal_move_number);
        for (int i = 0; i < legal_move_number; ++i)
        {
            cur_board = psuedo_place_orb(board, enemy, legal[i][0], legal[i][1]);
            int score = Minimax(cur_board, true, me, enemy, index, depth + 1, alpha, beta);
            best_score = min(best_score, score);
            index[0] = legal[i][0];
            index[1] = legal[i][1];
            beta = min(best_score, beta);
            if (beta <= alpha)
            {
                break;
            }
        }
    }
    return best_score;
}