#include<iostream>
#include<atomic>
#include<mutex>
using namespace std;
// # 전역객체로서의 싱글턴
// 손쉽게 개발자간의 약속을 하여 주석 등으로 단 한번만 인스턴스 하도록 하는 것이다.
/*
struct Database{
    /** 
     * \brief 이 객체를 두 개 이상 인스턴스화 하지 마시오.
     */
    /*
    Database(){}
};

// 하지만 의도하지 않은 은밀한 방식으로 생성자가 호출되어 버릴 수도 있다.
// 가장 간단한 아이디어는 static 전역 객체를 두는것이다.

static Database database{};

// static 전역객체의 문제점은 각각의 컴파일 단위 바이너리들에서 초기화 순서가 정의되어 있지 않다는 것이다.
// 전역객체가 여러 개 사용된다면 어느 한 모듈에서 전역 객체를 참조할 때 그 전역 객체가 참조하는 또 다른 전역 객체가 아직 초기화된 상태가 아닐 수 있다.
// 그리고 사용자가 전역객체가 있다는 사실을 어떻게 알 수 있느냐 하는 문제도 있다.

Database& get_database(){
    static Database database;
    return database;
}

*/
// 이 함수를 호출하면 데이터베이스에 접근할 수 있는 참조를 얻을 수 있다.
// 하지만 스레드 안정성이 C++11 이상 버전에서만 보증된다.
// static 객체를 초기화 하는 코드 앞뒤로 컴파일러가 락을 삽입해주는지 확인해야 한다.
// 싱글턴이 다른 싱글턴을 참조해도 되는가?

// # 전통적인 구현

/*
struct Database{
    Database(){
        static int instance_count{0};
        if (++instance_count > 1){
            throw std::runtime_error("Cannot make >1 database!");
        }
    }
};
*/

// 이렇게 생성하게 되면 사용자 관점 측면에서 생성자가 단 한번만 호출되어야 하는 것을 알 수 없다.
// 명시적으로 생성하는 것을 막는 방법은 생성자를 private로 선언하고 인스턴스를 리턴받기 위한 멤버 함수를 만드는 것이다.

struct Database{
protected:
    Database(){
        // 기타 필요한 작업
    }
    static atomic<Database*> istc;
    static mutex mtx;

public:
    static Database& get(){
        // C++11 이상 버전에서는 스레드 세이프 함
        static Database database;
        return database;
    }
    Database(Database const&) = delete;
    Database(Database&&) = delete;
    Database& operator=(Database const&) = delete;
    Database& operator=(Database &&) = delete;  

    // C++11 이전버전은 이증검증 락킹 방법으로 생성자를 보호해야 한다.
    static Database& instance();   
};

// 멀티 스레드 안정성을 위해 생성자를 보호한다. (원래는 boost를 사용해야함)
Database& Database::instance(){
    Database* db = istc.load(memory_order_consume);
    if(!db){
        lock_guard<mutex> guard(mtx);
        db = istc.load(memory_order_consume);
        if(!db){
            db = new Database();
            istc.store(db, memory_order_release);
        }
    }
}

// 위 코드에서 생성자를 숨기고 복제/이동 생성자/연산자를 삭제한다.
int main(){
    return 0;
}