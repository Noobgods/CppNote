#include<iostream>	// 2. 범위기반 for문
#include<cstdio>
#include<vector>
using namespace std;

// 범위기반 for문은 foreach 문과 비슷하다.
// 클래스를 범위기반 for 문으로 사용하기 위해서는 begin, end 함수를 정의해야한다.
int main(){
	vector<int> v{1,2,3}; 

	// 기존 방법
	for(vector<int>::iterator i=v.begin(); i != v.end; i++)
		printf("%d ", i);
	cout<<endl;

	// 범위기반 for문
	for(auto i : v)
		printf("%d", i);
	cout<<endl;

	return 0;
}