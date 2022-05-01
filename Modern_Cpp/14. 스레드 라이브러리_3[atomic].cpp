#include <iostream>
#include <thread>
#include <atomic>

using namespace std;

//atomic 객체를 사용하면 별 다른 동기화 작업없이 공유자원을 사용할 수 있다.
void func(atomic<int> &a, int t, int n){
    for(int i =0; i<t; i++){
        cout << "thread" << n <<" :" << a++ <<endl;
        this_thread::sleep_for(1s);
    }
}

int main(){
    atomic<int> a(1); // atomic은 클래스이다. 유니폼 초기화, 선언후 초기화 가능

    thread t1(func, ref(a), 5, 1);
    thread t2(func, ref(a), 5, 2);
    thread t3(func, ref(a), 5, 3);
    
    t1.join();
    t2.join();
    t3.join();
}