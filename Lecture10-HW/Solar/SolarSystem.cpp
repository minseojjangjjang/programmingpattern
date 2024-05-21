#pragma comment(lib, "Opengl32.lib")
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#define PI 3.141592
#include<math.h>

float moveFactor = 0.0f;
float scaleFactor = 1.0f;

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
    if (key == GLFW_KEY_UP && action == GLFW_PRESS)
    {
        moveFactor += 0.01f;
    }
    if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
    {
        scaleFactor += 0.1f;
    }
}

//int setVertexRotation(float x, float y, float angle_degree)
//{
//	glColor3f(0.7f, 0.8f, 0.85f);
//	glVertex2f(x * cos(-angle_degree) - (y * sin(-angle_degree)), x * sin(-angle_degree) + (y * cos(-angle_degree)));
//	return 0;

//}�ݴ�� ȸ���ϴ°�


int setVertexRotation(float x, float y, float angle_degree, float cx, float cy, float r, float g, float b)
{
    glColor3f(r, g, b);
    glVertex2f(cx + (x * cos(angle_degree) - y * sin(angle_degree)), cy + (x * sin(angle_degree) + y * cos(angle_degree)));
    return 0;
}


int setVertexRotation2(float x, float y, float angle_degree, float cx, float cy, float r, float g, float b) {

    glColor3f(r, g, b);
    float scaled_x = x * 0.25;//1/4�� ���
    float scaled_y = y * 0.25;//ũ�� 
    glVertex2f(cx + (x * cos(angle_degree) - scaled_y * sin(angle_degree)), cy + (scaled_x * sin(angle_degree) + y * cos(angle_degree)));//x,y
    return 0;

}

float angle_circle = 1.0f;
float angle_star = 0.01f; // ���� ȸ�� ����
float angle_star_orbit = 0.01f;
float angle_square_orbit = 0.01f; // �簢���� �˵� ȸ�� ����->����
float angle_square_self = 0.01f; // �簢���� ��ü ȸ�� ����->����
float circle_radius_star = 0.15f; // ���� ���� ���� ������
float circle_radius_square = 0.8f; // �簢���� ���� ���� ������
const float rotationSpeed_square_self = 2 * PI / 6000; // 100�ʿ� �� ����
const float rotationSpeed_square_orbit = 2 * PI / 36000; // 10�п� �� ����
const float rotationSpeed_star = 2 * PI / 1800; // 30�ʿ� �� ����
const float rotationSpeed_circle = 2 * PI / 1800;


