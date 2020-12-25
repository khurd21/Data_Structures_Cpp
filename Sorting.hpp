//
//  Sorting.hpp
//  CustomLibraries
//
//  Created by Kyle Hurd on 11/15/2020.
//
//  Sorting algorithms include bubble sort, selection sort, insertion sort,
//  and quick sort.
//

#ifndef Sorting_hpp
#define Sorting_hpp

#include <iostream>

//**PRINT ARRAY**//
/* *
 *  Created by:  Kyle Hurd
 *  Modified:    12/18/2020
 *  Description: Displays the entire array from the base address
 *               to the last element.
 */
template <typename T, size_t size>
void printArray(const T (&array)[size]) {
    for (int i = 0; i < size; i++) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
}

//**SWAP**//
/* *
 *  Created by:  Kyle Hurd
 *  Modified:    11/20/2020
 *  Description: Swaps the two arguments that are passed into function.
 *               Ex. if x = 5 and y = -4, then x will become -4 and y will
 *               become 5. Values are swapped by reference.
 */
template <typename T>
void swap(T &x, T &y) {
    T temp = x;
    x = y;
    y = temp;
}

//**BUBBLE SORT**//
/* *
 *  Created by:  Kyle Hurd
 *  Modified:    11/24/2020
 *  Description: A bubble sort algorithm. I believe the proper method to this
 *               algorithm is to bubble the items left to right, where the ending
 *               point decreases over time. I found this counter-intuitive, so
 *               I wrote it as two counters (i, j) that both increment up, but compare
 *               the second for-loop against the size of the array minus the 'i' position.
 *               The time complexity seems to be the same as the normal Bubble Sort.
 *
 *               Best sorting time:  O(n)
 *               Worst sorting time: O(n^2)
 */
template <typename T, size_t size>
void bubbleSort(T (&array)[size]) {
    for (int i = 0; i < size - 1; ++i) {
        bool flag = false;
        for (int j = 0; j < size - i - 1; ++j) {
            if (array[j] > array[j+1]) {
                swap(array[j], array[j+1]);
                flag = true;
            }
        }
        if (flag == false) {
            break;
        }
    }
}

//**SELECTION SORT**//
/* *
 *  Created by:  Kyle Hurd
 *  Modified:    11/18/2020
 *  Description: A selection sort algorithm. This is very similar to bubble sort
 *               with the exception that it must iterate through two for-loops
 *               regardless of the content within the array.
 *
 *               Best sorting time:  O(n^2)
 *               Worst sorting time: O(n^2)
 */
template <typename T, size_t size>
void selectionSort(T (&array)[size]) {
    int id;
    for (int i = 0; i < size - 1; ++i) {
        id = i;
        for (int j = i + 1; j < size; ++j) {
            if (array[j] < array[id]) {
                id = j;
            }
        }
        swap(array[id], array[i]);
    }
}

//**INSERTION SORT**//
/* *
 *  Created by:  Kyle Hurd
 *  Modified:    11/26/2020
 *  Description: An insertion sort. The method behind this is to assume the
 *               size of the array is one (a sorted array) and each iteration
 *               add one to the size of the array (the unsorted portion). Then
 *               place the unsorted element into the appropriate position.
 *
 *               Best sorting time:  O(n)
 *               Worst sorting time: O(n^2)
 */
template <typename T, size_t size>
void insertionSort(T (&array)[size]) {
    for (int i = 0; i < size; ++i) {
        int id = array[i];
        int j  = i - 1;
        while (j > -1 && array[j] > id) {
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = id;
    }
}

//**PARTITION**//
template <typename T>
int partition(T array[], int low, int high) {
    
    int pivotPos = high;
    int pivotVal = low;
    for (int i = low; i < high; i++) {
        if (array[i] < array[pivotPos]) {
            swap(array[i], array[pivotVal++]);
        }
    }
    swap(array[pivotVal], array[pivotPos]);
    return pivotPos;
}

//**QUICK SORT**//
/* *
 *  Created by:  Kyle Hurd
 *  Modified:    12/18/2020
 *  Description: Has the ability to only sort specific sections of the
 *               array. For example, if you want to quick sort the entire array,
 *               simply write the function as 'quickSort(array)' ignoring the low
 *               and high ranges. If you want to sort a specific section exclusively,
 *               you can write the function as 'quickSort(array, low, high). By default
 *               low is the 0th element and high is the last element.
 */
template <typename T, size_t size>
void quickSort(T (&array)[size], int low=0, int high=size-1) {
    if (low < high) {
        int pivot = partition(array, low, high);
        quickSort(array, low, pivot - 1);
        quickSort(array, pivot + 1, high);
    }
}

#endif /* Sorting.hpp */
