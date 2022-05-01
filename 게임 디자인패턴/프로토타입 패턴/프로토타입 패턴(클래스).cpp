#include<iostream>
#include<vector>
class Monster {
public:
    virtual ~Monster() {}
    virtual Monster* clone() = 0;

protected:
    int health_;
    int speed_;
};

class Ghost : public Monster {
public:
    Ghost(int health, int speed){
        this->health_ = health;
        this->speed_ = speed;
        std::cout << health_<< "/" << speed_<< " Ghost »ý¼º "<< std::endl;
    }

    Monster* clone() override{
        return new Ghost(health_, speed_);
    }
};
class Demon : public Monster {};
class Sorcerer : public Monster {};

/////////////////////////////////////////////////////////////////
class Spawner {
public:
    virtual ~Spawner(){}
    Spawner(Monster* prototype) : prototype_(prototype){}
    Monster* spawnMonster(){
        return prototype_->clone();
    };
    
private:
    Monster* prototype_;
};

int main(){
    Monster* GhostPrototype = new Ghost(50, 1);
    Spawner* GhostSpawner = new Spawner(GhostPrototype);

    std::vector<Monster*> monsters;
    for(int i=0; i<3; i++) 
        monsters.push_back(GhostSpawner->spawnMonster());

    for(auto i : monsters)
        delete i;
        
    return 0;
}
