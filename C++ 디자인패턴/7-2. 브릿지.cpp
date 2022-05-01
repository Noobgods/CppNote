#include<iostream>
using namespace std;

// Pimpl 관례는 브릿지 패턴의 특별한 예
// Renderer 클래스는 벡터, 래스터로 그릴 수 있다고 한다.
// Renderer 베이스 클래스는 다음과 같이 정의한다. 
struct Renderer{
    virtual void render_circle(float x, float y, float radius) = 0;
};

// 실제로 그리지 않고 콘솔에 메세지를 출력한다.
struct VectorRenderer : Renderer{
    void render_circle(float x, float y, float radius) override{
        cout << "Drawing a vector circle of radius " <<radius << endl;
    }
};
struct RasterRenderer : Renderer{
    void render_circle(float x, float y, float radius) override{
        cout << "Rasterizing circle of radius " << radius <<endl;
    }
};

// 기하도형의 베이스 클래스 Shape는 렌더러에 대한 참조를 가진다. 
// 기하 도형은 멤버 함수 draw를 통해서 자기 자신을 그릴 수 있다. 추가적으로 크기 변경을 할 수 있는 resize() 멤버 함수도 가진다.

struct Shape{
protected:
    Renderer& renderer;
    Shape(Renderer& renderer): renderer{renderer}{}
public:
    virtual void draw() = 0;
    virtual void resize(float factor) = 0;
};

// renderer는 Renderer 클래스의 참조 변수로 선언되어 있다. 처음부터 의도하진 않았지만 브릿지 패턴을 구현했다.

struct Circle: Shape{
    float x, y, radius;

    void draw() override{
        renderer.render_circle(x, y, radius);
    }

    void resize(float factor) override{
        radius *= factor;
    }
    Circle(Renderer& renderer, float x, float y, float radius)
     : Shape{renderer}, x{x}, y{y}, radius{radius}{}
};

// 브릿지를 이용해 Circle을 렌더링 절차에 연결하는 부분이 draw()안에 구현된다. 여기서 브릿지는 Renderer이다.
// 렌더러는 자신이 다루는것이 Circle인지 전혀 모르고 자신이 참조 변수로 접근되고 있다는 것도 알지 못한다.

int main(){
    RasterRenderer rr;
    Circle raster_circle{rr, 5, 5, 5};
    raster_circle.draw();
    raster_circle.resize(2);
    raster_circle.draw();

    return 0;
}
