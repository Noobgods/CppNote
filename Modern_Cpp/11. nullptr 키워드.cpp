#include<iostream> // 11. nullptr 키워드
using namespace std;

// 널포인터 키워드
// 포인터에 NULL이나 0을 넣을시 정수형으로 추론될 수 있음.
// nullptr은 클래스이다.
int main(){
    char* ptrnull = nullptr;
    cout << sizeof(nullptr);
}