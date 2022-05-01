#include<iostream>  // 8. 이동 시멘틱 
#include<cstring>
using namespace std;

/* Move Sematics
    C++11 에서 추가된 문법. 객체의 메모리 소유권을 이전하는 방식의 문법 
    기존의 C++에서 사용된 Copy semantics (복사 시멘틱)은 때때로 불필요한 복사때문에 보이지 않는 성능 저하의 원인이 되었다.
    데이터 복제 또는 대입이 끝난 후 데이터 소멸시 Move Semantics를 사용한다면 얕은 복사를 해도 메모리의 소유권 이전이기 때문에 비용이 발생하지 않음

    Class A = B;
    위처럼 사용시 디폴트 복사생성자를 컴파일러가 생성해줌
    디폴트 복사생성자의 문제 -> 얕은 복사

    swapping을 하게되면 불필요한 복사연산이 매우 많이 발생

    Move semantics 는 이때 사용하며 R-Value(임시객체)의 이동을 이용

    이동 연산을 한 객체는 빈 상태이므로 재사용해서는 절대 안된다.

    Copy Semantics 와 Move Semantics의 가장 큰 차이점은
    Copy Semantics는 깊은 복사를 통해 원본과 똑같은 객체를 생성해 복사하므로 메모리 낭비가 심하고
    Move Semantics는 메모리 소유권 이전을 통해 얕은 복사를 하고 원본을 NULL로 초기화 하는 것.
*/

class atring{
public:
    char *str;
    int len;
    int capacity;
    atring(){
        cout << "[+] call constructor ! " <<endl;
        len = 0;
        capacity = 0;
        str = NULL;
    }
    atring(char *s){
        cout << "[+] call constructor ! " << endl;
        len = strlen(s);
        capacity = len;
        str = new char[len];
        for(int i= 0; i!=len; i++)
            str[i] = s[i];
    }
    // 복사 연산자
    atring& operator=(atring &s){
        cout << "[+] copy ! " << endl;
        if(s.len > capacity){
            delete[] str;
            str = new char[s.len];
            capacity = s.len;
        }
        len = s.len;
        for(int i=0; i!=len; i++)
            str[i]= s.str[i];
        return *this;
    }
    // 이동 연산자 (move Semantics)
    atring& operator=(atring &&s){
        cout<<"[+] move ! "<<endl;
        str = s.str;
        capacity = s.capacity;
        len = s.len;

        s.str = nullptr;
        s.capacity = 0;
        s.len = 0;

        return *this;
    }
    atring(atring &s){
        cout <<"[+] call copy constructor ! " <<endl;
        len = s.len;
        str = new char[len];
        for(int i=0; i!=len; i++)
            str[i] = s.str[i];
    }
    atring(atring &&s){
        cout <<"[+] call move constructor ! " <<endl;
        len = s.len;
        str = s.str;
        capacity = s.capacity;

        s.str = nullptr;
        s.len = 0;
        s.capacity = 0;
    }
    ~atring(){
        if (str) delete[] str;
    }
    int length(){
        return len;
    }
    void print(){
        for(int i =0; i!=len; i++)
            cout<<str[i];
        cout <<endl;
    }
};
template<typename T>
void awap(T &a, T &b){
    T tmp(move(a));
    a = move(b);
    b = move(tmp);

    // 아래와 같이 swap 연산을 실시 한다면 Copy Semantics에 의해 불필요한 복사가 발생한다.
    /* T tmp(a);
    a = b;
    b = tmp;*/
}
int main(){
    atring str1("CAT");
    atring str2("DOG");
    cout << "===== before Swap =====" <<endl;
    cout << "[=] str1 : ";str1.print();
    cout << "[=] str2 : ";str2.print();
    cout << "===== after Swap =====" <<endl;
    awap(str1, str2);
    cout << "[=] str1 : ";str1.print();
    cout << "[=] str2 : ";str2.print();
    cout << str1.str<<endl;
    return 0;
}