#include "quickSort.h"

#include <iostream>
#include <vector>
using namespace std;

void swap(vector<int>* arr, int i, int j) {
  int temp = (*arr)[i];
  (*arr)[i] = (*arr)[j];
  (*arr)[j] = temp;
}

int partition(vector<int>* arr, int l, int r, vector<StackFrame>& st, vector<int>& state) {
  for(int i = l; i <= r; i++) {
    state[i] = 2;
  }
  
  int pivotInd = l;
  int pivot = (*arr)[r];
  state[pivotInd] = 1;

  StackFrame curState1{*arr, state};
  st.push_back(curState1);

  for (int i = l; i < r; i++) {
    if ((*arr)[i] <= pivot) {
      swap(arr, i, pivotInd);
      state[pivotInd] = 0;
      pivotInd++;
      state[pivotInd] = 1;

      StackFrame curState{*arr, state};
      st.push_back(curState);
    }
  }

  swap(arr, pivotInd, r);

  for (int i = l; i <= r; i++) {
    if(i != pivotInd) {
      state[i] = 0;
    }
  }
  StackFrame curState2{*arr, state};
  st.push_back(curState2);

  return pivotInd;
}

void quickSort(vector<int>* arr, int l, int r, vector<StackFrame>& st, vector<int>& state) {
  if (l >= r) {
    return;
  }
  int partitionInd = partition(arr, l, r, st, state);
  state[partitionInd] = 0;

  StackFrame curState{*arr, state};
  st.push_back(curState);

  quickSort(arr, l, partitionInd - 1, st, state);
  quickSort(arr, partitionInd + 1, r, st, state);
}