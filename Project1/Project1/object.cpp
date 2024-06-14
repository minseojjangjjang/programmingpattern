#include "object.h"
#include <iostream>

// 전역 변수들
float blockX = 0.0f;
float blockY = -0.5f;
float velocityY = 0.0f;
bool isJumping = false;
const float gravity = -9.81f;  // 중력 가속도 (m/s^2)
const float jumpForce = 5.0f;  // 점프 초기 속도 (m/s)
float obstacleX = 1.0f;
const float obstacleWidth = 0.075f; // 장애물의 가로 길이를 0.05f 줄임
const float obstacleHeightLow = 0.25f;  // 낮은 높이 장애물 높이 (50px x 100px)
const float obstacleHeightHigh = 0.75f; // 높은 높이 장애물 높이 (50px x 300px)
const float obstacleSpeed = 1.0f;  // 장애물의 기본 이동 속도
float currentObstacleSpeed = obstacleSpeed;
const float groundY = -0.6f; // Ground의 y 위치
bool isLowObstacle = true; // 장애물 높이 변경을 위한 플래그

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
        velocityY = jumpForce;  // 점프 초기 속도 설정
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
    // 점프하는 사각형 그리기
    glBegin(GL_QUADS);
    glColor3f(1.0f, 0.0f, 0.0f); // 빨간색

    // 블록의 위치를 반영하여 꼭지점 설정 (가로 길이 50px로 변환)
    glVertex2f(blockX - 0.1625f, blockY - 0.1625f);
    glVertex2f(blockX + 0.1625f, blockY - 0.1625f);
    glVertex2f(blockX + 0.1625f, blockY + 0.1625f);
    glVertex2f(blockX - 0.1625f, blockY + 0.1625f);

    glEnd();

    // 점프 중일 때 중력과 위치 업데이트
    if (isJumping)
    {
        velocityY += gravity * deltaTime;  // 중력 가속도 적용
        blockY += velocityY * deltaTime;

        // 블록이 바닥에 닿으면 점프 중지
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
    glVertex2f(1.0f, -0.6f);   // 오른쪽 위
    glVertex2f(1.0f, -1.0f);  // 오른쪽 아래
    glVertex2f(-1.0f, -1.0f); // 왼쪽 아래
    glVertex2f(-1.0f, -0.6f);  // 왼쪽 위
    glEnd(); // 사각형 그리기 종료

    return 0;
}

int Obstacle(float deltaTime)
{
    // 장애물 사각형 그리기
    glBegin(GL_QUADS);
    glColor3f(0.0f, 1.0f, 0.0f); // 녹색

    if (isLowObstacle)
    {
        // 낮은 높이 장애물의 위치를 반영하여 꼭지점 설정
        glVertex2f(obstacleX - obstacleWidth, groundY);
        glVertex2f(obstacleX + obstacleWidth, groundY);
        glVertex2f(obstacleX + obstacleWidth, groundY + obstacleHeightLow);
        glVertex2f(obstacleX - obstacleWidth, groundY + obstacleHeightLow);
    }
    else
    {
        // 높은 높이 장애물의 위치를 반영하여 꼭지점 설정
        glVertex2f(obstacleX - obstacleWidth, groundY);
        glVertex2f(obstacleX + obstacleWidth, groundY);
        glVertex2f(obstacleX + obstacleWidth, groundY + obstacleHeightHigh);
        glVertex2f(obstacleX - obstacleWidth, groundY + obstacleHeightHigh);
    }

    glEnd();

    // 장애물의 위치 업데이트
    obstacleX -= currentObstacleSpeed * deltaTime;

    // 화면 왼쪽을 벗어나면 다시 오른쪽으로 이동 및 크기 변경
    if (obstacleX < -1.0f)
    {
        obstacleX = 1.0f;
        // 장애물 높이 변경
        isLowObstacle = !isLowObstacle;
    }

    return 0;
}

void CheckCollision()
{
    float obstacleHeight = isLowObstacle ? obstacleHeightLow : obstacleHeightHigh;

    // 플레이어와 장애물의 충돌 체크
    if (blockX + 0.1625f > obstacleX - obstacleWidth &&
        blockX - 0.1625f < obstacleX + obstacleWidth &&
        blockY + 0.1625f > groundY &&
        blockY - 0.1625f < groundY + obstacleHeight)
    {
        std::cout << "Collision detected with " << (isLowObstacle ? "low" : "high") << " obstacle!" << std::endl;
        glfwTerminate();
        exit(0); // 충돌 시 프로그램 종료
    }
}
