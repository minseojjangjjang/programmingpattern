#include <iostream>

using namespace std;

enum ForeColour //색깔을 표현하는 열거형 선언
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
    int num = 0;    // 입력 받은 숫자를 저장하는 변수
    int rest = 1;     // 나머지 값을 저장하는 변수
    bool okay = true;     // 반복문을 제어하는 변수
    int condition = 32;     // 색깔 조건을 나타내는 변수
    cout << "\x1b[000m" << "화면에 그림을 그리는 프로그램입니다." << endl;
    cout << "학번 : 202327041" << endl;
    cout << "이름 : 조민서" << endl;
    cout << "화면에 그릴 물체코드를 입력하세요 :" << endl;
    cin >> num;    //cin 입력받는 함수 ( 사용자로부터 숫자를 입력 받음)

    while (num != 64)// 입력된 숫자가 64가 아닌 동안 반복
    {
        while (okay)// 입력된 숫자가 64가 아닌 동안 반복
        {
            if (condition == 32)// 색깔 조건이 32인 경우(마젠타)
            {
                rest = num / 32;// 입력된 숫자를 32로 나눈 몫을 계산
                if (num % 32 == 0 || rest >= 1) // 입력된 숫자가 32로 나누어 떨어지거나 몫이 1 이상인 경우
                {
                    rest = 0;
                    cout << "\x1b[035m" << "♥" << endl; //마젠타
                    num -= 32;// 입력된 숫자에서 32를 빼줌
                    if (num % 32 == 0)// 입력된 숫자가 32로 나누어 떨어지는 경우
                    {
                        condition = 0;// 색깔 조건 초기화
                        okay = false;// 반복문 탈출 조건 변경
                        break;
                    }
                }
                condition = 16;// 다음 색깔 조건으로 설정
            }

            else if (condition == 16)
            {
                rest = num / 16;
                if (num % 16 == 0 || rest >= 1)
                {
                    rest = 0;
                    cout << "\x1b[036m" << "♥" << endl;  //시안색
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
                    cout << "\x1b[033m" << "♥" << endl; //누런색
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
                    cout << "\x1b[032m" << "♥" << endl; //초록색
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
                    cout << "\x1b[031m" << "♥" << endl; //뻘건색
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
                    cout << "\x1b[037m" << "♥" << endl; //흰색
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

        cout << "화면에 그릴 물체코드를 입력하세요 :" << endl;// 사용자에게 새로운 숫자를 입력 받음
        cin >> num;
        condition = 32;// 색깔 조건 초기화
        okay = true;// 반복문 제어 변수 초기화
    }

}

/*
* 흰색 블록을 그리는 키코드 : 1 (1)
* 빨강색 블록을 그리는 키코드 : 2 (10)
* 녹색 블록을 그리는 키코드 : 4 (100)
* 노란색 블록을 그리는 키코드 : 8 (1000)
* 청록색 블록을 그리는 키코드 : 16 (10000)
* 마젠타색 블록을 그리는 키코드 : 32 (100000)
* 프로그램 종료 : 64 (1000000)
*
* 프로그램을 시작하면 아래와 같이 쓰시오
*
*
* 화면에 그림을 그리는 프로그램입니다.
* 학번 : 349218347(본인학번)
* 이름 : 본인이름
*
* 화면에 그릴 물체코드를 입력하세요 :
* (반복)
*/



