#pragma comment(lib, "Opengl32.lib")
#include <GLFW/glfw3.h>
#include <iostream>

void errorCallback(int error, const char* description)
{
    std::cerr << "GLFW Error: " << description << std::endl;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT)
    {
        if (action == GLFW_PRESS)
        {
            // ���� ���콺 ��ư�� ������ �� �����츦 ������� ����
            glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
        }
        else if (action == GLFW_RELEASE)
        {
            // ���� ���콺 ��ư�� �������� �� ������ ���������� ����
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        }
    }
    else if (button == GLFW_MOUSE_BUTTON_RIGHT)
    {
        if (action == GLFW_PRESS)
        {
            // ������ ���콺 ��ư�� ������ �� �����츦 ���������� ����
            glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        }
        else if (action == GLFW_RELEASE)
        {
            // ������ ���콺 ��ư�� �������� �� ������ ���������� ����
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        }
    }
}

void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
{
    int leftButton = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
    int rightButton = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT);

    if (leftButton == GLFW_PRESS)
    {
        // ���� ��ư�� ������ �巡�� ���̸� ����Ÿ������ ����
        glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
    }
    else if (rightButton == GLFW_PRESS)
    {
        // ������ ��ư�� ������ �巡�� ���̸� �Ķ������� ����
        glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    }
}

int main(void)
{
    if (!glfwInit())
        return -1;

    GLFWwindow* window;
    window = glfwCreateWindow(1280, 768, "MuSoeunEngine", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetErrorCallback(errorCallback);
    glfwSetKeyCallback(window, keyCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetCursorPosCallback(window, cursorPositionCallback);

    // �ʱ� ������ ���������� ����
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}
