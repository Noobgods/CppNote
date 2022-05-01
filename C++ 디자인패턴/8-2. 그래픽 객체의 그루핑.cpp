#include <iostream>
#include <vector>
using namespace std;

// 개별 그래픽 객체를 렌더링할 수도 있고 여러 개의 도형을 하나의 그룹으로 렌더링할 수도 있다.
// 다음과 같은 인터페이스 하나면 충분하다.

struct GraphicObject{
    virtual void draw() = 0;
};

// 여러개의 사각형과 원들이 모인 그래픽 객체들도 집합적으로 하나의 그래픽 객체를 나타낼 수 있다.
// 원을 다음과 같이 정의할 수 있듯이 여기서 컴포지트 디자인 패턴이 드러난다.

struct Circle : GraphicObject{
    void draw() override{
        std::cout << "Circle"<< std::endl;
    }
};

// 비슷한 방식으로 여러 개의 그래픽 객체를 가지는 GhaphicObject를 정의할 수 있다.

struct Group : GraphicObject{
    std::string name;

    explicit Group(const std::string& name)
        : name{name}{}
    
    void draw() override {
        std::cout << "Group "<< name.c_str()<< " contains: "<< std::endl;
        for (auto&& o : objects){
            o->draw();
        }
    }

    std::vector<GraphicObject*> objects;
};
// 개별 원 객체든 그룹 그래픽 객체든 draw() 함수를 구현하고 있으면 그릴 수 있는 도형이다.
// 이제 다음과 같이 API를 이용할 수 있다.

int main(){
    Group root("root");
    Circle c1, c2;
    root.objects.push_back(&c1);

    Group subgroup("sub");
    subgroup.objects.push_back(&c2);

    root.objects.push_back(&subgroup);

    root.draw();

    return 0;
}

// 다음과 같이 출력된다.
/* 
Group root contains:
Circle
Group sub contains:
Circle 
*/
// 이 예제는 인위적인 커스텀 인터페이스 정의가 사용되기는 했지만 가장 단순한 형태의 컴포지트 패턴 구현이다.