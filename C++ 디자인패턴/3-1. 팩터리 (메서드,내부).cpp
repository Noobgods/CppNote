#include<iostream>
#define _USE_MATH_DEFINES
#include<math.h>
using namespace std;

/* # 시나리오 
    직교 좌표계의 좌표점 정보를 저장하려 한다고 하면 아래와 같이 구현할 것이다.

    직교좌표계가 아닌 극좌표계의 좌표값으로 저장한다고 하면 문제가 된다.
    쉽게 생각하면 극좌표계용 생성자를 추가하면 되지 않을가 싶지만 직교 좌표계의 생성자와 구분이 불가능하다.

struct Point{
    // 직교 좌표계 생성자
    Point(const float x, const float y)
        : x{x}, y{y} {} 

    // 극 좌표계 생성자
    Point(const float r, const float theta){
        x = r * cos(theta);
        y = r * sin(theta);
    }

    // 두개의 생성자 오버로딩이 겹친다... (float, float)

    float x, y; // 직교 좌표계 좌표값
}

    한가지 단순한 방법은 좌표계 종류를 구분하는 enum 타입을 정의하고
    
enum class PointType{
    cartesian,
    polar
};

    좌표의 생성자에 좌표계 종류를 지정하는 파라미터를 추가한다.

    Point(float a, float b, PointType type = PointType::cartesian){
        if(type == PointType::cartesian){
            x = a; y = b;
        }
        else {
            x = r * cos(theta);
            y = r * sin(theta);
        }
    }

    이러한 경우로 사용하면 생성자의 파라미터 이름이 a b가 되어 버리기 때문에 직관적으로 어떠한
    역할을 하는 파라미터인지 의미를 전달하기 어렵다.
*/

/* # 팩터리 메서드

struct Point{
    float x, y;
protected:
    Point(const float x, const float y)
        : x{x}, y{y} {}
public:
    static Point NewCartesian(float x, float y){
        return {x, y};
    }
    static Point NewPolar(float r, float theta){
        return {r* cos(theta), r* sin(theta)};
    }
};

 여기서 static 함수들을 팩터리 메서드라고 부른다.
 이러한 메서드가 하는일은 Point 객체를 생성하여 리턴하는 것 뿐이다.
 이제 좌표점을 사용할때 다음과 같이 명확하게 할 수 있다.
 <1><main code>
*/

/* # 팩터리
//  빌더와 마찬가지로 Point를 생성하는 함수들을 별도의 클래스에 몰아 넣을 수 있는데 그러한 클래스를 팩터리라고 부른다.
//  먼저 Point 클래스를 다음과 같이 정의한다.

struct Point {
    float x,y;
    friend class PointFactory;
private:
    Point(float x, float y) : x(x), y(y) {}
};
    눈여겨볼 부분이 두가지 있다.
    - Point의 생성자는 private로 선언되어 사용자가 직접 생성자를 호출할 수 없게 한다.
    - Point는 PointFactory를 frined 클래스로 선언한다. 이부분은 팩터리가 Point의 생성자에 접근할 수 있게 하려는 의도이다.

 이제 별도의 클래스 PointFactory에 New-() 함수들을 정의하기만 하면 된다.
struct PointFactory{
    static Point NewCartesian(float x, float y){
        return Point{x, y};
    }
    static Point NewPolar(float r, float theta){
        return Point{r* cos(theta), r* sin(theta)};
    }
};

 이제 다음과 같이 인스턴스를 생성할 수 있다.
 <2><main code>
*/
/* # 내부팩터리
    내부 팩터리는 생성할 타입의 내부 클래스로서 존재하는 간단한 팩터리를 말한다.
    C#, 자바 등 friend 키워드에 해당하는 문법이 없는 프로그래밍 언어들에서는 내부 팩터리를 흔하게 사용한다.

 내부 팩터리의 장점은 생성할 타입의 내부 클래스이기 때문에 private 멤버들에 자유로운 접근 권한을 가진다는 것이다.
*/
struct Point{
private:
    Point(float x, float y) : x{x}, y{y} {}
    struct PointFactory{
    private:
        PointFactory(){}

    public:
        static Point NewCartesian(float x, float y){
            return Point{x, y};
        }
        static Point NewPolar(float r, float theta){
            return Point{r* cos(theta), r* sin(theta)};
        }
    };

public: 
    float x, y;
    static PointFactory Factory;
};

// 이러한 방법은 팩터리가 생성해야할 클래스가 단 한종류일때 유용하지만 
// 여러타입을 활용하여 객체를 생성해야 한다면 내부 팩터리 형식은 적합하지 않다.
// <3><main code>

// :: 와 .을 섞어쓰거나 Point가 중복되서 입력되는 것이 마음에 등장하지 않는다면
// 팩터리를 public으로 두거나 typedef를 사용하면 된다.

int main(){
    /* 
    <1>
    auto p = Point::NewPolar(5, M_PI_4);

    <2>
    auto my_point = PointFactory::NewCartesian(3, 4);
    */
    auto pp = Point::Factory.NewCartesian(2,3);
    
    //
    return 0;
}