#include<iostream>	// 1. auto 키워드
#include<cstdio>
#include<vector>
using namespace std;

// 타 언어의 var 키워드와 비슷한 역할을 한다.
// 특정 자료형을 지정하지 않고 선언한다.
// 초기화값이 반드시 필요하고, 전역변수와 함수의 매개변수로 사용 불가하다.
int main(){
	auto Integer = 10;
	auto Long = 10L;
	auto Double = 100.999;
	auto String = "string";
	
	// 레퍼런스형 사용
	auto& a= Integer;

	// 포인터, 함수포인터 사용
	auto* Func = printf;
	Func("%s\n", String);

	// STL의 iterator형을 대신 할 수 있다.
	vector<int> v;
	auto begin = v.begin();

	// 구조체, 클래스에 사용
	class A {
	public:
		int a;
		char *b;
	};
	auto s = A();

	return 0;
}