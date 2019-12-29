#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "../include/algorithm.h"
#include "../include/player.h"
#include "../include/board.h"

using namespace std;
//g++ source/board.cpp source/rules.cpp source/player.cpp source/algorithm_TA.cpp source/Minimax.cpp source/chain_reaction.cpp


int score(Board board, Player player);
Board pseudo_place_orb(Board board,Player player, int row, int col);
void best_node(Board, Player, int);
void QuickSort(int array[], int left, int right, int pos_x[], int pos_y[]);
int InsertionSort(int array[], int left, int right, int pos_x[], int pos_y[]);
void Partition(int array[], int left, int right, int &p_l, int &p_r, int pos_x[], int pos_y[]);

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
    
    //cin >> best_row;
    //cin >> best_col;
    int alpha = 10000;
    int beta = -10000;
    int pos_x[30], pos_y[30];
    for(int i = 0; i < 30; ++i)
    {
        pos_x[i] = i % 5;
        pos_y[i] = i % 6;
    }
    
    index[0] = best_row;
    index[1] = best_col;
    cin.get();
}

//
void minimax(Board board, Player &player, int depth, int &best_row, int &best_col, 
    int pos_x[], int pos_y[], int &alpha, int &beta)
{

    if(depth == 3)
    {
        best_row = pos_x[0];
        best_col = pos_y[0];
    }

    if(player.get_color() == 'r')
    {
        
    }
    else if(player.get_color() == 'b')
    {

    }
}

Board pseudo_place_orb(Board board, Player player, int row, int col)
{
    board.place_orb(row,col, &player);
    return board;
}

void best_node(Board board, Player player, int breadth)
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
                    return;
                ++array_idx;
            }
        }
    }
}


int score(Board board, Player me)
{
    
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
    if(enemy_cell == 0 && my_cell > 1)
        return 10000;
    if(my_cell == 0 && enemy_cell > 1)
        return -10000;
    
    return sc;
}
//descending order
int InsertionSort(int array[], int left, int right, int pos_x[], int pos_y[])
{
    int j;
    for (int i = left + 1; i <= right; ++i)
    {
        j = i;
        while (j > left && array[j] > array[j - 1])
        {
            swap(array[j - 1], array[j]);
            swap(pos_x[j-1],pos_x[j]);
            swap(pos_y[j-1],pos_y[j]);
            --j;
        }
    }
    return ((right - left) >> 1) + left;
}

// 3 - way partition + median of three + descending order
void Partition(int array[], int left, int right, int &p_l, int &p_r,int pos_x[], int pos_y[])
{
    int mid = (right - left) / 2 + left;
    if (array[mid] < array[right])
    {
        swap(array[mid], array[right]);
        swap(pos_x[mid], pos_x[right]);
        swap(pos_y[mid], pos_y[right]);
    }
    if (array[left] < array[right])
    {
        swap(array[left], array[right]);
        swap(pos_x[left], pos_x[right]);
        swap(pos_y[left], pos_y[right]);
    }   
    if (array[left] < array[mid])
    {
        swap(array[left], array[mid]);
        swap(pos_x[left], pos_x[mid]);
        swap(pos_y[left], pos_y[mid]);
    }

    p_l = left, p_r = left; // array[p_l] ~ array[p_r] == pivot value
    int p_idx = left;
    int pivot = array[left];
    int pivot_x = pos_x[left];
    int pivot_y = pos_y[left];

    for (int i = left + 1; i <= right; ++i)
    {
        if (array[i] > pivot)
        {
            int temp = array[i];
            array[i] = array[p_r + 1];
            array[p_r + 1] = pivot;
            array[p_l] = temp;

            int temp_x = pos_x[i];
            pos_x[i] = pos_x[p_r+1];
            pos_x[p_r + 1] = pivot_x;
            pos_x[p_l] = temp_x;

            int temp_y = pos_y[i];
            pos_y[i] = pos_y[p_r+1];
            pos_y[p_r + 1] = pivot_y;
            pos_y[p_l] = temp_y;

            ++p_l;
            ++p_r;
        }
        else if (array[i] == pivot)
        {
            swap(array[p_r + 1], array[i]);
            swap(pos_x[p_r + 1], pos_x[i]);
            swap(pos_x[p_r + 1], pos_y[i]);
            ++p_r;
        }
    }
}

void QuickSort(int array[], int left, int right, int pos_x[], int pos_y[])
{
    while (left < right)
    {
        if (right - left <= 4)
        {
            InsertionSort(array, left, right, pos_x, pos_y);
            break;
        }
        else
        {
            int p_l, p_r;
            Partition(array, left, right, p_l, p_r, pos_x, pos_y);
            // left part  size < right part size
            // recur for the smaller one which is left part
            if (p_l - left < right - p_r)
            {
                QuickSort(array, left, p_l - 1, pos_x, pos_y);
                left = p_r + 1;
            }
            else
            {
                QuickSort(array, p_r + 1, right, pos_x, pos_y);
                right = p_l - 1;
            }
        }
    }
}