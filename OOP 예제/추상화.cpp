#include<iostream>
using namespace std;

class A{
    virtual int func(int a)=0;
};

class B : A{
public:
    virtual int func(int a){ return a; };
};

class C : A{
public:
    virtual int func(int a){ return a+2; };
};

int main(){
    B b;
    C c;

    cout << "B is " << b.func(3) << endl;
    cout << "C is " << c.func(3) << endl;
    
    return 0;
}