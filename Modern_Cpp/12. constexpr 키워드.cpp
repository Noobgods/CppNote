#include<iostream> // 12. constexpr 키워드
using namespace std;
// const 키워드와 constexpr 키워드의 차이 : 에러 발생 시기
// const : 변수 초기화시 런타임까지 변수의 초기화 지연 가능
// constexpr : 컴파일 타임에 변수의 초기화가 이루어져야 함

// constexpr 변수는 반드시 상수식으로 초기화 되어야 함

// constexpr 함수는 컴파일 타임에 리턴 값을 계산할 수 있다면 수행
// 그렇지 않다면 일반적인 함수처럼 런타임시 리턴값 결정

constexpr int func(int n){
    return n*n;
}

// constexpr 함수의 제약사항
// 1. 정의후에 사용 가능
// 2. 인자에 constexpr을 사용할 수 없음
// 3. 가상함수로 사용할 수 없음
// (C++14부터 가능한 것들)
// 4. 증감연산을 사용할 수 없음 
// 5. 지역변수를 사용할 수 없음
// 6. return 구문은 single state 여야만 함(삼항연산자 사용가능)

int main(){
    constexpr int a = 1;
    constexpr int b = {1}; 
    //constexpr int c; error
    int d = 1;
    //constexpr int e = d + 2; error
    //constexpr int f = time(NULL); error

    int n;
    cin >> n;
    cout << func(n) <<endl; // 런타임
    cout << func(1) <<endl; // 컴파일
    return 0;
}