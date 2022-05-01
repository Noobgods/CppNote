#include<iostream>
#include<vector>
#include<algorithm>
#include<any>
using namespace std;

/* # 속성 관찰자
struct Person{
    int age;
    Person(int age) : age{age}{}
}
    폴링을 하여 사람의 나이가 변경되는 것을 알 수 있지만 
    매 100msec마다 현재나이를 읽어 직전의 나이와 비교하는 것은 상당히 비효율적이다.

struct Person {
    int get_age() const {return age;}
    void set_age(const int value) {age= value;}

private:
    int age;
};

    이제 set_age()가 호출되어 값이 바뀔때마다 어떤 알림을 보내면 된다. 그런데 어떻게 보낼 수 있을까

*/

// # Observer<T>
// Person의 변화에 관심을 가지는 쪽에서 사용할 수 있도록 콜백 함수를 정의하여 베이스 클래스에 두는 것이다.
/*
struct Personlistener{
    virtual void person_changed(Person& p, const string& property_name, const any new_value) = 0;
};
*/// 하지만 이러한 접근 방법은 Person 타입에 한정되어 있다.
// 아래의 Observer 정의로 여러 타입의 클래스를 모니터링 할 수 있다.
template<typename T> struct Observer{
    virtual void field_changed(T& source, const string& field_name) = 0;
};

/* 예를 들어 쓰기 작업이 있을때마다 콘솔에 메세지를 출력하고 싶다면 아래와 같이 작성한다.
struct ConsolePersonObserver : Observer<Person>{
    void field_changed(Person& source, const string& field_name) override{
        cout << "Person's "<< field_name << " has changed to " << source.get_age() << ".\n";
    }
};

struct Creature;
// 복수의 클래스들의 필드값을 모니터링 하기 위해선 아래와 같이 작성한다.
struct ConsolePersonObserver : Observer<Person>, Observer<Creature>{
    void field_changed(Person& source, const string& field_name) override{...}
    void field_changed(Creature& source, const string& field_name) override{...}
};
*/

// # Observerable<T>
//Person을 모니터링이 가능한 Observable 클래스로 만들어 본다. 
/* Observable은 다음과 같은 책임을 갖게 된다.
    - Person의 변경을 모니터링 하려는 관찰자들을 private 리스트로 관리한다.
    - 관찰자가 Person의 변경 이벤트에 수신 등록 또는 해제(subscribe()/unsubscribe())할 수 있게 한다.
    - notify()를 통해 변경 이벤트가 발생했을 때 모든 관찰자에게 정보가 전달되도록 한다.
*/

template<typename T> struct Observable{
    void notify(T& source, const string& name);
    void subscribe(Observer<T>* f) { 
        observers.push_back(f);
    }
    void unsubscribe(Observer<T>* f){
        //...
    }
private:
    vector<Observer<T>*> observers;
};
// private로 관찰자 목록이 임의로 수정되는 것을 막는다.
// 다음으로 notify를 구현한다. 모든 관찰자를 순회하며 관찰자의 field_changed()를 차례로 호출한다.

template<typename T>
void Observable<T>::notify(T& source, const string& name){
    for(auto obs : observers){
        obs->field_changed(source, name);       
    }
}

// Observable<T> 를 상속받는 것만으로는 부족하다. 
// 관찰 받는 클래스에서도 자신의 필드가 변경될 때마다 notify()를 호출해주어야 한다.
/* set_age() 멤버함수는 다음과 같은 세가지 책임이 주어진다.
    - 필드의 값이 실제로 바뀌었는지 검사해야 한다.
    - 필드의 적절한 값이 설정되어야 한다.
    - 필드의 값이 바뀌었을 때 올바른 인자로 notify()를 호출한다.
*/

struct Person : Observable<Person>{
    Person(int age) : age{age}{}
    int get_age(){return this->age;}
    void set_age(const int age){
        if(this->age == age) return;
        this->age = age;
        notify(*this, "age");
    }
private:
    int age;
};

/* 관찰자(Observer)와 관찰대상(Observable)의 연결
    알림을 받기 위한 관찰자는 다음과 같이 정의된다.
*/
struct ConsolePersonObserver : Observer<Person>{
    void field_changed(Person& source, const string& field_name) override{
        cout << "Person's "<< field_name << " has changed to " << source.get_age() << ".\n";
    }
};

// 속성의 종속성, 스레드 안정성, 재진입 안정성과 같은 문제들을 고려할 필요가 없다면 여기까지의 구현들을 사용해도 괜찮다.

int main(){
    Person p{20};
    ConsolePersonObserver cpo;
    p.subscribe(&cpo);
    p.set_age(21);
    p.set_age(22);

    return 0;
}