#pragma once
#include <GLFW/glfw3.h>

extern float blockX;
extern float blockY;
extern float velocityY;
extern bool isJumping;
extern const float gravity;
extern const float jumpForce;
extern float obstacleX;
extern const float obstacleWidth;
extern const float obstacleHeightLow;
extern const float obstacleHeightHigh;
extern const float obstacleSpeed;
extern float currentObstacleSpeed;
extern const float groundY;
extern bool isLowObstacle;

void errorCallback(int error, const char* description);
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
int Player(float deltaTime);
int Ground();
int Obstacle(float deltaTime);
void CheckCollision();
