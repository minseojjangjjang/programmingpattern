#pragma comment(lib, "Opengl32.lib")

#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include "object.h"

// 윈도우 크기 설정
const int windowWidth = 800;
const int windowHeight = 600;

// 배경색 설정 (하늘색)
const float bgColorR = 0.0f / 255.0f;
const float bgColorG = 30.0f / 255.0f;
const float bgColorB = 100.0f / 255.0f;

int main(void)
{
    // GLFW 라이브러리 초기화
    if (!glfwInit())
        return -1;

    GLFWwindow* window;
    window = glfwCreateWindow(windowWidth, windowHeight, "Google Dino Run Copy Game", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    // OpenGL 컨텍스트 설정
    glfwMakeContextCurrent(window);
    glfwSetErrorCallback(errorCallback);
    glfwSetKeyCallback(window, keyCallback);

    float lastFrameTime = glfwGetTime();
    float deltaTime = 0.0f;

    while (!glfwWindowShouldClose(window))
    {
        float currentFrameTime = glfwGetTime();
        deltaTime = currentFrameTime - lastFrameTime;
        lastFrameTime = currentFrameTime;

        glfwPollEvents();
        glClearColor(bgColorR, bgColorG, bgColorB, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        Ground();
        Player(deltaTime);
        Obstacle(deltaTime);
        CheckCollision();

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}
