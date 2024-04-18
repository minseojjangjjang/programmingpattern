//������ ������Ʈ��: Lecture04_HW
//idle : ȭ��� ���������� clear
//���콺 ������ KeyDown�ϸ� : ������
//���콺 ������ KeyUp�ϸ� : ���󺹱�
//���콺 ���� KeyDown�ϸ� : ���
//���콺 ���� KeyUp�ϸ� : ���󺹱�
//���콺 ������ KeyDown�ϰ� �巡�� ���̸� : �Ķ���
//���콺 ���� KeyDown�ϰ� �巡�� ���̸� : ����Ÿ��

//�й� : 202327041
//�̸� : ���μ�

#pragma comment (lib, "OpenGL32.lib")
#include <GLFW/glfw3.h>
#include <iostream>

bool IsRightBtnDown = false; 
bool IsLeftBtnDown = false; 
bool IsRightBtnDrag = false; 
bool IsLeftBtnDrag = false; 

// ���콺 Ŭ�� �ݹ� �Լ�(���콺 Ŭ�� �̺�Ʈ�� �߻����� �� ȣ��Ǵ� �Լ�, �̺�Ʈ�� ���� ����,ó���� ���)
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_RIGHT) // ��Ŭ�� �� ����
    {
        if (action == GLFW_PRESS) // ���콺�� Ŭ������ ��
        {
            IsRightBtnDown = true;//��Ŭ���� ��
            IsRightBtnDrag = false;//��Ŭ���巡�״� ����
        }
        else if (action == GLFW_RELEASE) // ���콺 Ŭ���� �������� ��
            IsRightBtnDown = false;//��Ŭ���� ��������
    }
    else if (button == GLFW_MOUSE_BUTTON_LEFT) // ���� ���콺 ��ư Ŭ�� �� ����
    {
        if (action == GLFW_PRESS) // ���콺�� Ŭ������ ��
        {
            IsLeftBtnDown = true;//��Ŭ���� ��
            IsLeftBtnDrag = false; //��Ŭ���巡�״� ����
        }
        else if (action == GLFW_RELEASE) // ���콺 Ŭ���� �������� ��
            IsLeftBtnDown = false;//��Ŭ���� ��������
    }
}

// ���콺 �̵� �ݹ� �Լ�(���콺 �̵� �̺�Ʈ�� �߻����� �� ����Ǵ� �Լ��μ�, �̺�Ʈ�� ���� ����,ó�� ���)
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
    //���콺 Ŀ���� ��ġ�� ����� ������ ȣ��Ǵ� �ݹ� �Լ�-> �ι�°�� ����° �Ű������� xpos��ypos�� ���� ���콺Ŀ���� ���� ��ġ�� ���޹���
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) // ������ ���콺 ��ư�� ���� ���°� ���ӵ� ��
    {
        IsRightBtnDrag = true; //������ �巡�� ���� �� ��
        IsLeftBtnDrag = false; //���� �巡�� ���� �� ����
        glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // ȭ���� �Ķ������� ����
    }
    else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) // ���� ���콺 ��ư�� ���� ���°� ���ӵ� ��
    {
        IsRightBtnDrag = false; //������ �巡�� ���� �� ����
        IsLeftBtnDrag = true; //���� �巡�� ���� �� ��
        glClearColor(1.0f, 0.0f, 1.0f, 1.0f); // ȭ���� ����(����Ÿ)������ ����
    }
    else
    {
        IsRightBtnDrag = false; //������ �巡�� ���� �� ����
        IsLeftBtnDrag = false; //���� �巡�� ���� �� ����
    }

    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);
}

int main() {
    // GLFW �ʱ�ȭ
    if (!glfwInit()) {
        std::cerr << "GLFW �ʱ�ȭ ����" << std::endl;
        return -1;
    }

    // GLFW ������ ����
    GLFWwindow* window = glfwCreateWindow(1280, 760, "OpenGL Window", NULL, NULL);
    if (!window) {
        std::cerr << "GLFW ������ ���� ����" << std::endl;
        glfwTerminate();
        return -1;
    }

    // ������ ���ؽ�Ʈ ����
    glfwMakeContextCurrent(window);
    // ���콺 Ŭ�� �ݹ� �Լ� ���
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    // ���콺 �̵� �ݹ� �Լ� ���
    glfwSetCursorPosCallback(window, cursor_position_callback);
    // ȭ�� ó�� �ӵ� ���� �޼���
    glfwSwapInterval(1);

    //���� ����
    while (!glfwWindowShouldClose(window)) {//�����찡 �������� ���θ� Ȯ���ϴ� �Լ� �����찡 �����ٸ� true�� ��ȯ
        glfwPollEvents();//�� �ݺ����� �� �Լ��� ȣ��Ǿ� �̺�Ʈ�� ó���� (���콺 �Է�, Ű �Է�, ������ ũ�� ���� ��)

        if (IsRightBtnDown) // ������ ���콺�� ������
        {
            glClearColor(1.0f, 0.0f, 0.0f, 1.0f); // ȭ���� ���������� ����
        }
        else if (IsLeftBtnDown)
        {
            glClearColor(0.0f, 1.0f, 0.0f, 1.0f); // ȭ���� �ʷϻ����� ����
        }
        else
        {
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // �ƹ��͵� �� ���� ���¸� ȭ���� ���������� ����
        }

        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
    }

    // GLFW ����
    glfwTerminate();
    return 0;
}