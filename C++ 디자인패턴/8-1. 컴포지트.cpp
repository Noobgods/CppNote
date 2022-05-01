#include<iostream>
#include<array>     // array 자료구조
#include<numeric>   // accumulate 함수
#include<algorithm> // max_element 함수
using namespace std;

// 컴포지트 패턴
// : 어떤 객체들의 집합에 대해 개별 인터페이스를 동일하게 가져갈 수 있게 하는 것

/* 
class Creature {
    int strength, agility, intelligence;
public:
    int get_strength() const{
        return strength;
    }
    
    void set_strength(int strength){
        Creature::strength = strength;
    }

    // 다른 get/set 멤버 함수들...
};
*/

// 통계를 내려면 단순하게 다음과 같이 만들어야 한다. 하지만 바람직하지 않다...

/* 
class Creature{
    int strength, agility, intelligence;
    // 다른 멤버들...
    int sum() const {
        return strength + agility + intelligence;
    }
    double average() const {
        return sum() / 3.0;
    }
    int max() const {
        return ::max(::max(strength, agility), intelligence);
    }
} 
*/

// 다음과 같은 문제로 바람직하지 않다.
// - 전체 합계를 계산할 때 필드 중 하나를 빠뜨리기 쉽다.
// - 평균을 계산할 때 상숫값 3.0이 사용되고 있다. 이 값은 필드의 개수가 바뀔때마다 바뀌어야 해서 의도치않은 종속성을 야기한다.
// - 최대 값을 구할 때 모든 필드 값 쌍마다 std::max()을 반복 호출해야 한다.

// 좋은 방법으로 배열기반 속성이 있다.

class Creature {
    enum Abilities{ str, agl, intl, count};
    array<int, count> abilities;

    // 이제 힘, 빠르기 등등에 대해 get/set 멤버 함수를 정의할 수 있다.
    int get_strength() const { return abilities[str]; }
    void set_strength(int value) { abilities[str] = value;}
    // 다른 속성들도 같은 방식으로 get/set 구현...

    // 이제 sum(), average(), max()의 구현이 대단히 쉬워진다.
    int sum() const{
        return accumulate(abilities.begin(), abilities.end(), 0);
    }
    
    double average() const {
        return sum() / (double)count;
    }

    int max() const{
        return *max_element(abilities.begin(), abilities.end());
    }
};