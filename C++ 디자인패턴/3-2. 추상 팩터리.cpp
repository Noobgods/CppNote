#include<iostream>
#include<memory>
#include<map>
#include<functional>
using namespace std;

// # 추상팩터리
// 그동안 객체 한개를 생성하는 경우를 살펴봤다. 드물지만 여러 종류의 연관된 객체를 생성해야 할 경우도 있다.
// 추상 팩터리는 그러한 경우를 위한 패턴이다.

// 뜨거운 차와 커피를 판매하는 카페를 운영해야한다고 가정했을때, 이 두음료는 다른 장비를 이용해 만들어진다.
// 다음과 같이 뜨거운 음료를 추상화하는 HotDrink를 정의한다.
struct HotDrink{
    virtual void prepare(int volume) = 0;
};

struct Tea : HotDrink{
    void prepare(int volume) override{
        cout << "Take tea bag, boil water, pour "<< volume <<"ml, add some lemon" << endl;
    }
};

struct Coffee : HotDrink{
    void prepare(int volume) override{
        cout << "Grind some beans, boil water, pour " << volume << "ml, add cream, enjoy!" << endl;
    }
};

// make_drink 함수를 간단히 만들어 본다.
/*
unique_ptr<HotDrink> make_drink(string type){
    unique_ptr<HotDrink> drink;
    if(type == "tea"){
        drink = make_unique<Tea>();
        drink->prepare(200);
    }
    else{
        drink = make_unique<Coffee>();
        drink->prepare(50);
    }
    return drink;
}
*/
// 그런데 차와 커피를 만드는 장비는 다르다. 따라서 팩터리를 만들기로 한다.

struct HotDrinkFactory{
    virtual unique_ptr<HotDrink> make() const = 0;
};
// 이 팩터리가 추상 팩터리이다.
// 어떤 특정 인터페이스를 규정하고 있지만 구현 클래스가 아닌 추상 클래스이다.

// 아래와 같은 자식 클래스로 구현클래스로서 만들 수 있다.

struct TeaFactory : HotDrinkFactory{
    unique_ptr<HotDrink> make() const override{
        return make_unique<Tea>();
    }
};

struct CoffeeFactory : HotDrinkFactory{
    unique_ptr<HotDrink> make() const override{
        return make_unique<Coffee>();
    }
};
// 이제 좀 더 상위 수준에서 다른 종류의 음료를 만들어야 한다고 가정해 보자
// 뜨거운 음료 뿐만 아니라 차가운 음료도 만들 수 있어야 한다.
// 이를 위해 DrinkFactory를 두어 사용 가능한 다양한 팩터리들에 대한 참조를 내부에서 가지도록 할 수 있다.

class DrinkFactory{
    map<string, unique_ptr<HotDrinkFactory>> hot_factories;
public:
    DrinkFactory(){
        hot_factories["coffee"] = make_unique<CoffeeFactory>();
        hot_factories["Tea"] = make_unique<TeaFactory>();
    }

    unique_ptr<HotDrink> make_drink(const string& name){
        auto drink = hot_factories[name]->make();
        drink->prepare(200);
        return drink;
    }
};

// # 함수형 팩터리
// 팩터리라고 말할때 두 가지 중 하나를 의미한다.
// - 객체를 어떻게 생성하는지 알고 있는 어떤 클래스
// - 호출했을 때 객체를 생성하는 함수
// 2번째의 경우는 팩터리 메서드라고 생각될 수도 있지만 팩터리라고 부른다. 메서드는 객체의 멤버함수를 의미한다.

// 함수도 변수에 저장될 수 있다. 즉, 팩터리에 포인터를 저장하는 방법 대신에 200ml의 음료를 생성하는 절차 자체가 팩터리에 내장하게 할 수 있다.
class DrinkWithVolumeFactory{
    map<string, function<unique_ptr<HotDrink>()>> factories;
public:
    DrinkWithVolumeFactory(){
        factories["tea"] = []{
            auto tea = make_unique<Tea>();
            tea->prepare(200);
            return tea;
        };
        factories["coffee"] = []{
            auto coffee = make_unique<Coffee>();
            coffee->prepare(50);
            return coffee;
        };
    }
    unique_ptr<HotDrink> make_drink(const string& name);
};

// 저장된 팩터리를 직접 호출하는 과정을 다음과 같이 생략 할 수 있다.
inline unique_ptr<HotDrink> DrinkWithVolumeFactory::make_drink(const string& name){
    return factories[name]();
}
// 이 코드는 동일하게 사용자가 이용할 수 있다.
int main(){
    DrinkFactory df;
    df.make_drink("Tea");

    DrinkWithVolumeFactory dv;
    dv.make_drink("coffee");
    return 0;
}