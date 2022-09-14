#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "./classes/Shader.h"
#include "./classes/StackFrame.h"
#include "./algorithms/mergeSort/mergeSort.h"
#include "./algorithms/quickSort/quickSort.h"
#include "./algorithms/bubbleSort/bubbleSort.h"
#include "./algorithms/insertionSort/insertionSort.h"

#include <iostream>
#include <chrono>
#include <thread>
using namespace std;

float* vertecies = (float*)malloc(2400 * sizeof(float));
unsigned int* elements = (unsigned int*)malloc(600 * sizeof(float));

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
}

float map(float x, float a, float b, float c, float d) {
  return (x - a) * ((d - c) / (b - a)) + c;
}

void renderSort(float length, float vertecies[], unsigned int elements[], vector<int> vals, vector<int> state) {
  float width = 1.5f / length;
  for(int i = 0; i < length; i++) {
    float r, g, b;
    if(state[i] == 0) {
      r = 1.0f; g = 1.0f; b = 1.0f;
    } else if(state[i] == 1) {
      r = 1.0f; g = 0.0f; b = 0.0f;
    } else if(state[i] == 2) {
      r = 0.0f; g = 1.0f; b = 0.0f;
    }
    float val = map(vals[i], 1, 100, 1, length);
    float height = 2.0f / length * val;

    float y2 = -1.0f;
    float y1 = y2 + height;
    float x1 = -1.0f + 2.0f / length * i;
    float x2 = x1 + width;

    int ind = i * 24;
    vertecies[ind] = x1;
    vertecies[ind + 1] = y1;
    vertecies[ind + 2] = 0.0f;

    vertecies[ind + 3] = r;
    vertecies[ind + 4] = g;
    vertecies[ind + 5] = b;

    vertecies[ind + 6] = x1;
    vertecies[ind + 7] = y2;
    vertecies[ind + 8] = vertecies[ind + 2];

    vertecies[ind + 9] = r;
    vertecies[ind + 10] = g;
    vertecies[ind + 11] = b;

    vertecies[ind + 12] = x2;
    vertecies[ind + 13] = y1;
    vertecies[ind + 14] = vertecies[ind + 2];

    vertecies[ind + 15] = r;
    vertecies[ind + 16] = g;
    vertecies[ind + 17] = b;

    vertecies[ind + 18] = x2;
    vertecies[ind + 19] = y2;
    vertecies[ind + 20] = vertecies[ind + 2];

    vertecies[ind + 21] = r;
    vertecies[ind + 22] = g;
    vertecies[ind + 23] = b;

    ind /= 4;

    elements[ind] = 4 * i;
    elements[ind + 1] = 4 * i + 2;
    elements[ind + 2] = 4 * i + 3;
    elements[ind + 3] = 4 * i + 3;
    elements[ind + 4] = 4 * i + 1;
    elements[ind + 5] = 4 * i;
  }
}

int main() {
  int inp = 0;
  string s = "Sort Visualizer";
  srand(time(0));

  vector<StackFrame> v;
  vector<int> arr(100);
  vector<int> state(100);
  srand(time(0));
  for(int i = 0; i < 100; i++) {
    arr[i] = rand() % 100 + 1;
  }

  cout << "Hello, this is sorting vizaulizer. please choose which sorting algorithm you want to see\n";
  while(inp < 1 || inp > 4) {
    cout << "[1]Merge Sort\n" << "[2]Bubble Sort\n" << "[3]Quick Sort\n" << "[4]Insetion Sort\n";
    cin >> inp;
  }

  if(inp == 1) {
    renderSort(100, vertecies, elements, arr, state);
    mergeSort(&arr, 0, 99, v, state);
    s += "- MergeSort";
  } else if(inp == 2) {
    renderSort(100, vertecies, elements, arr, state);
    bubbleSort(100, &arr, v, state);
    s += "- BubbleSort";
  } else if (inp == 3) {
    renderSort(100, vertecies, elements, arr, state);
    quickSort(&arr, 0, 99, v, state);
    s += "- QuickSort";
  } else if (inp == 4) {
    renderSort(100, vertecies, elements, arr, state);
    insertionSort(&arr, v, state);
    s += "- InsertionSort";
  }

  const char* c = s.c_str();

  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow* window = glfwCreateWindow(1200, 900, c, NULL, NULL);
  if (window == NULL) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  Shader shaderProgram("./shaders/my_vertex.vs", "./shaders/my_fragment.fs");

  unsigned int VBO, VAO, EBO;

  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, 1200 * sizeof(float), vertecies, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, 600 * sizeof(unsigned int), elements, GL_STATIC_DRAW);
  
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  int ind = 0;

  while (!glfwWindowShouldClose(window)) {
    this_thread::sleep_for(chrono::milliseconds(8));
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    renderSort(100, vertecies, elements, v[ind].v, v[ind].colorState);
    glBufferData(GL_ARRAY_BUFFER, 2400 * sizeof(float), vertecies, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 600 * sizeof(unsigned int), elements, GL_STATIC_DRAW);

    if(ind < v.size() - 1) {
      ind++;
    }

    glBindVertexArray(VAO);
    shaderProgram.use();
    glDrawElements(GL_TRIANGLES, 600, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glfwTerminate();
  return 0;
}