#pragma comment(lib, "Opengl32.lib")

#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <ctime>
#include <cstdlib>

// Player�� ���¸� �����ϴ� ����
float posY = -0.1f; // �ʱ� Y ��ġ, Ground�� Y ��ǥ���� �ణ ���� ��ġ
float velocityY = 0.0f;
const float GRAVITY = -9.8f;
const float JUMP_VELOCITY = 5.0f;
const float DELTA_TIME = 0.016f; // �� 60FPS
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
    glColor3f(0.0f, 1.0f, 0.0f); // �簢���� ���� ���� (�ʷϻ�)

    // �簢���� �� ������
    glVertex2f(-1.0f, -1.0f); // ���� �Ʒ�
    glVertex2f(1.0f, -1.0f);  // ������ �Ʒ�
    glVertex2f(1.0f, -0.3f);  // ������ ��
    glVertex2f(-1.0f, -0.3f); // ���� ��

    glEnd();
}

void Player() {
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0f, 0.0f, 1.0f); // �簢���� ���� ���� (��ȫ��)

    // �簢���� �� ������
    glVertex2f(-0.2f, posY - 0.2f); // ���� �Ʒ�
    glVertex2f(0.2f, posY - 0.2f);  // ������ �Ʒ�
    glVertex2f(0.2f, posY + 0.2f);  // ������ ��
    glVertex2f(-0.2f, posY + 0.2f); // ���� ��

    glEnd();
}

void ObstacleDraw(const Obstacle& obstacle) {
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0f, 0.0f, 0.0f); // �簢���� ���� ���� (������)

    // �簢���� �� ������
    glVertex2f(obstacle.posX - 0.2f, obstacle.posY - 0.2f); // ���� �Ʒ�
    glVertex2f(obstacle.posX + 0.2f, obstacle.posY - 0.2f); // ������ �Ʒ�
    glVertex2f(obstacle.posX + 0.2f, obstacle.posY + 0.2f); // ������ ��
    glVertex2f(obstacle.posX - 0.2f, obstacle.posY + 0.2f); // ���� ��

    glEnd();
}

void updateObstacles(float deltaTime) {
    for (auto& obstacle : obstacles) {
        obstacle.posX -= obstacleSpeed * deltaTime;
    }

    // ��ֹ� ����
    spawnTimer += deltaTime;
    if (spawnTimer >= SPAWN_INTERVAL) {
        spawnTimer = 0.0f;
        Obstacle newObstacle = { 1.0f, -0.1f }; // Y ��ġ�� -0.1�� ����
        obstacles.push_back(newObstacle);
    }

    // ��ֹ��� ȭ�� ������ ������ ����
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
    // �߷��� �ӵ��� ��ġ�� ����
    velocityY += GRAVITY * DELTA_TIME;
    // �ӵ��� ��ġ�� ��ġ�� ����
    posY += velocityY * DELTA_TIME;

    // �ٴڿ� ������ ���� ���� ���� �� ��ġ, �ӵ� �ʱ�ȭ
    if (posY <= -0.7f) {
        posY = -0.7f;
        velocityY = 0.0f;
        isJumping = false;
    }

    // ��ֹ� ������Ʈ
    updateObstacles(DELTA_TIME);

    // �浹 �˻�
    if (checkCollision()) {
        std::cout << "Game Over!" << std::endl;
        glfwSetWindowShouldClose(glfwGetCurrentContext(), GLFW_TRUE);
    }
}

int main(void) {
    // GLFW �ʱ�ȭ
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

    std::srand(static_cast<unsigned int>(std::time(0))); // ���� �õ� �ʱ�ȭ

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        update(); // �÷��̾� ���� �� ��ֹ� ������Ʈ

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