int render()
{

    // �簢���� �߽� ��ǥ
    float square_center_x = circle_radius_square * cos(angle_square_orbit);
    float square_center_y = circle_radius_square * sin(angle_square_orbit);

    glLineWidth(3.0f);
    glBegin(GL_LINE_LOOP);
    setVertexRotation(-0.04f, -0.04f, angle_square_self, square_center_x, square_center_y, 0.0f, 0.0f, 0.0f); // �Ķ���
    setVertexRotation(0.04f, -0.04f, angle_square_self, square_center_x, square_center_y, 0.0f, 0.0f, 0.0f);  // �Ķ���
    setVertexRotation(0.04f, 0.04f, angle_square_self, square_center_x, square_center_y, 0.0f, 0.0f, 0.0f);   // �Ķ���
    setVertexRotation(-0.04f, 0.04f, angle_square_self, square_center_x, square_center_y, 0.0f, 0.0f, 0.0f);  // �Ķ���
    glEnd();

    glBegin(GL_QUADS);
    // �簢�� �׸��� (��ü ȸ�� ����)
    setVertexRotation(-0.04f, -0.04f, angle_square_self, square_center_x, square_center_y, 0.0f, 0.0f, 1.0f);
    setVertexRotation(0.04f, -0.04f, angle_square_self, square_center_x, square_center_y, 0.0f, 0.0f, 1.0f);
    setVertexRotation(0.04f, 0.04f, angle_square_self, square_center_x, square_center_y, 0.0f, 0.0f, 1.0f);
    setVertexRotation(-0.04f, 0.04f, angle_square_self, square_center_x, square_center_y, 0.0f, 0.0f, 1.0f);
    glEnd();

    // ���� �߽� ��ǥ
    float star_center_x = square_center_x + circle_radius_star * cos(angle_star);//�簢�� ����+�������� ũ��(�����̵�)
    float star_center_y = square_center_y + circle_radius_star * sin(angle_star);

    glLineWidth(1.0f);
    glBegin(GL_LINE_LOOP);

    setVertexRotation(-0.05f, 0.04f, angle_star, star_center_x, star_center_y, 0.0f, 0.0f, 0.0f); // �Ķ���
    setVertexRotation(0.02f, 0.04f, angle_star, star_center_x, star_center_y, 0.0f, 0.0f, 0.0f); // �Ķ���
    setVertexRotation(0.04f, 0.03f, angle_star, star_center_x, star_center_y, 0.0f, 0.0f, 0.0f); // �Ķ���
    setVertexRotation(0.05f, 0.04f, angle_star, star_center_x, star_center_y, 0.0f, 0.0f, 0.0f); // �Ķ���
    setVertexRotation(-0.02f, 0.04f, angle_star, star_center_x, star_center_y, 0.0f, 0.0f, 0.0f); // �Ķ���
    setVertexRotation(-0.04f, -0.03f, angle_star, star_center_x, star_center_y, 0.0f, 0.0f, 0.0f); // �Ķ���
    setVertexRotation(0.0f, 0.08f, angle_star, star_center_x, star_center_y, 0.0f, 0.0f, 0.0f); // �Ķ���
    setVertexRotation(-0.03f, 0.0f, angle_star, star_center_x, star_center_y, 0.0f, 0.0f, 0.0f); // �Ķ���
    setVertexRotation(0.03f, 0.0f, angle_star, star_center_x, star_center_y, 0.0f, 0.0f, 0.0f); // �Ķ���
    glEnd();

    glBegin(GL_TRIANGLES);
    // �� �׸���
    setVertexRotation(-0.05f, 0.04f, angle_star, star_center_x, star_center_y, 1.0f, 1.0f, 0.0f); // �Ķ���
    setVertexRotation(0.02f, 0.04f, angle_star, star_center_x, star_center_y, 1.0f, 1.0f, 0.0f); // �Ķ���
    setVertexRotation(0.04f, -0.03f, angle_star, star_center_x, star_center_y, 1.0f, 1.0f, 0.0f); // �Ķ���
    setVertexRotation(0.05f, 0.04f, angle_star, star_center_x, star_center_y, 1.0f, 1.0f, 0.0f); // �Ķ���
    setVertexRotation(-0.02f, 0.04f, angle_star, star_center_x, star_center_y, 1.0f, 1.0f, 0.0f); // �Ķ���
    setVertexRotation(-0.04f, -0.03f, angle_star, star_center_x, star_center_y, 1.0f, 1.0f, 0.0f); // �Ķ���
    setVertexRotation(0.0f, 0.08f, angle_star, star_center_x, star_center_y, 1.0f, 1.0f, 0.0f); // �Ķ���
    setVertexRotation(-0.03f, 0.0f, angle_star, star_center_x, star_center_y, 1.0f, 1.0f, 0.0f); // �Ķ���
    setVertexRotation(0.03f, 0.0f, angle_star, star_center_x, star_center_y, 1.0f, 1.0f, 0.0f); // �Ķ���
    glEnd();

    // ū ���� �߽� ��ǥ
    float big_circle_center_x = 0.0f;
    float big_circle_center_y = 0.0f;

    glLineWidth(20.0f);
    glBegin(GL_LINE_LOOP);
    for (float angle = 0; angle <= 360; angle += 1) {
        setVertexRotation(0.4, 0.4, angle + angle_circle, big_circle_center_x, big_circle_center_y, 1.0f, 0.5f, 0.0f); // ȸ�� ���� ����
    }
    glEnd();
    // ū �� �׸���
    glBegin(GL_TRIANGLE_FAN);
    for (float angle = 0; angle <= 360; angle += 1) {
        setVertexRotation(0.4, 0.4, angle + angle_circle, big_circle_center_x, big_circle_center_y, 1.0f, 0.843f, 0.0f); // ȸ�� ���� ����
    }
    glEnd();

    // ���� ���� �߽� ��ǥ
    float small_circle_center_x = 0.0f;
    float small_circle_center_y = 0.3;

    // ū ���� ȸ�� ������ ���� ���� ���� ��ǥ ��ȯ//ȸ�����
    float rotated_small_circle_center_x = small_circle_center_x * cos(angle_circle) - small_circle_center_y * sin(angle_circle);
    float rotated_small_circle_center_y = small_circle_center_x * sin(angle_circle) + small_circle_center_y * cos(angle_circle);

    glBegin(GL_TRIANGLE_FAN);
    for (float angle = 0; angle <= 360; angle += 1) {
        setVertexRotation(0.1, 0.1, angle + angle_circle, rotated_small_circle_center_x, rotated_small_circle_center_y, 1.0f, 0.91f, 0.76f); // ȸ�� ���� ����
    }
    glEnd();

    // ���� ���� �߽� ��ǥ
    small_circle_center_x = 0.0f;
    small_circle_center_y = -0.4f;

    // ū ���� ȸ�� ������ ���� ���� ���� ��ǥ ��ȯ//�����̵�
    rotated_small_circle_center_x = small_circle_center_x * cos(angle_circle) - small_circle_center_y * sin(angle_circle);//ȸ����ȯ
    rotated_small_circle_center_y = small_circle_center_x * sin(angle_circle) + small_circle_center_y * cos(angle_circle);

    glBegin(GL_TRIANGLE_FAN);//angle�� ��
    for (float angle = 0; angle <= 360; angle += 1) {
        setVertexRotation2(0.1, 0.1, angle + angle_circle, rotated_small_circle_center_x, rotated_small_circle_center_y, 1.1f, 0.9273f, 0.0f); // ȸ�� ���� ����
    }
    glEnd();

    angle_star += rotationSpeed_star; // ���� ȸ�� �ӵ�
    angle_star_orbit += rotationSpeed_star;//���� �˵� ȸ�� �ӵ�
    angle_square_orbit += rotationSpeed_square_orbit; // �簢���� �˵� ȸ�� �ӵ�
    angle_square_self += rotationSpeed_square_self; // �簢���� ��ü ȸ�� �ӵ�
    angle_circle += rotationSpeed_circle;// ������ ȸ��

    //angle_star += 0.0003f;//5��49��

    return 0;
}

int main(void)
{
    if (!glfwInit())
        return -1;

    GLFWwindow* window;
    window = glfwCreateWindow(1000, 1000, "MuSoeunEngine", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetErrorCallback(errorCallback);
    glfwSetKeyCallback(window, keyCallback);

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
        render();
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}