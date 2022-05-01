#include<iostream>
#include<vector>
#include<memory>
#include<math.h>
using namespace std;

// # 시나리오
// 기본적인 그리기 객체를 정의하자.
struct Point{
    int x, y;
};

struct Line{
    Point start, end;
};

// 기하학적 도형을 모두 담을 수 있도록 일반화 한다.
// vector<Line>을 상속받아 표현할 수도 있지만 순수 가상 함수의 쌍으로 정의하자.
struct VectorObject{
    virtual vector<Line>::iterator begin() = 0;
    virtual vector<Line>::iterator end() = 0;
};

// 이제 사각형 Rectangle을 시작점과 크기를 입력받아 생성하고, 
// 사각형을 구성하는 선분들을 vector<Line> 타입 필드에 저장하여 그 꼭짓점들만 노출하는 방식으로 정의할 수 있다.

struct VectorRectangle : VectorObject{
    VectorRectangle(int x, int y, int width, int height){
        lines.emplace_back(Line{Point{x,y}, Point{x+width, y}});
        lines.emplace_back(Line{Point{x+width, y}, Point{x+width, y+height}});
        lines.emplace_back(Line{Point{x, y}, Point{x, y+height}});
        lines.emplace_back(Line{Point{x, y+height}, Point{x+width, y+height}});
    }

    vector<Line>::iterator begin() override{
        return lines.begin();
    }

    vector<Line>::iterator end() override{
        return lines.end();
    }

private:
    vector<Line> lines;
};

// 이제 사각형 그림을 그린다고 하자. 하지만 그렇게 할 수 없다. 아래 인터페이스와 같이 되어있기 때문이다.
// (MFC 라이브러리의 CPaintDC 클래스)
/*

void DrawPoints(CPaintDC& dc, std::vector<Point>::iterator start, std::vector<Point>::iterator end){
    for(auto i = start; i!= end; ++i)
        dc.SetPixel(i->x, i->y, 0);
}

// 그리기 인터페이스는 점을 찍는 것밖에 없지만 우리는 선분을 그려야 한다.
*/

// # 어댑터
/* 사각형 몇개를 그려야 한다고 가정하자.
<1:MainCode>
*/

// 이 객체들을 그리기 위해서는 사각형을 이루는 선분의 집합에서 각각의 선분마다 많은 수의 점이 변환되어야 한다.
// 이를 위해 별도의 클래스를 만든다.

struct LineToPointAdapter{
    typedef vector<Point> Points;
    LineToPointAdapter(Line& line){
        int left = min(line.start.x, line.end.x);
        int right = max(line.start.x, line.end.x);
        int top = min(line.start.y, line.end.y);
        int bottom = max(line.start.y, line.end.y);
        int dx = right - left;
        int dy = line.end.y - line.start.y;
        
        if(dx == 0){
            for(int y = top; y <= bottom; ++y){
                points.emplace_back(Point{left, y});
            }
        }
        else if(dy == 0){
            for(int x = left; x <= right; ++x){
                points.emplace_back(Point{x, top});
            }
        }
    }

    virtual Points::iterator begin() {return points.begin();}
    virtual Points::iterator end() {return points.end();}
private:
    Points points;
};

//
// <2:MainCode>

int main(){
    /*
    <1>
    vector<shared_ptr<VectorObject>> vectorObjects{
        make_shared<VectorRectangle>(10, 10, 100, 100),
        make_shared<VectorRectangle>(30, 30, 60, 60)
    };
    
    <2>
    for(auto& obj : vectorObjects){
        for(auto line : *obj){
            LineToPointAdapter lpo{line};
            DrawPoints(dc, lpo.begin(), lpo.end());
        }
    }
    */
    return 0;
}
