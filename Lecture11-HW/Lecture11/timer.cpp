#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

int main() {
    // 1초 간격을 나타내는 chrono::duration 객체 생성
    auto duration = chrono::seconds(1);

    // 현재 시간을 기준으로 시작 시간 설정
    auto start_time = chrono::steady_clock::now();

    // 1부터 10까지 반복 루프
    for (int i = 1; i <= 10; ++i) {
        // 현재 시간 측정
        auto current_time = chrono::steady_clock::now();

        // 시작 시간과 현재 시간의 차이 계산
        auto elapsed_time = current_time - start_time;

        // 1초 간격이 지났는지 확인
        if (elapsed_time >= duration) {
            // 숫자 출력
            cout << i << " ";

            // 시작 시간을 현재 시간으로 업데이트
            start_time = current_time;
        }

        // 1밀리초 동안 휴식
        this_thread::sleep_for(chrono::milliseconds(1));
    }

    cout << endl; // 마지막에 줄 바꿈 추가

    return 0;
}