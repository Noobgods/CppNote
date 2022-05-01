#include<iostream>  // 14. 스레드 라이브러리 2
#include<fstream>
#include<thread>
#include<mutex>

using namespace std;

mutex file_mutex;

// 공유 자원 관리
// mutex를 사용하여 상호 배제한다.
void func(string str){
    ofstream file("test.txt", ios::app);
    
    //file_mutex.lock();

    //lock 호출 뒤 unlock 미호출 시 deadlock에 빠진다.
    //lock_guard를 사용 시 자동으로 unlock 해줌
    { 
        lock_guard<mutex> guard(file_mutex);
        for(auto i : str)
            file << i;
        file << endl;
    }
    //file_mutex.unlock();
}

int main(){
    thread t1(func, "thread 1");
    thread t2(func, "thread 2");

    t1.join();
    t2.join();

    return 0;

}