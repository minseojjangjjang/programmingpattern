#include <iostream>

using namespace std;

enum ForeColour //������ ǥ���ϴ� ������ ����
{
    Default = 0,
    Black = 30,
    Red = 31,
    Green = 32,
    Yellow = 33,
    Blue = 34,
    Magenta = 35,
    Cyan = 36,
    White = 37,
};

int main()
{
    int num = 0;    // �Է� ���� ���ڸ� �����ϴ� ����
    int rest = 1;     // ������ ���� �����ϴ� ����
    bool okay = true;     // �ݺ����� �����ϴ� ����
    int condition = 32;     // ���� ������ ��Ÿ���� ����
    cout << "\x1b[000m" << "ȭ�鿡 �׸��� �׸��� ���α׷��Դϴ�." << endl;
    cout << "�й� : 202327041" << endl;
    cout << "�̸� : ���μ�" << endl;
    cout << "ȭ�鿡 �׸� ��ü�ڵ带 �Է��ϼ��� :" << endl;
    cin >> num;    //cin �Է¹޴� �Լ� ( ����ڷκ��� ���ڸ� �Է� ����)

    while (num != 64)// �Էµ� ���ڰ� 64�� �ƴ� ���� �ݺ�
    {
        while (okay)// �Էµ� ���ڰ� 64�� �ƴ� ���� �ݺ�
        {
            if (condition == 32)// ���� ������ 32�� ���(����Ÿ)
            {
                rest = num / 32;// �Էµ� ���ڸ� 32�� ���� ���� ���
                if (num % 32 == 0 || rest >= 1) // �Էµ� ���ڰ� 32�� ������ �������ų� ���� 1 �̻��� ���
                {
                    rest = 0;
                    cout << "\x1b[035m" << "��" << endl; //����Ÿ
                    num -= 32;// �Էµ� ���ڿ��� 32�� ����
                    if (num % 32 == 0)// �Էµ� ���ڰ� 32�� ������ �������� ���
                    {
                        condition = 0;// ���� ���� �ʱ�ȭ
                        okay = false;// �ݺ��� Ż�� ���� ����
                        break;
                    }
                }
                condition = 16;// ���� ���� �������� ����
            }

            else if (condition == 16)
            {
                rest = num / 16;
                if (num % 16 == 0 || rest >= 1)
                {
                    rest = 0;
                    cout << "\x1b[036m" << "��" << endl;  //�þȻ�
                    num -= 16;
                    if (num % 16 == 0)
                    {
                        condition = 0;
                        okay = false;
                        break;
                    }
                }
                condition = 8;
            }

            else if (condition == 8)
            {
                rest = num / 8;
                if (num % 8 == 0 || rest >= 1)
                {
                    rest = 0;
                    cout << "\x1b[033m" << "��" << endl; //������
                    num -= 8;
                    if (num % 8 == 0)
                    {
                        condition = 0;
                        okay = false;
                        break;
                    }
                }
                condition = 4;
            }

            else if (condition == 4)
            {
                rest = num / 4;
                if (num % 4 == 0 || rest >= 1)
                {
                    rest = 0;
                    cout << "\x1b[032m" << "��" << endl; //�ʷϻ�
                    num -= 4;
                    if (num % 4 == 0)
                    {
                        condition = 0;
                        okay = false;
                        break;
                    }
                }
                condition = 2;
            }

            else if (condition == 2)
            {
                rest = num / 2;
                if (num % 2 == 0 || rest >= 1)
                {
                    rest = 0;
                    cout << "\x1b[031m" << "��" << endl; //���ǻ�
                    num -= 2;
                    if (num % 2 == 0)
                    {
                        condition = 0;
                        okay = false;
                        break;
                    }
                }
                condition = 1;
            }

            else if (condition == 1)
            {
                rest = num / 1;
                if (num % 1 == 0 || rest >= 1)
                {
                    rest = 0;
                    cout << "\x1b[037m" << "��" << endl; //���
                    num -= 1;
                    if (num % 1 == 0)
                    {
                        condition = 0;
                        okay = false;
                        break;
                    }
                }
                condition = 0;
            }
        }

        cout << "ȭ�鿡 �׸� ��ü�ڵ带 �Է��ϼ��� :" << endl;// ����ڿ��� ���ο� ���ڸ� �Է� ����
        cin >> num;
        condition = 32;// ���� ���� �ʱ�ȭ
        okay = true;// �ݺ��� ���� ���� �ʱ�ȭ
    }

}

/*
* ��� ����� �׸��� Ű�ڵ� : 1 (1)
* ������ ����� �׸��� Ű�ڵ� : 2 (10)
* ��� ����� �׸��� Ű�ڵ� : 4 (100)
* ����� ����� �׸��� Ű�ڵ� : 8 (1000)
* û�ϻ� ����� �׸��� Ű�ڵ� : 16 (10000)
* ����Ÿ�� ����� �׸��� Ű�ڵ� : 32 (100000)
* ���α׷� ���� : 64 (1000000)
*
* ���α׷��� �����ϸ� �Ʒ��� ���� ���ÿ�
*
*
* ȭ�鿡 �׸��� �׸��� ���α׷��Դϴ�.
* �й� : 349218347(�����й�)
* �̸� : �����̸�
*
* ȭ�鿡 �׸� ��ü�ڵ带 �Է��ϼ��� :
* (�ݺ�)
*/



