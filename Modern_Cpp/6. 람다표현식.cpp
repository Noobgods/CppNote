#include<iostream> // 6. 람다표현식
#include<functional>
using namespace std;

// 이름없는 함수로 불림.
// 코딩이 간편해지고 코드의 가독성 향상
// 한 번 사용하고 사용하지 않는 함수는 코드 전체를 볼때 가독성이 떨어짐
// 이때 해당 스코프 내에서 람다 함수를 사용하면 편리하고 가독성 향상
// 또한 STL의 알고리즘을 더 간편하게 사용하게 해줌.
// 무엇보다 수십줄읠 코드를 단 몇 줄로 줄여주는 효과를 준다.

/* 기본문법
[captures](parameters)mutable -> return type { body } (execute);

captures{
    람다식의 본문이 바깥쪽 범위의 변수에 액세스할 변수들을 캡처한다.
    변수명, =(call by value), &(call by reference) 가 들어간다.
    비워두면 아무것도 사용하지 않는다는 뜻이다.
    ex) [=], [&], [a,&b], [this] 
    
    call by value 로 캡쳐된 변수들은 lambda body 에서 변수가 새로 만들어지고 const 키워드가 붙는다.
    그러므로 lambda body에서 변수의 수정이 불가능해진다. (mutable 키워드 사용하면 가능)
    
    전역변수 캡처 불가
    전역변수를 캡쳐하려면 [&] or [=]를 이용해야 한다.

    C++14 부터 [a=1+2] 와 같은 초기화 캡쳐 구문 생김
}
parameters{
    인자값.
    C++14 부터 auto 키워드 통해 선언 가능
    생략 가능
}
mutable{
    mutable 키워드를 사용시 call by value로 캡쳐된 변수들이 const키워드가 붙지않음
    그러나 [=]는 call by value 이기 때문에 lambda body 내부에서만 일시적으로 값을 변경 
}
return type{
    리턴형을 명시해줄때는 후행 반환 형식 사용
    생략, 추론 가능
    C++11 은 리턴이 한번만 나타나거나 없는 경우 자동타입 추론
    lambda body 내의 모든 반환형이 동일한 경우 자동타입 추론
}
body{
    함수 내용
}
excute{
    lambda식 선언 즉시 함수 실행할 경우 () 연산자 통해 함수 실행
}
*/
auto k= 5;
auto getLambda() {
    return [&]() {k=4; cout<<k<<endl;};
}

class Person {
private:
    string name;
public:
    Person(string _name) : name(_name){}
    void show(){
        [this]() {cout << name << endl;}();
    }
};
int main(){
    auto a = 5;

    // 기본 사용법
    [&](){a = 1; cout << a << endl;}();

    // 함수 포인터 사용 (auto 이용)
    auto func1 = [&](){a = 2; cout<<a<<endl;};
    func1();

    // 함수 포인터 사용 (std::function 이용)
    std::function<void()> func2 = [&](){a = 3; cout<<a<<endl;};
    func2();

    // 람다 반환 함수
    auto func3 = getLambda();
    func3();

    // 람다속 람다
    auto func4 = [&](){return [&](){a=5; return a;}();};
    cout<<func4()<<endl;

    // 재귀 람다
    // 함수 포인터 시엔 auto를 많이 사용하지만, 재귀로 할때는 std::function 사용
    std::function<int(int)> func5 = [&func5](int num) -> int{
        if(num <= 1) return 1;
        else return num* func5(num-1);
    };
    auto fact = func5(5);
    cout<<fact<<endl;

    return 0;
}