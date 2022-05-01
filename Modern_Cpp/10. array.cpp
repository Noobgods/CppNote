#include<iostream>  // 10. array
#include<array>
using namespace std;

// 기존 STL vector 대신 사용한다.
// vector는 생성과 소멸에 드는 비용이 꽤 크고 언제나 메모리를 32bit를 사용한다.
// 위와 같은 문제를 해결하는것이 array 이다.
// vector : 동적배열, 힙 / array : 정적배열, 스택

int main(){
    array<int, 5> arr{1,2,3};   // 나머지는 0으로 초기화 된다.
    for(auto i : arr) {
        cout << i << " ";
    }
    cout << endl;
    
    int *p = arr.data(); // data 함수는 첫번재 원소의 주소를 반환(포인터)
    for(int i=0; i<arr.size; i++){
        cout << *(p+i) << " ";
    }
    cout << endl;
}