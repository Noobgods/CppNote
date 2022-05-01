#include<iostream>
#include<vector>
using namespace std;

class GameObject{
public:
    GameObject(){}
};

class Monster {
public:
    virtual ~Monster() {
        delete gameObject_;
    }

    Monster(int health, int speed, GameObject* gameObject)
     : health_(health), speed_(speed), gameObject_(gameObject){
        cout << " 몬스터 생성" << endl;
    }
protected:
    int health_;
    int speed_;
    GameObject* gameObject_;
};

class Ghost : public Monster {
public:
    Ghost(Ghost& ghost)
     : Monster(ghost.health_, ghost.speed_, ghost.gameObject_){
    }

    Ghost(int health, int speed, GameObject* gameObject)
     : Monster(health, speed, gameObject){
    }
};
class Demon : public Monster {};
class Sorcerer : public Monster {};

/////////////////////////////////////////////////////////////////
class Spawner{
public:
    virtual ~Spawner(){}
    virtual Monster* spawnMonster() = 0;
};

template<typename T>
class SpawnFor : public Spawner {
public:
    T* prototype_;

    ~SpawnFor(){
        delete prototype_;
    }
    SpawnFor(T* prototype) : prototype_(prototype){}
    
    virtual T* spawnMonster() {
        return newMonster(*prototype_);
    }
private:
    T* newMonster(T& proto){
        T* monster = new T(proto);
        // 
        return monster;
    }
};

int main(){
    Ghost* originalGhost = new Ghost(50, 1, new GameObject());
    SpawnFor<Ghost>* ghostSpawner = new SpawnFor<Ghost>(originalGhost);

    vector<Monster*> monsters;
    for(int i=0; i<3; i++) 
        monsters.push_back(ghostSpawner->spawnMonster());

    for(auto i : monsters){
        delete i;
    }
    return 0;
}
