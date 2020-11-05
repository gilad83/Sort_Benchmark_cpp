//
// Created by gilad on 25/10/2020.
//

#ifndef COPTERPIX_ASSIGNMENT_SORTALGOS_H
#define COPTERPIX_ASSIGNMENT_SORTALGOS_H

#include <vector>
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <random>

class SortAlgos {
    public:
    static void swap(std::vector<int> &numbers,int left,int right);
    virtual void sort(std::vector<int> &numbers) = 0;
};

class BubbleSort :public SortAlgos{
    public:
    virtual void sort(std::vector<int> &numbers);
};

class MergeSort : public SortAlgos{
public:
    virtual void sort(std::vector<int> &numbers);

private:
    void sortRecursive(std::vector<int> &numbers,int left,int right);
    void merge(std::vector<int> &numbers,int left,int middle,int right);
};

class QuickSort : public SortAlgos {
public:
    virtual void sort(std::vector<int> &numbers);
    void chooseMethod(int choice);
private:
    int findMedian(std::vector<int> &numbers);
    int deterministicMedian(std::vector<int> &numbers, int left, int right, int target);
    int deterministicMedian(std::vector<int> &numbers, int left, int right);
    int getPivot(std::vector<int> &numbers,int left,int right);
    int partition(std::vector<int> &numbers,int left,int right,int pivot);
    void sortRecursive(std::vector<int> &numbers,int left,int right);
    int method = 0;

    bool isLastGroup(int n, int i) const;
};

class InsertionSort: public SortAlgos{
public:
    virtual void sort(std::vector<int> &numbers);
};

#endif //COPTERPIX_ASSIGNMENT_SORTALGOS_H
