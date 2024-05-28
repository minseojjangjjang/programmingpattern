#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

int main()
{
    int count = 0;
    int thousand = 1010;
    chrono::steady_clock::time_point prev_end = chrono::steady_clock::now();//����ð� Ÿ������Ʈ ������ ���� �ð� = ���� �ð� ����
    chrono::steady_clock::time_point end = chrono::steady_clock::now();//����ð� Ÿ������Ʈ ���� �ð� = ���� �ð� ����

    while (count < 10)//10���� ���� ������
    {
        prev_end = end; //������ ���� �� = ���� ���� ��
        end = chrono::steady_clock::now(); //���� ���� �Ŵ� = ���� ���� �ð�
        chrono::steady_clock::duration diff = end - prev_end; //���� �ð� ������ �ð� = ���� �� - ������ ������        ���� - ���� = �ɸ� �ð�(����)
        auto duration_ns = chrono::duration_cast<chrono::milliseconds>(diff).count(); // ���� �ð� = ����

        count++;
        cout << count << " dur: " << duration_ns << endl;

        this_thread::sleep_for(chrono::milliseconds(1000));
    }
}