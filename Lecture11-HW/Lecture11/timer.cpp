#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

int main()
{
    int count = 0;
    int thousand = 1010;
    chrono::steady_clock::time_point prev_end = chrono::steady_clock::now();//현재시각 타임포인트 이전에 끝난 시간 = 현재 시간 지금
    chrono::steady_clock::time_point end = chrono::steady_clock::now();//현재시각 타임포인트 끝난 시간 = 현재 시간 지금

    while (count < 10)//10보다 작을 때까지
    {
        prev_end = end; //이전에 끝난 건 = 지금 끝난 거
        end = chrono::steady_clock::now(); //지금 끝난 거는 = 지금 현재 시간
        chrono::steady_clock::duration diff = end - prev_end; //현재 시간 사이의 시간 = 끝난 거 - 이전에 끝난거        종료 - 시작 = 걸린 시간(차이)
        auto duration_ns = chrono::duration_cast<chrono::milliseconds>(diff).count(); // 사이 시간 = 차이

        count++;
        cout << count << " dur: " << duration_ns << endl;

        this_thread::sleep_for(chrono::milliseconds(1000));
    }
}