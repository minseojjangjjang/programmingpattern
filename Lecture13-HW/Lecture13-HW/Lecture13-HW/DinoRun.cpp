#pragma comment(lib, "Opengl32.lib")

#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <ctime>
#include <cstdlib>

// Player의 상태를 관리하는 변수
float posY = -0.1f; // 초기 Y 위치, Ground의 Y 좌표보다 약간 위에 위치
float velocityY = 0.0f;
const float GRAVITY = -9.8f;
const float JUMP_VELOCITY = 5.0f;
const float DELTA_TIME = 0.016f; // 약 60FPS
bool isJumping = false;

struct Obstacle {
    float posX;
    float posY;
};

std::vector<Obstacle> obstacles;
float obstacleSpeed = 1.0f;
float spawnTimer = 0.0f;
const float SPAWN_INTERVAL = 1.5f;

void errorCallback(int error, const char* description) {
    std::cerr << "GLFW Error: " << description << std::endl;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS && !isJumping) {
        velocityY = JUMP_VELOCITY;
        isJumping = true;
    }
}

void Ground() {
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0.0f, 1.0f, 0.0f); // 사각형의 색상 설정 (초록색)

    // 사각형의 각 꼭짓점
    glVertex2f(-1.0f, -1.0f); // 왼쪽 아래
    glVertex2f(1.0f, -1.0f);  // 오른쪽 아래
    glVertex2f(1.0f, -0.3f);  // 오른쪽 위
    glVertex2f(-1.0f, -0.3f); // 왼쪽 위

    glEnd();
}

void Player() {
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0f, 0.0f, 1.0f); // 사각형의 색상 설정 (자홍색)

    // 사각형의 각 꼭짓점
    glVertex2f(-0.2f, posY - 0.2f); // 왼쪽 아래
    glVertex2f(0.2f, posY - 0.2f);  // 오른쪽 아래
    glVertex2f(0.2f, posY + 0.2f);  // 오른쪽 위
    glVertex2f(-0.2f, posY + 0.2f); // 왼쪽 위

    glEnd();
}

void ObstacleDraw(const Obstacle& obstacle) {
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0f, 0.0f, 0.0f); // 사각형의 색상 설정 (빨간색)

    // 사각형의 각 꼭짓점
    glVertex2f(obstacle.posX - 0.2f, obstacle.posY - 0.2f); // 왼쪽 아래
    glVertex2f(obstacle.posX + 0.2f, obstacle.posY - 0.2f); // 오른쪽 아래
    glVertex2f(obstacle.posX + 0.2f, obstacle.posY + 0.2f); // 오른쪽 위
    glVertex2f(obstacle.posX - 0.2f, obstacle.posY + 0.2f); // 왼쪽 위

    glEnd();
}

void updateObstacles(float deltaTime) {
    for (auto& obstacle : obstacles) {
        obstacle.posX -= obstacleSpeed * deltaTime;
    }

    // 장애물 생성
    spawnTimer += deltaTime;
    if (spawnTimer >= SPAWN_INTERVAL) {
        spawnTimer = 0.0f;
        Obstacle newObstacle = { 1.0f, -0.1f }; // Y 위치를 -0.1로 설정
        obstacles.push_back(newObstacle);
    }

    // 장애물이 화면 밖으로 나가면 제거
    if (!obstacles.empty() && obstacles.front().posX < -1.2f) {
        obstacles.erase(obstacles.begin());
    }
}

bool checkCollision() {
    for (const auto& obstacle : obstacles) {
        if (std::abs(obstacle.posX) < 0.4f && std::abs(obstacle.posY - posY) < 0.4f) {
            return true;
        }
    }
    return false;
}

void update() {
    // 중력이 속도에 미치는 영향
    velocityY += GRAVITY * DELTA_TIME;
    // 속도가 위치에 미치는 영향
    posY += velocityY * DELTA_TIME;

    // 바닥에 닿으면 점프 상태 해제 및 위치, 속도 초기화
    if (posY <= -0.7f) {
        posY = -0.7f;
        velocityY = 0.0f;
        isJumping = false;
    }

    // 장애물 업데이트
    updateObstacles(DELTA_TIME);

    // 충돌 검사
    if (checkCollision()) {
        std::cout << "Game Over!" << std::endl;
        glfwSetWindowShouldClose(glfwGetCurrentContext(), GLFW_TRUE);
    }
}

int main(void) {
    // GLFW 초기화
    if (!glfwInit())
        return -1;

    GLFWwindow* window = glfwCreateWindow(1680, 960, "MuSoeunEngine", NULL, NULL);

    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetErrorCallback(errorCallback);
    glfwSetKeyCallback(window, keyCallback);

    std::srand(static_cast<unsigned int>(std::time(0))); // 랜덤 시드 초기화

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        update(); // 플레이어 상태 및 장애물 업데이트

        Ground();
        Player();
        for (const auto& obstacle : obstacles) {
            ObstacleDraw(obstacle);
        }

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}
