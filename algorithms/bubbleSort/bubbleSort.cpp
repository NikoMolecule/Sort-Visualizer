#include "bubbleSort.h"

#include <iostream>
using namespace std;

void bubbleSort(int length, vector<int>* arr, vector<StackFrame>& st, vector<int>& state) {
  for (int i = 0; i < 100; i++) {
    for (int j = 0; j < 100 - i - 1; j++) {
      int k = min(max(0, j - 1), 97);
      state[k] = 0;
      state[k + 1] = 1;
      state[k + 2] = 1;
      if ((*arr)[j] > (*arr)[j + 1]) {
        swap((*arr)[j], (*arr)[j + 1]);
        swap(state[j], state[j + 1]);
      }

      StackFrame curState{*arr, state};
      st.push_back(curState);
    }
    fill(state.begin(), state.end(), 0);
  }

  fill(state.begin(), state.end(), 0);

  StackFrame curState{*arr, state};
  st.push_back(curState);
}