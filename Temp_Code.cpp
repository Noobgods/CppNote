#include<iostream>
#include<vector>
#include<memory>
using namespace std;

class GameObject{
public:
    GameObject(){}
};

class Monster {
public:
    virtual ~Monster() {
    }

    Monster(int health, int speed, shared_ptr<GameObject> gameObject)
     : health_(health), speed_(speed){
        gameObject_ = move(gameObject);
        cout << " 몬스터 생성" << endl;
    }
protected:
    int health_;
    int speed_;
    shared_ptr<GameObject> gameObject_;
};

class Ghost : public Monster {
public:
    Ghost(Ghost& ghost)
     : Monster(ghost.health_, ghost.speed_, ghost.gameObject_){
    }

    Ghost(int health, int speed, shared_ptr<GameObject> gameObject)
     : Monster(health, speed, gameObject){
    }
};
class Demon : public Monster {};
class Sorcerer : public Monster {};

/////////////////////////////////////////////////////////////////
class Spawner{
public:
    virtual ~Spawner(){}
    virtual shared_ptr<Monster> spawnMonster() = 0;
};

class SpawnFor : public Spawner {
public:
    shared_ptr<Monster> prototype_;

    ~SpawnFor(){
    }
    SpawnFor(shared_ptr<Monster> prototype) : prototype_(prototype){}
    
    virtual shared_ptr<Monster> spawnMonster() {
        return newMonster(prototype_);
    }
private:
    shared_ptr<Monster> newMonster(shared_ptr<Monster> proto){
        shared_ptr<Monster> monster = make_shared<Monster>(proto);
        // 
        return monster;
    }

};

int main(){
    shared_ptr<Ghost> originalGhost = make_shared<Ghost>(50, 1, make_shared<GameObject>());
    shared_ptr<SpawnFor> ghostSpawner = make_shared<SpawnFor>(originalGhost);

    vector<shared_ptr<Monster>> monsters;
    for(int i=0; i<3; i++) 
        monsters.push_back(ghostSpawner->spawnMonster());

    return 0;
}
