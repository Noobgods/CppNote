#include <iostream>
using namespace std;

#define MAX_ENTITIES 256

// 행동을 가지고 있는 무언가를 정의할 Entity 클래스
class Entity {
public:
    Entity() : x_(0), y_(0) {}
    virtual ~Entity(){}
    virtual void Update() =0;

    double x() const{ return x_;}
    double y() const{ return y_;}
    
    void setX(double x) {x_ = x;}
    void setY(double y) {y_ = y;}

private:
    double x_;
    double y_;
};

// 루프를 가지고 있는 월드 클래스
class World {
public:
    World() : numEntities_(0) {}
    void gameLoop();

private:
    Entity* entities_[MAX_ENTITIES];
    int numEntities_;
};

// 게임 루프
void World::gameLoop(){
    while(true){
        // 유저 입력 처리

        // Entity 들을 순서대로 업데이트 해준다.
        for(int i=0; i<numEntities_; i++){
            entities_[i]->Update();
        }

        // 물리, 렌더링
    }
}

int main(){


    return 0;    
}