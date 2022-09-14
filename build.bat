set CFLAGS= -target x86_64-pc-win32 -std=c++17 -O2 -Wall -Wextra -Wpedantic
set CFLAGS2= -I..\glfw-3.3.8\include -L..\glfw-3.3.8\lib-vc2022 -I..\GLAD\include -I\classes\Shader.h -I\algorithms\mergeSort\mergeSort.h  -I\algorithms\quickSort\quickSort.h -I\algorithms\bubbleSort\bubbleSort.h  -I\algorithms\insertionSort\insertionSort.h
set LDFLAGS= -lshell32 -luser32 -lglu32 -lopengl32 -lgdi32 -lglfw3_mt -lglu32 -lopengl32 -lgdi32 -lglfw3_mt
set SOURCES= main.cpp glad.c .\algorithms\mergeSort\mergeSort.cpp .\algorithms\quickSort\quickSort.cpp .\algorithms\bubbleSort\bubbleSort.cpp .\algorithms\insertionSort\insertionSort.cpp

clang++.exe %CFLAGS% %CFLAGS2% %SOURCES% %LDFLAGS% -o test.exe