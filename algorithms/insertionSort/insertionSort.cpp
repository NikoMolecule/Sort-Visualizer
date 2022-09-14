#include "insertionSort.h"

#include <iostream>
using namespace std;

void insertionSort(vector<int>* arr, vector<StackFrame>& st, vector<int>& state) {
  for(int i = 1; i < (*arr).size(); i++) {
    int keyInd = i;
    int key = (*arr)[i];
    int j;
    state[keyInd] = 2;

    StackFrame curState{*arr, state};
    st.push_back(curState);
    for(j = i - 1; j >= 0; j--) {
      if(i != j + 2) {
        state[j + 2] = 0;
      }

      if(i != j + 1) {
        state[j + 1] = 1;
      }
      state[j] = 1;

      StackFrame curState1{*arr, state};
      st.push_back(curState1);
      if((*arr)[j] > key) {
        (*arr)[j + 1] = (*arr)[j];
      } else {
        break;
      }
    }
    (*arr)[j + 1] = key;
    fill(state.begin(), state.end(), 0);

    StackFrame curState1{*arr, state};
    st.push_back(curState1);
  }
}