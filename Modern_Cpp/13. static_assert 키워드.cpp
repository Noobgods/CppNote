#include<iostream> // 13. static_assert 키워드

// C언어 조건식 assert(조건식);
// assert 함수의 조건식 -> 참 : 패스 / 거짓 : 에러메세지
// 런타임시 검증되어 컴파일 시에는 검증이 안된다.
// 컴파일시 검증하는것이 static_assert 키워드
// 조건식이 에러일 시 컴파일 에러가 뜬다.

int main(){

    // 상수만 들어갈 수 있다. 변수는 들어갈 수 없다.
    static int n = 3;
    static_assert(1, "error");

    return 0;
}