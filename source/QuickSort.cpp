#include <iostream>
#include <chrono>
using namespace std::chrono;
using namespace std;

void QuickSort(int array[], int left, int right);
int InsertionSort(int array[], int left, int right);
void Partition(int array[], int left, int right, int &p_l, int &p_r);
void S_Partition(int array[], int left, int right, int &p_l, int &p_r);
void PrintArray(int array[], int length);
void BuildArray(int *array, int length);
int main()
{

    //int array[] = {2, -1, 0, 4, 2, 6, 8, 2, 2, 100, 200, 30, 49, 20, -7, -6};

    //int length = sizeof(array)/ sizeof(array[0]);
    
    int length = 20;
    int *array = new int[length];
    BuildArray(array, length);
    array[9] = 7;
    array[10] = 7, array[11] = 7,array[13] = 7, array[16] = 7;
    //array[19] = 7;
    int pos_x[20];
    for(int i = 0 ; i < length; ++i)
    {
        pos_x[i] = i % 5;
    }
    PrintArray(array, length);
    PrintArray(pos_x,length);
    cout << "0-------0" << endl;
    int i = 0;
    int j = 3;
    auto start = high_resolution_clock::now();
    //Partition(array,0,length-1, i ,j);
    //S_Partition(array,0,length-1, i ,j);
    //InsertionSort(array, 0, length - 1, pos_x);
    //QuickSort(array,0, length - 1);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << duration.count() << endl;

    for(int i = 0 ; i < length; ++i)
    {
        cout << pos_x[i] << ": " << array[i] << ", ";
    }
    cout << endl;
    //g++ -std=c++11 source/QuickSort.cpp
    return 0;
}

void BuildArray(int *array, int length)
{

    for (int i = 0; i < length; ++i)
        array[i] = i;
}
void PrintArray(int array[], int length)
{
    for (int i = 0; i < length; ++i)
        cout << array[i] << " ";
    cout << endl;
}
//descending order
int InsertionSort(int array[], int left, int right)
{
    int j;
    for (int i = left + 1; i <= right; ++i)
    {
        j = i;
        while (j > left && array[j] > array[j - 1])
        {
            swap(array[j - 1], array[j]);
            --j;
        }
    }
    return ((right - left) >> 1) + left;
}

// 3 - way partition + median of three + descending order
void Partition(int array[], int left, int right, int &p_l, int &p_r)
{
    int mid = (right - left) / 2 + left;
    if (array[mid] < array[right])
        swap(array[mid], array[right]);
    if (array[left] < array[right])
        swap(array[left], array[right]);
    if (array[left] < array[mid])
        swap(array[left], array[mid]);

    p_l = left, p_r = left; // array[p_l] ~ array[p_r] == pivot value
    int p_idx = left;
    int pivot = array[left];

    for (int i = left + 1; i <= right; ++i)
    {
        if (array[i] > pivot)
        {
            int temp = array[i];
            array[i] = array[p_r + 1];
            array[p_r + 1] = pivot;
            array[p_l] = temp;
            ++p_l;
            ++p_r;
        }
        else if (array[i] == pivot)
        {
            swap(array[p_r + 1], array[i]);
            ++p_r;
        }
    }
}

void QuickSort(int array[], int left, int right)
{
    while (left < right)
    {
        if (right - left <= 4)
        {
            InsertionSort(array, left, right);
            break;
        }
        else
        {
            int p_l, p_r;
            Partition(array, left, right, p_l, p_r);
            // left part  size < right part size
            // recur for the smaller one which is left part
            if (p_l - left < right - p_r)
            {
                QuickSort(array, left, p_l - 1);
                left = p_r + 1;
            }
            else
            {
                QuickSort(array, p_r + 1, right);
                right = p_l - 1;
            }
        }
    }
}