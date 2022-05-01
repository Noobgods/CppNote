#include<iostream>
using namespace std;

// 1. 이상한 재귀 템플릿 패턴 (Curiously Recurring Template Pattern)
// 자기자신을 베이스의 템플릿 인자로 상속받는 패턴

// 베이스 클래스의 구현부에서 타입이 지정된 this 포인터를 사용할 수 있음
// 서브클래스에 begin()/end() 인터페이스가 구현되어 있지 않으면 실행 불가
// CRTP를 적용하면 this를 서브 클래스 타입으로 캐스팅 가능
template <typename Derived>
struct SomeBase{
    void foo(){
        for(auto& item : *static_cast<Derived*>(this)){
            //...
        }
    }
};

struct Foo : SomeBase<Foo>{
    //...
};

// 2. 첨가(Mixin) 상속
// 자기 자신을 템플릿 인자로 하는 정의
// 첨가 상속을 이용하면 계층적으로 여러 타입을 합성할 수 있다.
template <typename T> struct Mixin : T{
    //...
};
// 예로 Foo<Bar<Baz>> x; 와 같이 변수를 선언하면 새로운 타입을 구현하지 않고 세가지 속성을 가짐

// 3. 속성
// get/set 메서드를 가지는 클래스 내부 변수 : 속성
// __declspec을 사용하면 자동으로 get/set 메서드 호출 (VS community)
class person{
    int age_;
public:
    int get_age() const { return age_;}
    void set_age(int value) {age_ = value;}

    // MS표준이기 때문에 VScommunity이외(ex G++)에 실행 불가
    //__declspec(property(get=get_age, put=set_age)) int age; 
};

int main(){

    return 0;
}