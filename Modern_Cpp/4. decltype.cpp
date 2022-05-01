#include<iostream>	// 4. decltype 키워드
#include<cstdio>
#include<vector>
#include<typeinfo>
using namespace std;

// decleared type(선언된 형식)의 줄임말 
// 주어진 표현식의 타입을 알려준다.
// auto : 값에 대응하는 타입을 추론
// decltype : 값으로부터 타입을 추론

// 리턴형을 auto로 할 때 리턴값 추론(Cpp11)
auto func1(int x, int y) -> decltype(x+y){
	return x+y;
}

template<typename A, typename B>
auto func2(A a, B b) -> decltype(a+b){
	return a+b;
}

template<typename A, typename B>
auto func3(A a, B b){	// Cpp14 부터는 생략가능
	return a+b;
}

int main(){
	auto a = 1;
	auto b = 2.5;
	decltype(a+b) c = 3; // a+b의 타입으로 결정. double형

	// c 변수의 타입 출력
	cout<<"c : "<< c <<" and type is " << typeid(c).name()<<endl;
	
	// 함수 호출 후 리턴의 타입 출력
	cout<<"a+b : "<< a+b <<" and type is " << typeid(func3(a,b)).name()<<endl;
	return 0;
}