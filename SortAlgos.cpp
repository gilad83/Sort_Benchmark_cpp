//
// Created by gilad on 25/10/2020.
//

#include <random>
#include "SortAlgos.h"
/**
 * Base class *
 */
void SortAlgos::swap(std::vector<int> &numbers, int left, int right) {
    int temp;
    temp = numbers[left];
    numbers[left] = numbers[right];
    numbers[right] = temp;
}

/**
 * Sorts the array using Bubble Sort *
 */
void BubbleSort::sort(std::vector<int> &numbers) {
    int n = int(numbers.size());
    for (int i = 0; i < n-1; ++i) {
        // The last i elements are already in place
        for (int j = 0; j < n - i - 1; ++j) {
            if (numbers[j] > numbers[j + 1]) {
                swap(numbers, j, j + 1);
            }
        }
    }
}

/**
 * Sorts the array using Merge Sort
 */
void MergeSort::sort(std::vector<int> &numbers) {
    int n = int(numbers.size()) - 1;
    sortRecursive(numbers,0,n);
}
/** sortRecursive
 * Recursively cuts the array to two sub arrays
 * Than merged sub arrays in ascending order.
 */
void MergeSort::sortRecursive(std::vector<int> &numbers, int left, int right){
    if(left < right){
        int median = left + (right - left) / 2;
        sortRecursive(numbers, left, median);// subArray 1
        sortRecursive(numbers, median + 1, right);// subArray 2
        merge(numbers, left, median, right);
    }
}
/** merge
 * Merging the subArrays in ascending order.
 */
void MergeSort::merge(std::vector<int> &numbers, int left, int median, int right) {
    int firstArrSize = median - left + 1, secondArrSize = right - median;
    std::vector<int> first,second; // Create two subArrays

    for(int i = 0; i < firstArrSize; ++i) {
        first.push_back(numbers[left + i]);
    }
    for(int j = 0; j < secondArrSize; ++j) {
        second.push_back(numbers[median + 1 + j]);
    }
    int firstArrIndex = 0;
    int secondArrIndex = 0;
    int mergedArray = left;
    while (firstArrIndex < firstArrSize && secondArrIndex < secondArrSize){
        if (first[firstArrIndex] <= second[secondArrIndex]){
            numbers[mergedArray] = first[firstArrIndex];
            firstArrIndex++;
        }
        else{
            numbers[mergedArray] = second[secondArrIndex];
            secondArrIndex++;
        }
        mergedArray++;
    }
    // Copy the remaining elements if exists
    while (firstArrIndex < firstArrSize){
        numbers[mergedArray] = first[firstArrIndex];
        firstArrIndex++;
        mergedArray++;
    }
    while (secondArrIndex < secondArrSize){
        numbers[mergedArray] = second[secondArrIndex];
        secondArrIndex++;
        mergedArray++;
    }
}

/**
 * Sorts the array using Quick Sort *
 */
void QuickSort::sort(std::vector<int> &numbers) {
    int n = int(numbers.size())- 1;
    sortRecursive(numbers,0,n);
}
/**
 * Change quickSort's methods/
 * @param choice = 0 (for random pivot selection)
 *        choice = 1 (for deterministic median pivot selection)
 */
void QuickSort::chooseMethod(int choice) {
    method = choice;
}
/**
 * Helper function for deterministic median pivot selection.
 * @param numbers is a five numbers Array.
 * @return the median of the array.
 */
int QuickSort::findMedian(std::vector<int> &numbers) {
    InsertionSort insertionSort;
    insertionSort.sort(numbers);
    return numbers[numbers.size()/2];   // Return median element
}

/**
 * Function for deterministic median pivot selection
 * Divide numbers[] in groups of size 5, calculate median
 * of every group and store it in median[] array.
 * @return the median of the array.
 */
int QuickSort::deterministicMedian(std::vector<int> &numbers, int left, int right, int target) {
    if (target >= 0 && target <= right - left + 1)
    {
        int n = right-left+1; // Number of elements in numbers[l..r]

        int i;

        std::vector<int> median((n + 4) / 5);// There will be floor((n+4)/5) groups;
        std::vector<int> temp_array;
        for (i = 0; i < n/5; ++i){
            for(int j = i * 5; j < (i * 5) + 5; ++j) {
                temp_array.push_back(numbers[left + j]);
            }
            median[i] = findMedian(temp_array);
            temp_array.clear();
        }

        if (isLastGroup(n, i)) //For last group with less than 5 elements
        {
            for(int j = i * 5; j <= right; ++j) {
                temp_array.push_back(numbers[left + j]);
            }
            median[i] = findMedian(temp_array);
            ++i;
        }

        // Find median of all medians using recursive call.
        // If median[] has only one element return.
        return (i == 1)? median[i-1]:
               deterministicMedian(median, 0, i - 1, i / 2);
    }
    return numbers[right];
}

bool QuickSort::isLastGroup(int n, int i) const { return i * 5 < n; }

/**
 * Helper function for deterministic median pivot selection.
 * @return the index of the median.
 */
int QuickSort::deterministicMedian(std::vector<int> &numbers, int left, int right) {
    int med = deterministicMedian(numbers, left, right, (right + left) / 2);
    for (int i = right; i >= left ; --i){
        if(numbers[i] == med)
            return i;
    }
    return int(numbers.size()) / 2;
}
/**
 * @return pivot in random or deterministic manner.
 */
int QuickSort::getPivot(std::vector<int> &numbers, int left, int right) {
    if (method == 0 ) {
        srand(time(nullptr));
        return left + rand() % (right - left);
    }
    else{
        return deterministicMedian(numbers, left, right);
    }

}
/**
 *  Partition all numbers arounds the pivot.
 * @return pivot location.
 */
int QuickSort::partition(std::vector<int> &numbers, int left, int right, int pivot) {
    swap(numbers,right,pivot);
    int i = left;
    for(int j = left; j <= right - 1; ++j) {
        if (numbers[j] <= numbers[right]) {
            swap(numbers, i, j);
            i++;
        }
    }
    swap(numbers,i,right);
    return i;
}

/**
 * Partition the array recursively.
 */
void QuickSort::sortRecursive(std::vector<int> &numbers, int left, int right) {
    if (left < right){
        int pivot = getPivot(numbers,left,right);
        int p = partition(numbers,left,right,pivot);
        sortRecursive(numbers,left,p - 1);
        sortRecursive(numbers,p + 1,right);
    }
}

/**
 * Helper class for deterministic select
 * @param numbers
 */
void InsertionSort::sort(std::vector<int> &numbers) {
    int n = numbers.size(), i, key, j;

    for (i = 1; i < n; ++i)
    {
        key = numbers[i];
        j = i - 1;
        /* Move elements of arr[0..i-1], that are
        greater than key, to one position ahead
        of their current position */
        while (j >= 0 && numbers[j] > key)
        {
            numbers[j + 1] = numbers[j];
            j = j - 1;
        }
        numbers[j + 1] = key;
    }

}



