//과제물 프로젝트명: Lecture04_HW
//idle : 화면색 검정색으로 clear
//마우스 오른쪽 KeyDown하면 : 빨간색
//마우스 오른쪽 KeyUp하면 : 원상복구
//마우스 왼쪽 KeyDown하면 : 녹색
//마우스 왼쪽 KeyUp하면 : 원상복구
//마우스 오른쪽 KeyDown하고 드래그 중이면 : 파랑색
//마우스 왼쪽 KeyDown하고 드래그 중이면 : 마젠타색

//학번 : 202327041
//이름 : 조민서

#pragma comment (lib, "OpenGL32.lib")
#include <GLFW/glfw3.h>
#include <iostream>

bool IsRightBtnDown = false; 
bool IsLeftBtnDown = false; 
bool IsRightBtnDrag = false; 
bool IsLeftBtnDrag = false; 

// 마우스 클릭 콜백 함수(마우스 클릭 이벤트가 발생했을 때 호출되는 함수, 이벤트에 대한 응답,처리를 담당)
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_RIGHT) // 우클릭 시 동작
    {
        if (action == GLFW_PRESS) // 마우스를 클릭했을 때
        {
            IsRightBtnDown = true;//우클릭은 참
            IsRightBtnDrag = false;//우클릭드래그는 거짓
        }
        else if (action == GLFW_RELEASE) // 마우스 클릭을 해제했을 때
            IsRightBtnDown = false;//우클릭을 거짓으로
    }
    else if (button == GLFW_MOUSE_BUTTON_LEFT) // 왼쪽 마우스 버튼 클릭 시 동작
    {
        if (action == GLFW_PRESS) // 마우스를 클릭했을 때
        {
            IsLeftBtnDown = true;//좌클릭은 참
            IsLeftBtnDrag = false; //좌클릭드래그는 거짓
        }
        else if (action == GLFW_RELEASE) // 마우스 클릭을 해제했을 때
            IsLeftBtnDown = false;//좌클릭을 거짓으로
    }
}

// 마우스 이동 콜백 함수(마우스 이동 이벤트가 발생했을 때 실행되는 함수로서, 이벤트에 대한 응답,처리 담당)
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
    //마우스 커서의 위치가 변경될 때마다 호출되는 콜백 함수-> 두번째와 세번째 매개변수인 xpos와ypos를 통해 마우스커서의 현재 위치를 전달받음
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) // 오른쪽 마우스 버튼을 누른 상태가 지속될 때
    {
        IsRightBtnDrag = true; //오른쪽 드래그 중일 때 참
        IsLeftBtnDrag = false; //왼쪽 드래그 중일 때 거짓
        glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // 화면을 파란색으로 변경
    }
    else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) // 왼쪽 마우스 버튼을 누른 상태가 지속될 때
    {
        IsRightBtnDrag = false; //오른쪽 드래그 중일 때 거짓
        IsLeftBtnDrag = true; //왼쪽 드래그 중일 때 참
        glClearColor(1.0f, 0.0f, 1.0f, 1.0f); // 화면을 보라(마젠타)색으로 변경
    }
    else
    {
        IsRightBtnDrag = false; //오른쪽 드래그 중일 때 거짓
        IsLeftBtnDrag = false; //왼쪽 드래그 중일 때 거짓
    }

    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);
}

int main() {
    // GLFW 초기화
    if (!glfwInit()) {
        std::cerr << "GLFW 초기화 실패" << std::endl;
        return -1;
    }

    // GLFW 윈도우 생성
    GLFWwindow* window = glfwCreateWindow(1280, 760, "OpenGL Window", NULL, NULL);
    if (!window) {
        std::cerr << "GLFW 윈도우 생성 실패" << std::endl;
        glfwTerminate();
        return -1;
    }

    // 윈도우 컨텍스트 설정
    glfwMakeContextCurrent(window);
    // 마우스 클릭 콜백 함수 등록
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    // 마우스 이동 콜백 함수 등록
    glfwSetCursorPosCallback(window, cursor_position_callback);
    // 화면 처리 속도 증가 메서드
    glfwSwapInterval(1);

    //구동 루프
    while (!glfwWindowShouldClose(window)) {//윈도우가 닫혓는지 여부를 확인하는 함수 윈도우가 닫혓다면 true를 반환
        glfwPollEvents();//각 반복마다 이 함수가 호출되어 이벤트를 처리함 (마우스 입력, 키 입력, 윈도우 크기 변경 등)

        if (IsRightBtnDown) // 오른쪽 마우스를 누르면
        {
            glClearColor(1.0f, 0.0f, 0.0f, 1.0f); // 화면을 빨간색으로 변경
        }
        else if (IsLeftBtnDown)
        {
            glClearColor(0.0f, 1.0f, 0.0f, 1.0f); // 화면을 초록색으로 변경
        }
        else
        {
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // 아무것도 안 누른 상태면 화면을 검정색으로 변경
        }

        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
    }

    // GLFW 종료
    glfwTerminate();
    return 0;
}