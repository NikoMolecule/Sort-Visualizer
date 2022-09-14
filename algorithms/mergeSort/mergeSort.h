#ifndef MERGESORT_H
#define MERGESORT_H

#include "../../classes/StackFrame.h"

void merge(vector<int>* arr, int l, int mid, int r, vector<StackFrame>& st, vector<int>& state);
void mergeSort(vector<int>* arr, int l, int r, vector<StackFrame>& st, vector<int>& state);

#endif;