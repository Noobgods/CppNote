#include <cstdio>
using namespace std;
#define EPSILON 0.0001

// 먼저 벡터를 표현하는 구조체를 정의합니다.
struct Vector2{
double x, y;
//생성자
Vector2(double _x, double _y){
x = _x, y = _y;
}
//외적
double cross(const Vector2& other) const{
return x*other.y-y*other.x;
}

/* 연산자 오버로딩을 통해 실제 벡터의 연산을 구현합니다. */

//벡터의 실수배
Vector2 operator * (double r) const{
	return Vector2(x*r, y*r);
}
//벡터의 덧셈
Vector2 operator + (Vector2 other) const{
	return Vector2(x + other.x, y + other.y);
}
//벡터의 뺄셈
Vector2 operator - (Vector2 other) const{
	return Vector2(x - other.x, y - other.y);
}
//두 벡터의 비교
bool operator == (Vector2 other) const{
	return x == other.x && y == other.y;
}
bool operator < (Vector2 other) const{
	return x < other.x && y < other.y;
}
};

bool lineIntersection(Vector2 a, Vector2 b, Vector2 c, Vector2 d, Vector2& x){
	double det = (b - a).cross(d - c);
	// 두 선이 평행인 경우
}