#include <iostream>
using namespace std;

// # Pimpl 관례
/* Pimpl (Pointer to Implementation)
    구현부를 포인터로 참조하는 관례
*/

struct Person{
    string name;
    void greet();

    Person();
    ~Person();

    class PersonImpl;
    PersonImpl *impl; // gsl::owner<T>를 활용하기 좋은 멤버
};
// PersonImpl은 무엇인가?
// 클래스의 구현부를 다른 클래스(PersonImpl)에 숨기고자 하는 의도에서 발생한다.
// 구현 클래스 PersonImpl을 헤더파일이 아닌 .cpp 파일에 정의하는 것이 핵심적이다.

// PersonImpl의 정의는 아래와 같다.
struct Person::PersonImpl{
    void greet(Person* p);
};

// Person 클래스는 PersonImpl를 전방 선언(forward-declare)하고 포인터로 관리한다.
// Person의 생성자와 소멸자에서는 PersonImpl의 포인터를 초기화하고 삭제한다.

Person::Person() : impl(new PersonImpl){}
Person::~Person() {delete impl;}

// 이제 greet를 구현한다.

void Person::greet(){
    impl->greet(this);
}

void Person::PersonImpl::greet(Person *p){
    cout << "hello " << p->name << endl;
}

/* Pimpl의 장점
 - 클래스의 구현부의 상당부분이 실제로 감춰질 수 있다. 꼭 필요한 public 인터페이스만 노출 가능
 - 바이너리 호환성을 보증하기 쉬워진다. 숨겨진 구현 클래스에 대한 수정은 바이너리 호환성에 영향을 안미친다.
 - 헤더파일이 멤버 선언에 필요한 헤더들만 인클루드하게 할 수 있다.
*/