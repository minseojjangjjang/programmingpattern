#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

int main() {
    // 1�� ������ ��Ÿ���� chrono::duration ��ü ����
    auto duration = chrono::seconds(1);

    // ���� �ð��� �������� ���� �ð� ����
    auto start_time = chrono::steady_clock::now();

    // 1���� 10���� �ݺ� ����
    for (int i = 1; i <= 10; ++i) {
        // ���� �ð� ����
        auto current_time = chrono::steady_clock::now();

        // ���� �ð��� ���� �ð��� ���� ���
        auto elapsed_time = current_time - start_time;

        // 1�� ������ �������� Ȯ��
        if (elapsed_time >= duration) {
            // ���� ���
            cout << i << " ";

            // ���� �ð��� ���� �ð����� ������Ʈ
            start_time = current_time;
        }

        // 1�и��� ���� �޽�
        this_thread::sleep_for(chrono::milliseconds(1));
    }

    cout << endl; // �������� �� �ٲ� �߰�

    return 0;
}