#include<iostream>
#include<memory>
#include<boost/serialization/access.hpp>
using namespace std;
using namespace boost;

struct Address;
/* # 객체 생성
    아래의 두 객체는 중복된 부분이 있다.
    contact john{ "John Doe", Address{"123 East Dr", "London", 10}};
    contact jane{ "Jane Doe", Address{"123 East Dr", "London", 11}};
    
    john과 jane은 사무실 방만 다르고 같은 건물에서 일하고 있다. (다른 사람들도)
    수많은 객체가 같은 값으로 중복되게 초기화 되는 작업이 발생한다.
    
    프로토타입 패턴은 객체의 복제가 주요기능이다.
*/

/* # 평범한 중복처리
    복제의 목적이 값을 사용하는 것에 있고, 복제 대상 객체의 모든 항목이 값으로만 되어있다면
    복제하는데 문제 될 것이 없다. 예로 연락처와 주소가 다음과 같이 정의되어 있다면,

struct Address{
    string street, city;
    int suite;
};
struct Contact{
    string name;
    Address address;  
};
*/
// 아래와 같은 코드를 사용하는데 문제가 없다.
// <1><main code>

// 실제로 이렇게 쉬운 경우는 드물다.
// 아래 코드와 같이 Address의 내부객체가 포인터로 된 경우가 많다.

// 이 부분은 문제가 있다. Contact john = prototype 코드가 수행될 때 포인터가 복제되기 때문에
// 둘다 같은 객체를 가지게 된다.

// # 복제 생성자를 통한 중복처리

// 복제 생성자를 정의하는데 두가지 방법이 있다. 쉽게는 아래와 같이 구현한다.
struct Contact{
    string name;
    shared_ptr<Address> address;  

    /* 
    Contact(const Contact& other)
        : name{other.name}{
            address = make_shared<Address>(
                other.address->street,
                other.address->city,
                other.address->suite
            );
        }
    */// 주소의 항목이 변경되면 사용할 수 없으므로 위 코드는 범용적이지 않다.
    // Address에 복사생성자를 정의하고 Contact의 생성자를 재활용하여 사용할 수 있다.

    Contact(const Contact& other)
        : name{name}, address{make_shared<Address>(*other.address)}{
    }
    Contact& operator=(const Contact& other){
        if(this == &other)
            return *this;
        name = other.name;
        address = other.address;
        return *this;
    }
    Contact(const string name, const shared_ptr<Address> address)
        : name{name}, address{address}{
    }
};
struct Address{
    string street, city;
    int suite;
    Address(const string& street, const string& city, const int suite)
        : street{street}, city{city}, suite{suite}{}
};

int main(){
    /* <1>
    // 프로토타입 객체
    Contact worker{"", Address{"123 East Dr", "London", 0}};

    // 프로토타입 복제하고 일부 수정
    Contact john = worker;

    john.name = "John Doe";
    john.address.suite = 10;
    */
   
    // 이전과 같이 프로토타입을 생성하면서도 안전하게 재사용이 가능하다.
    Contact worker{"", make_shared<Address>("123 East Dr", "London", 0)};
    Contact john{worker}; // or Contact john = worker;
    john.name = "John";
    john.address->suite = 10;
    
    // 이 방법의 유일한 문제는 온갖 복제 생성자를 하나하나 구현하는데 오래걸린다는 점이다.
    // 예를 들어 다음과 같은 코드가 작성되었다고 하자.

    // Contact john = worker;

    // 그리고 Address에 복제 생성자와 대입 연산자의 구현이 누락되었다고 하자(단 Contact는 구현되어 있다).
    // 이 코드는 컴파일되는데 아무런 문제가 없다. 
    // 복사생성자만 사용된다면 상황이 조금 낫다. 존재하지 않는 복사생성자의 호출이 있으면 에러가 발생하여 문제를 인지할 수 있다.
    // 하지만 대입 연산자는 디폴트 동작이 정해져 있으므로 적절한 대입연산자를 정의하지 않았더라도 컴파일되어 실행된다.

    // 또 다른 문제로 이중 포인터 또는 unique_ptr를 사용한다면 코드 자동생성을 사용할 시에 문제가 생길 수 있다.
    return 0;
}