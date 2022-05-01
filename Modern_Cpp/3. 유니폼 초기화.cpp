#include<iostream>	// 모던 C++ 3.유니폼 초기화
#include<cstdio>
#include<string>
#include<vector>
using namespace std;

typedef struct Car {
	int cost;
	int oil;
}Car;

class Book{
public:
	string name;
	int cost;

	Book(const string& name, int cost) : name(name), cost(cost){}
};

// 함수 리턴값으로 사용
vector<int> return_func(){
	return {1,2,3};
}

// 함수 인자로 사용
void parameter_func(vector<int> v){
	for(auto i : v) cout<<i<<" ";
	cout<<endl;
}

int main(){
	// 5로 초기화
	int v1{5};
	printf("v1: %d \n",v1);

	// 배열 1,2,3 으로 초기화
	int v2[]{1,2,3};
	printf("v2 [0]:%d [1]:%d [2]:%d\n",v2[0], v2[1], v2[2]);

	// vector 클래스 1,2,3 으로 초기화
	vector<int> v3{1,2,3};
	printf("v3 [0]:%d [1]:%d [2]:%d\n", v3[0], v3[1], v3[2]);

	// vector 클래스 pair초기화 {1, '1'}, {2, 'b'}
	vector<pair<int, string>> v4{{1, "1"}, {2,"b"}};
	printf("v4 [0]%d %s [1]%d %s \n", v4[0].first, v4[0].second.c_str(), v4[1].first, v4[1].second.c_str());

	// 클래스 초기화
	Car car{50, 20};
	printf("Car cost[%d] oil[%d]\n", car.cost, car.oil);

	// vector 클래스 템플릿 클래스로 초기화
	vector<Book> book{{"a", 100}, {"b", 200}};
	printf("Book [0](%s,%d) [1](%s,%d)\n", book[0].name.c_str(), book[0].cost, book[1].name.c_str(), book[1].cost);

	// 이름없는 임시변수 초기화
	vector<int> {1,2,3};

	// 동적할당
	int * v = new int[3]{1,2,3};

	// 함수 리턴값 초기화를 받음
	vector<int> v = return_func();

	// 함수 인자로 사용
	parameter_func({1,2,3});

	return 0;
}