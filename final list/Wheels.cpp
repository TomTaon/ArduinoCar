#include <Arduino.h>
#include "Wheels.h"

#define SET_MOVEMENT(side,f,b) digitalWrite( side[0], f);\
                               digitalWrite( side[1], b)

Wheels::Wheels() 
{ }

void Wheels::attachRight(int pF, int pS, int pB)
{
    pinMode(pF, OUTPUT);
    pinMode(pB, OUTPUT);
    pinMode(pS, OUTPUT);
    this->pinsRight[0] = pF;
    this->pinsRight[1] = pB;
    this->pinsRight[2] = pS;
}


void Wheels::attachLeft(int pF, int pS, int pB)
{
    pinMode(pF, OUTPUT);
    pinMode(pB, OUTPUT);
    pinMode(pS, OUTPUT);
    this->pinsLeft[0] = pF;
    this->pinsLeft[1] = pB;
    this->pinsLeft[2] = pS;
}

void Wheels::attach(int pRF, int pRB, int pRS, int pLF, int pLB, int pLS)
{
    this->attachRight(pRF, pRB, pRS);
    this->attachLeft(pLF, pLB, pLS);
}

void Wheels::setSpeedRight(uint8_t s)
{
    analogWrite(this->pinsRight[2], s);
}

void Wheels::setSpeedLeft(uint8_t s)
{
    analogWrite(this->pinsLeft[2], s);
}

void Wheels::setSpeed(uint8_t s)
{
    setSpeedLeft(s);
    setSpeedRight(s);
}

void Wheels::forwardLeft() 
{
    SET_MOVEMENT(pinsLeft, LOW, HIGH);
}

void Wheels::forwardRight() 
{
    SET_MOVEMENT(pinsRight, HIGH, LOW);
}

void Wheels::forward()
{
    this->forwardLeft();
    this->forwardRight();
}

void Wheels::backLeft()
{
    SET_MOVEMENT(pinsLeft, HIGH, LOW);
}

void Wheels::backRight()
{
    SET_MOVEMENT(pinsRight, LOW, HIGH);
}

void Wheels::back()
{
    this->backLeft();
    this->backRight();
}

void Wheels::goForward(int cm)
{
    this->lTicks = 0;
    this->rTicks = 0;
    
    cm = cm * 100;
    int cm2 = cm;
    
    bool a = true;
    bool b = true;
    
    this->forwardLeft();
    this->forwardRight();
    
    while(a || b){

      Serial.print(this->lTicks);
      Serial.print("  ");
      Serial.println(this->rTicks);
      
      if (this->lTicks > cm && a == true){
        this->stopRight();
        a = false;
      }

      if (this->rTicks > cm2 && b == true){
        this->stopLeft();
        b = false;
      }
    }
}

void Wheels::goBack(int cm)
{
    this->lTicks = 0;
    this->rTicks = 0;
  
    cm = cm * 100;
    int cm2 = cm;  
    
    bool a = true;
    bool b = true;
    
    this->backLeft();
    this->backRight();
    
    while(a || b){
      Serial.print(this->lTicks);
      Serial.print("  ");
      Serial.println(this->rTicks);
      
      if (this->lTicks > cm && a == true){
        this->stopRight();
        a = false;
      }

      if (this->rTicks > cm2 && b == true){
        this->stopLeft();
        b = false;
      }
    }
}

void Wheels::rotateRight(float angel)
{
    this->lTicks = 0;
    this->rTicks = 0;

    
    angel = angel * 30;
    float angel2 = angel;

    bool a = true;
    bool b = true;
    
    this->forwardRight();
    this->backLeft();
    
    while(a || b){

      Serial.print(this->lTicks);
      Serial.print("  ");
      Serial.println(this->rTicks);
      
      if (this->lTicks > angel && a == true){
        this->stopLeft();
        a = false;
      }

      if (this->rTicks > angel2 && b == true){
        this->stopRight();
        b = false;
      }
    }  
}

void Wheels::rotateLeft(float angel)
{
    this->lTicks = 0;
    this->rTicks = 0;
    
    angel = angel * 30;
    float angel2 = angel;

    bool a = true;
    bool b = true;
    
    this->forwardLeft();
    this->backRight();
    
    while(a || b){
      Serial.print(this->lTicks);
      Serial.print("  ");
      Serial.println(this->rTicks);
      
      if (this->lTicks > angel && a == true){
        this->stopLeft();
        a = false;
      }

      if (this->rTicks > angel2 && b == true){
        this->stopRight();
        b = false;
      }
    }  
}

void Wheels::stopLeft()
{
    SET_MOVEMENT(pinsLeft, LOW, LOW);
}

void Wheels::stopRight()
{
    SET_MOVEMENT(pinsRight, LOW, LOW);
}

void Wheels::stop()
{
    this->stopLeft();
    this->stopRight();
}
