#include<iostream>
using namespace std;

// 객체 의존성 (Object Dependencies)
// 현재 객체가 다른 객체와 상호작용(참조)하고 있다면 현재 객체는 다른 객체에 의존성을 가진다.

class Animal{
public:
    Animal(){}
    virtual ~Animal(){}
    virtual void speak()=0;
};

class Dog : public Animal{
public:
    Dog() : Animal() {}
    void speak(){
        cout << "멍멍" << endl;
    }
};

// PetOwner는 Dog에 의존성을 가진다
class PetOwner{
    Animal *animal;

    public:
    PetOwner(){
        this->animal = new Dog(); // 해당 열에 의해 Dog에 의존
    }
    Animal* getAnimal(){
        return this->animal;
    }
};
// 이러한 의존성을 감소시키는게 DI(Dependency Injection).
// 프레임워크 등에 의해 객체의 의존성이 주입되는 설계 패턴.
// -> 클래스 A가 B,C에 의존적일 때 B,C를 외부에서 생성하고 A에게 B,C를 사용하라고 전달하는 것 

int main(){
    PetOwner owner;

    owner.getAnimal()->speak();

    return 0;
}