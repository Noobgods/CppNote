#include<iostream>
using namespace std;

// R-value Reference(우측값 참조)
/* 
        좌측값(L-Value) 우측값(R-Value)
    int a              =3
    
    우측값은 표현식이 종료되면 더이상 존재하지 않게됨. (임시개체)
    크기가 큰 자료형일 경우에 복사를 반복적으로 할경우 오버헤드가 발생할 수 있다.
    우측값 참조는 우측값을 파괴하지 않고 우측값을 그대로 참조할 수 있게 한다.
    그러므로 크기가 큰 자료형을 참조할때 우측값 참조를 사용하면 오버헤드를 줄일 수 있다.
    
*/
template<typename T>
class X{
    public:
    X& operator=(T&& rhs){   // 우측값을 참조함
        this->value = rhs;
        return *this;
    }
    
    T getValue(){return this->value;};
    private:
    T value;
};

int main(){
    int a = 5;      // L = R
    int b = a;      // L = L
    int c = a++;    // L = R
    int d = ++a;    // L = L
    int& e = b;     // L = L
    int f = b + c;  // L = R
    int* g = &a;    // L = R

    X<int> x;
    x = 5;  // 우측값 참조를 통해 5가 유지되고 그 값을 받음
    
    cout<< x.getValue() <<endl; 
    return 0;
}