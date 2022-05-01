#include<iostream>

// # 상태 기반 상태 전이
// 전등 스위치를 모델링해보자. 상태 값과 다른 상태로 전이할 수단을 가지면 된다.
class State{
    virtual void on(LightSwitch *ls){
        std::cout << "Light is already on\n";
    }
    virtual void off(LightSwitch *ls){
        std::cout << "Light is already off\n";
    }
};

class OffState:public State{};
class OnState:public State{};

class LightSwitch{
    State *state;
public:
    LightSwitch(){
        state = new OffState();
    }
    void set_state(State* state){
        this->state = state;
    }
};

