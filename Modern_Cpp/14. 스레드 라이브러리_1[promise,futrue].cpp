#include<iostream>
#include<thread> // 스레드 사용 헤더
#include<future> // promise, future 객체를 사용하기 위한 헤더
using namespace std;

chrono::system_clock::time_point start_time;

class Class{
    public:
    static void func(int a, int b){
        for(int i=0; i<b; i++){
            cout << a << endl;
        }
    }
};
void func(int a, int b){
    this_thread::sleep_until(start_time + 3s); // 프로그램 시작 후 3초뒤 실행
    for(int i=0; i<b; i++){
        this_thread::sleep_for(1s); // 1초 동안 sleep
        cout << a << endl;
    }
}

void sum(promise<int>& ret, int t){
    this_thread::sleep_for(5s);
    int sum = 0;
    for(int i=1; i<=t; i++) sum += i;
    ret.set_value(sum);
}
int main(){
    start_time = chrono::system_clock::now(); // 프로그램 시작시간

    thread t1(func, 1, 5); // 첫번째인자는 함수, 두번째 인자부터 매개변수
    thread t2([](int a, int b){ // 람다 함수도 지원
        for(int i=0; i<b; i++){
            cout << a << endl;
        }
    }, 2, 5);
    thread t3;
    /* join 함수를 호출하지 않으면 스레드 함수가 종료되기 전에
    메인함수가 종료되는 경우가 있으므로 join() 함수를 호출한다.
    해당 스레드 함수가 종료될 때까지 join() 함수의 다음 코드는 실행되지 않는다.
    
    */
    t1.join();
    t2.join();
    
    t3 = thread(Class::func,3,5); // 선언만 해놓고 원하는 타이밍에 스레드 실행
    // static 함수 / 전역 함수 만 가능하다.
    /*
    Class c;//일반 클래스 멤버함수를 호출하기 위해서는
    t3 = thread(&Class::func, &c ,3, 5);//다음과 같이 호출한다.
    */
    t3.join();

    // 스레드 함수의 리턴값 받기
    promise<int> ret;
    future<int> value = ret.get_future(); // future<int> => auto 가능
    thread t4(sum, ref(ret), 10); // 참조형태로 넘기고 싶다면 ref() 함수 사용

    cout << value.get() <<endl;
    // get() 함수는 set_value()가 호출될 때까지 기다린다.
    // 그러므로 join()함수를 이 다음줄에 호출해도 에러가 발생하지 않는다.

    t4.join();
}