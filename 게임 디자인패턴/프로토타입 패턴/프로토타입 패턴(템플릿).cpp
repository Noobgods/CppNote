#include<iostream>
#include<vector>

class Monster {
public:
    virtual ~Monster() {}
    virtual Monster* clone() = 0;
    Monster(){std::cout << " Monster »ý¼º "<< std::endl;}
    Monster(int health, int speed)
     : health_(health), speed_(speed){}
protected:
    int health_;
    int speed_;
};

class Ghost : public Monster {
public:
    Ghost() : Monster(){}
    Ghost(int health, int speed)
     : Monster(health, speed){
    }
    
    Monster* clone() override{
        return new Ghost(health_, speed_);
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

template <typename T>
class SpawnFor : public Spawner {
public:
    virtual Monster* spawnMonster() {
        return new T();
    }
};

int main(){
    Spawner* ghostSpawner = new SpawnFor<Ghost>();

    std::vector<Monster*> monsters;
    for(int i=0; i<3; i++) 
        monsters.push_back(ghostSpawner->spawnMonster());

    for(auto i : monsters)
        delete i;
        
    return 0;
}
