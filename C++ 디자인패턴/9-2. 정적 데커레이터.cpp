#include <iostream>
#include <sstream>
using namespace std;

struct Shape {
    virtual string str() const = 0;
};

struct Circle : Shape {
    float radius;
 
    Circle(){}

    explicit Circle(const float radius)
        : radius{ radius } {}
    void resize(float factor) { radius *= factor; }

    string str() const override {
        ostringstream oss;
        oss << "A circle of radius " << radius;
        return oss.str();
    }
};

struct Square : Shape {
    float size;
    
    Square(){}

    explicit Square(const float size)
        : size{ size } {}
    void resize(float factor) { size *= factor; }

    string str() const override {
        ostringstream oss;
        oss << "A square with side " << size;
        return oss.str();
    }
};

// resize() 멤버 함수는 Shape 인터페이스와 관계가 없기 때문에 데커레이터에서 호출할 수 없다.
// 보통의 상속 대신 MixIn 상속이라 불리는 방식을 이용한다.

// static_assert를 이용해 Shape이외의 타입이 지정되는 것을 막는다.

template <typename T> struct ColoredShape : T {
    static_assert(is_base_of<Shape, T>::value,
        "template argument must be a Shape");

    string color;

    ColoredShape(){}

    template <typename...Args>
    ColoredShape(const string& color, Args ...args)
        : T(std::forward<Args>(args)...), color{ color }{}
    // 여기서 베이스 클래스의 소멸자를 호출할 수는 없다.
    // 왜냐면 소멸자를 알 수가 없기 때문이다.

    string str() const override {
        ostringstream oss;
        oss << T::str() << " has the color " << color;
        return oss.str();
    }
};  // TransparentShape<T>의 구현은 생략...

// 하지만 모든 생성자를 한번에 편리하게 호출 하던 부분을 잃었다.

// 데커레이션을 완성하기 위해 ColoredShape와 TransparentShape에 생성자를 전달한다. 이 생성자들은 두 종류의 인자를 받는다. 
// 첫번째 인자들은 현재의 템플릿 클래스에 적용되는 것들이고 두번째 인자들은 부모 클래스에 전달될 제네릭 파라미터 팩이다.

template <typename T> struct TransparentShape : T {
    static_assert(is_base_of<Shape, T>::value,
        "template argument must be a Shape");

    uint8_t transparency;

    TransparentShape(){}

    template<typename...Args>
    TransparentShape(const uint8_t transparency, Args ...args)
        : T(std::forward<Args>(args)...), transparency{ transparency }{}

    string str() const override {
        ostringstream oss;
        oss << T::str() << " has "
            << static_cast<float>(transparency) / 255.f * 100.f
            << "% transparency";
        return oss.str();
    }
};

int main() {
    // 디폴트 생성자가 없으면 동작하지 않는다.
    ColoredShape<TransparentShape<Square>> square{ "blue" };
    square.size = 2;
    square.transparency = 50;
    cout << square.str() << endl;
    // 이제 square의 어떤 멤버든 접근 가능
    square.resize(3);
    
    // 위의 생성자는 이제 임의의 개수의 인자를 받을 수 있다. 이제 구현을 이용해보자.
    ColoredShape<TransparentShape<Square>> sq = { "red", 51, 5 };
    cout << sq.str() << endl;
    // 출력결과 "A square with side 5 has 20% transparency has the color red"

    return 0;
}