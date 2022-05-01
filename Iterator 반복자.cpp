// iterator 반복자

// 내부 표현부를 노출하지 않고 어떤 집합 객체에 속한 원소들을 순차적으로 접근할 수 있는 방법을 제공
// - 리스트 객체에 접근해서 새로운 내용을 삽입 삭제 하거나 순회하는 내용을 반복자 객체에 정의
// List -> Iterator 다형성을 지닌 반복이 가능하도록 하여야함


#include<iostream>
using namespace std;
#define DEFAULT_LIST_CAPACITY 10000000;

template<class Item>
class List {
    public:
    
    // 생성, 소멸, 초기화, 대입
    List(long size = DEFAULT_LIST_CAPACITY) : _size(size);
    List(List&);
    ~List(){

    }
    List& operator=(const List&){
        return *this;
    }
    
    // 접근용 함수
    long Count() const{
        return _size;
    }
    Item& Get(long index) const{
        return _item;
    }
    Item& First() const;
    Item& Last() _const;
    bool Includes(const Item&) const{

    };

    void Append(const Item&){

    };

    void Prepend(const Item&){

    };

    // 
    void Remove(const Item&);
    void RemoveLast();
    void RemoveFirst();
    void RemoveAll();

    Item& Top() const;
    void Push(const Item&);
    Item& pop();

private:
    long _size;
    Item* _head, _tail;
};

template<class Item>
void List<Item>::Append(const Item& item){

}