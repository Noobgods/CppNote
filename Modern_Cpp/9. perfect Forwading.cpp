#include<iostream> // 9. 완벽한 전달
#include<vector>
using namespace std;

// L-Value Reference를 인자로 받는 함수에 R-Value를 넘겼을때 해결하는 방법.
// Universal Reference : 타입 추론을 인자로 받을때 좌측값/우측값 참조가 될 수도 있다.

class Class{};
int b;
// R-Value Reference;
Class&& c = Class();

// Universal Reference
auto&& a = b;

// R-Value Reference;
void func(Class&& c);

// R-Value Reference;
template<typename T>
vector<T> func (vector<T>&& v);

// Universal Reference
template<typename T>
void func(T&& t);

/* C++ 참조 규칙
    1. non const lvalue reference는 lvalue만 참조 가능
    2. const lvalue reference는 lvalue / rvalue 둘 다 참조 가능
    3. rvalue reference는 rvalue만 참조가능 (C++11부터 사용 가능)
*/

// 오버로딩을 통해 구현했을때는 원하는대로 동작하지 않는 경우가 있다.

void func(int& i){
    cout<<"This is L-Value Reference"<<endl;
}

void func(int&& i){
    cout<<"This is R-Value Reference"<<endl;
}

// forward 키워드를 사용하지 않으면 L-Value로 인식한다.
template<typename T>
void proc(T&& t){
    func(forward<T>(t));
}

int main(){
    int a = 1;
    proc(a);
    proc(1);
}
