#version 330 core

in vec3 colorState;
out vec4 fragColor;

void main(){
  fragColor = vec4(colorState, 1.0);
}