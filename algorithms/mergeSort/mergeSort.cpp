#include "mergeSort.h"

#include <iostream>
using namespace std;

void merge(vector<int>* arr, int l, int mid, int r, vector<StackFrame>& st, vector<int>& state) {
  int size1 = mid - l + 1;
  int size2 = r - mid;

  int* leftArray = (int*)malloc(size1 * sizeof(int));
  int* rightArray = (int*)malloc(size2 * sizeof(int));

  for (int i = l; i <= mid; i++) {
    leftArray[i - l] = (*arr)[i];
  }

  for (int i = mid + 1; i <= r; i++) {
    rightArray[i - mid - 1] = (*arr)[i];
  }

  int* sortedArray = (int*)malloc((size1 + size2) * sizeof(int));

  int p1 = 0, p2 = 0, p3 = 0;
  while (p1 < size1 || p2 < size2) {
    if (p1 >= size1) {
      sortedArray[p3] = rightArray[p2];
      state[mid + p2] = 0;
      state[mid + p2 + 1] = 1;
      p2++;
    } else if (p2 >= size2) {
      sortedArray[p3] = leftArray[p1];
      state[l + p1 - 1] = 0;
      state[l + p1] = 1;
      p1++;
    } else {
      state[mid + p2] = 0;
      state[l + p1 - 1] = 0;
      state[mid + p2 + 1] = 1;
      state[l + p1] = 1;
      if (leftArray[p1] > rightArray[p2]) {
        sortedArray[p3] = rightArray[p2];
        state[mid + p2 + 1] = 2;
        p2++;
      } else {
        sortedArray[p3] = leftArray[p1];
        state[l + p1] = 2;
        p1++;
      }
    }

    StackFrame curState1{*arr, state};
    st.push_back(curState1);

    p3++;
  }

  fill(state.begin(), state.end(), 0);

  for (int i = l; i <= r; i++) {
    (*arr)[i] = sortedArray[i - l];
    state[i] = 1;
    StackFrame curState2{*arr, state};
    st.push_back(curState2);

    state[i] = 0;
    StackFrame curState3{*arr, state};
    st.push_back(curState3);
  }
}

void mergeSort(vector<int>* arr, int l, int r, vector<StackFrame>& st, vector<int>& state) {
  if (l >= r) {
    return;
  }
  int mid = (l + r) / 2;
  mergeSort(arr, l, mid, st, state);
  mergeSort(arr, mid + 1, r, st, state);
  merge(arr, l, mid, r, st, state);
}
