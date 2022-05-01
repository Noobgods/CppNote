#include<iostream>

// 임시 키
#define PRESS_B 'B'
#define PRESS_DOWN 40
#define RELEASE_DOWN 41

// 상태를 열거형으로 정의
enum State{
    STATE_STANDING,
    STATE_JUMPING,
    STATE_DUCKING,
    STATE_DIVING
};

// 임시 키 입력을 위한 임시 클래스
struct Input{
    bool operator==(char&& input){
        if(input == key)
            return true;
        else
            return false;
    }
private:
    char key;
};

// 상태를 사용할 Heroine 클래스
struct Heroine{
    Heroine(int maxCharge, int jumpVelocity)
     : MAX_CHARGE(maxCharge),
       JUMP_VELOCITY(jumpVelocity){} 

    void superBomb();
    
    virtual void handleInput(Input);
    virtual void update();

    const int MAX_CHARGE;
    const int JUMP_VELOCITY;

    HeroineState state_;
private:
};

// 상태를 변경할 때 호출하는 handleInput 함수
void Heroine::handleInput(Input input){
    // 현재 상태의 input에 따라 상태가 변경된다.
    HeroineState* state = state_->handleInput(*this, input);
    if(state != NULL){
        delete state_;
        state_ = state;
    }
}
void Heroine::update(){
    state_->update(*this);
}

// 상태 인터페이스
class HeroineState{
public:
    virtual ~HeroineState(){}
    virtual HeroineState* handleInput(Heroine& heroine,Input input){}
    virtual void update(Heroine& heroine){}

    static StandingState standing;
    static DuckingState ducking;
    static JumpingState jumping;
    static DivingState diving;
};

///////////////////////////////////////////////////////////////
// 아래는 상태 인터페이스를 상속받는 상태들

class DuckingState: public HeroineState {
public:
    DuckingState() : chargeTime_{0}{}

    virtual HeroineState* handleInput(Heroine&, Input);
    virtual void update(Heroine&);
private:
    int chargeTime_;
};

HeroineState* DuckingState::handleInput(Heroine& heroine, Input input){
    if(input == RELEASE_DOWN){
        heroine.state_ = &HeroineState::standing;
        //heroine.setGraphics(IMAGE_STAND);
    }
}

void DuckingState::update(Heroine& heroine){
    chargeTime_++;
    if(chargeTime_ > heroine.MAX_CHARGE){
        heroine.superBomb();
    }
}
//////////////////////////////////////////////////////////////////
class StandingState: public HeroineState {
public:
    StandingState(){}

    virtual HeroineState* handleInput(Heroine&, Input);
    virtual void update(Heroine&);
private:
};
HeroineState* StandingState::handleInput(Heroine& heroine, Input input){}
void StandingState::update(Heroine& heroine){}

//////////////////////////////////////////////////////////////////
class JumpingState: public HeroineState {
public:
    JumpingState(){}

    virtual HeroineState* handleInput(Heroine&, Input);
    virtual void update(Heroine&);
private:
};
HeroineState* JumpingState::handleInput(Heroine& heroine, Input input){}
void JumpingState::update(Heroine& heroine){}

//////////////////////////////////////////////////////////////////
class DivingState: public HeroineState {
public:
    DivingState(){}

    virtual HeroineState* handleInput(Heroine&, Input);
    virtual void update(Heroine&);
private:
};
HeroineState* DivingState::handleInput(Heroine& heroine, Input input){}
void DivingState::update(Heroine& heroine){}
