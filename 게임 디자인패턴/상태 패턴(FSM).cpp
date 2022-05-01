#include<iostream>

#define PRESS_B 'B'
#define PRESS_DOWN 40
#define RELEASE_DOWN 41

enum State{
    STATE_STANDING,
    STATE_JUMPING,
    STATE_DUCKING,
    STATE_DIVING
};

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

struct Heroine{
    Heroine(int maxCharge, int jumpVelocity)
     : MAX_CHARGE(maxCharge),
       JUMP_VELOCITY(jumpVelocity){} 

    void update();
    void superBomb();
private:
    void handleInput(Input input);

    float yVelocity_;
    int chargeTime_;

    const int MAX_CHARGE;
    const int JUMP_VELOCITY;
};

State state_ = STATE_JUMPING;
void Heroine::handleInput(Input input){
    switch (state_){
    case STATE_STANDING:
        if(input == PRESS_B){
            state_ = STATE_JUMPING;
            yVelocity_ = JUMP_VELOCITY;
            //setGraphics(IMAGE_JUMPING);
        }
        else if(input == PRESS_DOWN){
            state_ = STATE_DUCKING;
            chargeTime_ = 0;
            //setGraphic(IMAGE_DUCK);
        }
        break;
    case STATE_JUMPING:
        if(input==PRESS_DOWN){
            state_ = STATE_DIVING;
            //setGraphic(IMAGE_DIVE);
        }
        break;
    case STATE_DUCKING:
        if(input == RELEASE_DOWN){
            state_ = STATE_STANDING;
            //setGraphics(IMAGE_STAND);
        }
    }   
}

void Heroine::update(){
    if(state_ == STATE_DUCKING){
        chargeTime_++;
        if(chargeTime_ > MAX_CHARGE)
            superBomb();
    }
}

void Heroine::superBomb(){
    std::cout << "BOOOM!" << std::endl;
}