#ifndef QUICKSORT_H
#define QUICKSORT_H

#include "../../classes/StackFrame.h"

void swap(vector<int>* arr, int i, int j);
int partition(vector<int>* arr, int l, int r, vector<StackFrame>& st, vector<int>& state);
void quickSort(vector<int>* arr, int l, int r, vector<StackFrame>& st, vector<int>& state);

#endif