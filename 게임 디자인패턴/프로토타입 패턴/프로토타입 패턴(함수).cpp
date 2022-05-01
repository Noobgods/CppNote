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
Monster* spawnGhost(){
    return new Ghost(50, 1);
}

typedef Monster* (*SpawnCallback)();

class Spawner {
public:
    Spawner (SpawnCallback spawn) : spawn_(spawn){}
    Monster* spawnMonster(){
        return spawn_();
    }
private:
    SpawnCallback spawn_;
};

int main(){
    Spawner* ghostSpawner = new Spawner(spawnGhost);

    std::vector<Monster*> monsters;
    for(int i=0; i<3; i++) 
        monsters.push_back(ghostSpawner->spawnMonster());

    for(auto i : monsters)
        delete i;
        
    return 0;
}
