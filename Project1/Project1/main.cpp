#pragma comment(lib, "Opengl32.lib")

#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include "object.h"

// ������ ũ�� ����
const int windowWidth = 800;
const int windowHeight = 600;

// ���� ���� (�ϴû�)
const float bgColorR = 0.0f / 255.0f;
const float bgColorG = 30.0f / 255.0f;
const float bgColorB = 100.0f / 255.0f;

int main(void)
{
    // GLFW ���̺귯�� �ʱ�ȭ
    if (!glfwInit())
        return -1;

    GLFWwindow* window;
    window = glfwCreateWindow(windowWidth, windowHeight, "Google Dino Run Copy Game", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    // OpenGL ���ؽ�Ʈ ����
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
