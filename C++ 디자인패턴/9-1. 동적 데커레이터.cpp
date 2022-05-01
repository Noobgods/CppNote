#include <iostream>
#include <sstream>
using namespace std;

// 데커레이터 패턴
// : 이미 존재하는 타입에 새로운 기능을 추가하면서도 원래 타입의 코드에 수정을 피할 수 있게 해준다.

// 시나리오 : 도형을 나타내는 Shape가 기존에 존재하고 있고 이를 상속받아 색상이 있는 도형과 투명한 도형을 추가한다.
//          나중에 두가지 속성을 모두 필요로 하는 경우가 발생하여 추가로 클래스를 만드는데 결과적으로 두가지 기능을 추가하기 위해
//          클래스를 3개 만들게 된다. 이런식이면 기능이 하나 추가될때마다 7개의 클래스를 만들어야 할 수도 있다.
struct Shape{
    virtual string str() const =0;
};

struct Circle: Shape{
    float radius;

    explicit Circle (const float radius)
        : radius{radius} {}
    void resize(float factor){ radius *= factor;}

    string str() const override{
        ostringstream oss;
        oss<< "A circle of radius " << radius;
        return oss.str();
    }
}; // Square 구현은 생략

struct Square: Shape{
    float length;

    explicit Square (const float length)
        : length{length} {}
    void resize(float factor){ length *= factor;}

    string str() const override{
        ostringstream oss;
        oss<< "A square with side " << length;
        return oss.str();
    }
};
// 평범한 상속으로는 효율적으로 새로운 기능을 도형에 추가할 수가 없다는 것을 알 수 있다. 따라서 컴포지션을 활용한다.
// 컴포지션 : 데커레이터 패턴에서 객체들에 새로운 기능을 확장할때 활용되는 메커니즘

// 동적 컴포지션 : 참조를 주고받으면서 런타임에 동적으로 무언가를 합성할 수 있게 한다.
// 정적 컴포지션 : 템플릿을 이용하여 컴파일 시점에 추가기능이 합성되게 한다.

// 동적 데커레이터

// 도형에 색을 입히려 한다고 가정하자. 상속대신 컴포지션으로 ColoredShape을 만들 수 있다.
struct ColoredShape : Shape{
    Shape& shape;
    string color;

    ColoredShape(Shape& shape, const string& color)
        : shape{shape}, color{color}{}
    
    string str() const override{
        ostringstream oss;
        oss << shape.str() << " has the color " << color;
        return oss.str();
    }
};    

// 투명도를 가지게 하고 싶다면 다음과 같이 구현할 수 있다.
struct TransparentShape : Shape{
    Shape& shape;
    uint8_t transparency;

    TransparentShape(Shape& shape, const uint8_t transparency)
        : shape{shape}, transparency{transparency} {}

    string str() const override{
        ostringstream oss;
        oss << shape.str() << " has "
            << static_cast<float>(transparency) / 255.f * 100.f
            << "% transparency";
        return oss.str();
    }
};

// 이제 투명도를 0..255 범위로 지정하면 그것을 퍼센테이지로 출력해주는 새로운 기능이 추가되었다.
    
// 편리하게 ColoredShape와 TrnasparentShape를 합성하여 색상과 투명도 두 기능 모두 도형에 적용되도록 할 수 있다.

int main(){
    Circle circle{0.5f};
    ColoredShape redCircle{circle, "red"};
    cout << redCircle.str() << endl;
    // 출력결과 "A circle of radius 0.5 has the color red"

    Square square{3};
    TransparentShape demiSquare{square, 85};
    cout << demiSquare.str() << endl;
    // 출력결과 "A square with side 3 has 33.3333% transparency"

    Circle circle2{23};
    ColoredShape greenCircle{circle2, "green"};
    TransparentShape myCircle{greenCircle, 64};
    cout << myCircle.str() << endl;
    // 출력결과 "A circle of radius 23 has the color green has 25.098% transparency"
    return 0;
}