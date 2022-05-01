#include<iostream>
#include<vector>
using namespace std;

void assert(bool check){
    if(!check); // 예외발생
}
// 바이트코드
enum Instruction{
    INST_LITERAL = 0x00,
    INST_OBJECT = 0x01,
    INST_SET_HEALTH = 0x02,
    INST_SET_WISDOM = 0x03,
    INST_SET_AGILITY = 0x04,
    INST_GET_HEALTH = 0x05,
    INST_GET_WISDOM = 0x06,
    INST_GET_AGILITY = 0x07,
    INST_PLAY_SOUND = 0x08,
    INST_SPAWN_PARTICLES = 0x09,
};

// 사운드
class Sound{
public:
    void play();

private:
    string fileDirectory_;
};

// 파티클
class Particle{
public:
    void play();

private:
    string name_;
    int frame_;
};

// 오브젝트
class Object{
public:
    Object(int health, int wisdom, int agility)
    : health_(health), wisdom_(wisdom), agility_(agility){}
    int getHealth(){ return this->health_;};
    int getWisdom(){ return this->wisdom_;};
    int getAgility(){ return this->agility_;};
    void setHealth(int val){ this->health_ = val;};
    void setWisdom(int val){ this->wisdom_ = val;};
    void setAgility(int val){ this->agility_ = val;};

private:
    int health_;
    int wisdom_;
    int agility_;
};
vector<Object*> v_object_list;
class VM{
public:
    VM() : stackSize_(0){}
    void push(int value){
        assert(stackSize_ < MAX_STACK);
        stack_[stackSize_++] = value;
    }
    int pop(){
        assert(stackSize_ > 0);
        return stack_[--stackSize_];
    }
    // 기타 셋업
    void setHealth(int amount, Object* wizard){}
    void setWisdom(int amount, Object* wizard){}
    void setAgility(int amount, Object* wizard){}
    void playSound(int soundId){}
    void spawnParticles(int particleType){}

    void interpret(char bytecode[], int size){
        for(int i =0;i<size; i++){
            char instruction = bytecode[i];
            int amount, value;
            switch(instruction){
            case INST_LITERAL:
                value = bytecode[++i];
                push(value);
                break;
            case INST_OBJECT:
                object = v_object_list[pop()];
                push(value);
                break;
            case INST_SET_HEALTH:
                amount = pop();
                setHealth(amount, object);
                cout<<"체력을 " <<amount<<"으로 만들었다."<<endl;
                break;
            case INST_SET_WISDOM:
                amount = pop();
                setWisdom(amount, object);
                cout<<"지혜를 " <<amount<<"으로 만들었다."<<endl;
                break;
            case INST_SET_AGILITY:
                amount = pop();
                setAgility(amount, object);
                cout<<"민첩을 " <<amount<<"으로 만들었다."<<endl;
                break;
            case INST_GET_HEALTH:
                cout<<"체력이 " <<object->getHealth()<<"이다."<<endl;
                push(object->getHealth());
                break;
            case INST_GET_WISDOM:
                push(object->getWisdom());
                break;
            case INST_GET_AGILITY:
                push(object->getAgility());
                break;
            case INST_PLAY_SOUND:
                playSound(pop());
                break;
            case INST_SPAWN_PARTICLES:
                spawnParticles(pop());
                break;
            }
        }
    }
private:
    static const int MAX_STACK = 128;
    int stackSize_;
    int stack_[MAX_STACK];
    Object* object;
};
int main(){
    VM vm;
    v_object_list.push_back(new Object(30,20,50));
    char command[7] = {0,0,1,5,0,50,2};
    vm.interpret(command,7);
    return 0;
}