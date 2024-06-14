#include "object.h"
#include <iostream>

// ���� ������
float blockX = 0.0f;
float blockY = -0.5f;
float velocityY = 0.0f;
bool isJumping = false;
const float gravity = -9.81f;  // �߷� ���ӵ� (m/s^2)
const float jumpForce = 5.0f;  // ���� �ʱ� �ӵ� (m/s)
float obstacleX = 1.0f;
const float obstacleWidth = 0.075f; // ��ֹ��� ���� ���̸� 0.05f ����
const float obstacleHeightLow = 0.25f;  // ���� ���� ��ֹ� ���� (50px x 100px)
const float obstacleHeightHigh = 0.75f; // ���� ���� ��ֹ� ���� (50px x 300px)
const float obstacleSpeed = 1.0f;  // ��ֹ��� �⺻ �̵� �ӵ�
float currentObstacleSpeed = obstacleSpeed;
const float groundY = -0.6f; // Ground�� y ��ġ
bool isLowObstacle = true; // ��ֹ� ���� ������ ���� �÷���

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
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS && !isJumping)
    {
        isJumping = true;
        velocityY = jumpForce;  // ���� �ʱ� �ӵ� ����
    }
    if (key == GLFW_KEY_RIGHT && (action == GLFW_PRESS || action == GLFW_REPEAT))
    {
        currentObstacleSpeed = obstacleSpeed * 2.0f;
    }
    if (key == GLFW_KEY_RIGHT && action == GLFW_RELEASE)
    {
        currentObstacleSpeed = obstacleSpeed;
    }
}

int Player(float deltaTime)
{
    // �����ϴ� �簢�� �׸���
    glBegin(GL_QUADS);
    glColor3f(1.0f, 0.0f, 0.0f); // ������

    // ����� ��ġ�� �ݿ��Ͽ� ������ ���� (���� ���� 50px�� ��ȯ)
    glVertex2f(blockX - 0.1625f, blockY - 0.1625f);
    glVertex2f(blockX + 0.1625f, blockY - 0.1625f);
    glVertex2f(blockX + 0.1625f, blockY + 0.1625f);
    glVertex2f(blockX - 0.1625f, blockY + 0.1625f);

    glEnd();

    // ���� ���� �� �߷°� ��ġ ������Ʈ
    if (isJumping)
    {
        velocityY += gravity * deltaTime;  // �߷� ���ӵ� ����
        blockY += velocityY * deltaTime;

        // ����� �ٴڿ� ������ ���� ����
        if (blockY <= -0.5f)
        {
            blockY = -0.5f;
            isJumping = false;
        }
    }

    return 0;
}

int Ground()
{
    glBegin(GL_POLYGON);
    glColor3f(255.0f / 255.0f, 200.0f / 255.0f, 15.0f / 255.0f);
    glVertex2f(1.0f, -0.6f);   // ������ ��
    glVertex2f(1.0f, -1.0f);  // ������ �Ʒ�
    glVertex2f(-1.0f, -1.0f); // ���� �Ʒ�
    glVertex2f(-1.0f, -0.6f);  // ���� ��
    glEnd(); // �簢�� �׸��� ����

    return 0;
}

int Obstacle(float deltaTime)
{
    // ��ֹ� �簢�� �׸���
    glBegin(GL_QUADS);
    glColor3f(0.0f, 1.0f, 0.0f); // ���

    if (isLowObstacle)
    {
        // ���� ���� ��ֹ��� ��ġ�� �ݿ��Ͽ� ������ ����
        glVertex2f(obstacleX - obstacleWidth, groundY);
        glVertex2f(obstacleX + obstacleWidth, groundY);
        glVertex2f(obstacleX + obstacleWidth, groundY + obstacleHeightLow);
        glVertex2f(obstacleX - obstacleWidth, groundY + obstacleHeightLow);
    }
    else
    {
        // ���� ���� ��ֹ��� ��ġ�� �ݿ��Ͽ� ������ ����
        glVertex2f(obstacleX - obstacleWidth, groundY);
        glVertex2f(obstacleX + obstacleWidth, groundY);
        glVertex2f(obstacleX + obstacleWidth, groundY + obstacleHeightHigh);
        glVertex2f(obstacleX - obstacleWidth, groundY + obstacleHeightHigh);
    }

    glEnd();

    // ��ֹ��� ��ġ ������Ʈ
    obstacleX -= currentObstacleSpeed * deltaTime;

    // ȭ�� ������ ����� �ٽ� ���������� �̵� �� ũ�� ����
    if (obstacleX < -1.0f)
    {
        obstacleX = 1.0f;
        // ��ֹ� ���� ����
        isLowObstacle = !isLowObstacle;
    }

    return 0;
}

void CheckCollision()
{
    float obstacleHeight = isLowObstacle ? obstacleHeightLow : obstacleHeightHigh;

    // �÷��̾�� ��ֹ��� �浹 üũ
    if (blockX + 0.1625f > obstacleX - obstacleWidth &&
        blockX - 0.1625f < obstacleX + obstacleWidth &&
        blockY + 0.1625f > groundY &&
        blockY - 0.1625f < groundY + obstacleHeight)
    {
        std::cout << "Collision detected with " << (isLowObstacle ? "low" : "high") << " obstacle!" << std::endl;
        glfwTerminate();
        exit(0); // �浹 �� ���α׷� ����
    }
}
