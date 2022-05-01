#include<iostream>	// 5. 스마트 포인터
#include<cstdio>
#include<vector>
#include<memory>
using namespace std;

// delete 키워드를 이용한 메모리 해제를 하지 않고 사용하는 포인터
// 소멸자가 자동으로 사용이 끝난 메모리를 delete 해준다.
// 또한 값을 지정하지 않는 경우 디폴트 생성자가 자동으로 NULL로 초기화한다.
// 메모리 릭, 댕글링 포인터 방지
// * 메모리 릭 : 동적할당 후, 메모리를 해제하지 않아 메모리가 누수되는 오류
// * 댕글링 포인터 : 해제된 메모리를 참조하거나 스택에서 사라진 메모리를 참조하는 포인터

// unique_ptr/shared_ptr/weak_ptr을 지원한다.
/* unique_ptr :
	- 하나의 스마트 포인터만 특정 객체를 소유하도록 소유권을 가짐
	- 해당 객체의 소유권을 가지고 있을 때 소멸자가 해당 객체를 해제
	- 복사 생성자와 복사 대입 연산자가 필요없기 때문에 사용 불가.
	- 복사가 불가능하고 소유권 이전만 가능
	- 소유권 이전시 기존 unique_ptr은 null_ptr이 된다.
	- 소유권 이전은 move 함수 사용.
	- 포인터는 get 멤버함수로 얻고, 메모리 해제는 reset멤버 함수로 기능
*/
/* shared_ptr :
	- 참조 횟수를 통해 참조하는 스마트 포인터가 몇개인지 확인한다.
	- 참조 횟수는 특정 객체에 대해 shared_ptr이 추가될 때마다 1씩 증가, 해제 할때마다 1씩 감소
	- 참조 횟수가 0이 되면 자동 해제
	- unique_ptr과 같이 make_shared 함수를 통해 안전하게 생성 가능
	- 복사에 제한이 없음.
	- use_count 함수를 통해 참조 횟수를 알 수 있다.
	- 참조 횟수를 건드리기 때문에 shared_ptr 객체가 복사가 되어도 메모리 공간이 안늘어남.
	- move 함수를 사용하면 기존의 포인터를 제거하고 그대로 이전하기 때문에 참조 횟수가 안 변함
*/
/* weak_ptr :
	- 서로 상대방을 가르키는 스마트 포인터는 참조횟수가 0이 되지 않으므로 메모리가 해제되지 않는다.
	- weak_ptr은 이 순환참조를 제거하기 위해 사용된다.
	- weak_ptr은 하나 이상의 shared_ptr 인스턴스가 소유하는 객체에 대한 접근을 제공하지만 소유자 수에는 포함안됨.
	- weak_ptr이 가르키는 메모리 공간은 shared_ptr의 참조횟수에 포함되지 않음.
*/	
int main(){
	// Modern Cpp 이전 auto_ptr의 사용
	//auto_ptr<int> aptr1(new int(1));
	//auto_ptr<int> aptr2 = aptr1; // 이때 aptr1은 null_ptr이 된다.

	// unique_ptr
	unique_ptr<int> uptr(new int(1));
	cout << *uptr << endl; // output 1
	
	auto uptr2 = uptr.get(); // 소유권 이전이 아닌 순수 포인터 얻기
	*uptr2 = 2;
	cout << *uptr2 <<" "<< *uptr << endl; // output 2 2

	auto uptr3 = move(uptr); // 소유권 이전
	uptr.reset();	// 이미 소유권 이전이 되어 아무일도 안일어남.
	cout << *uptr3 <<" "; // output 2
	*uptr3 = 3;
	cout << *uptr3 << " " << *uptr2 << endl; // output 3 3

	// make_unique : 지정된 타입의 객체를 생성하고 생성된 객체를 가리키는 unique_ptr 반환
	// 예외 발생에 안전하게 대처
	unique_ptr<int[]> uptr4(new int[3]{1,2,3});
	for(int i=0; i<3; i++)
		cout << uptr4[i] << endl;

	unique_ptr<int[]> uptr5 = make_unique<int[]>(3);
	for(int i=0; i<3;) 
		uptr5[i] = ++i;
	for(int i=0; i<3; i++)
		cout << uptr5[i] << endl;

	// shared_ptr
	shared_ptr<int> sptr = make_shared<int>(1);
	cout << sptr.use_count()<<endl;	// 1

	auto sptr2 = sptr;	// 참조
	cout << sptr.use_count()<<endl;	// 2

	auto sptr3(sptr); 	// 생성자로 참조
	cout << sptr.use_count()<<endl;	// 3
	
	auto sptr4 = move(sptr2);	// 소유권 이전
	cout << sptr.use_count()<<endl;	// 3
	
	sptr4.reset();	// 포인터 해제
	sptr3.reset();
	sptr.reset();

	cout << sptr.use_count()<<endl;	// 0
	
	return 0;
}