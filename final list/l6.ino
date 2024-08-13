#include <Servo.h>
#include "Wheels.h"
#include "PinChangeInterrupt.h"

// piny dla sonaru (HC-SR04)
#define TRIG A4
#define ECHO A5

// pin kontroli serwo (musi być PWM)
#define SERVO 9

// piny obrotomierzy
#define INTINPUT0 A0
#define INTINPUT1 A1


Wheels w;

Servo serwo;

int dis;
bool check;

int right;
int left;

void setup() {
  
  pinMode(TRIG, OUTPUT);    // TRIG startuje sonar
  pinMode(ECHO, INPUT);     // ECHO odbiera powracający impuls
  
  pinMode(INTINPUT0, INPUT);
  pinMode(INTINPUT1, INPUT);

  serwo.attach(SERVO);
  
  PCICR  = 0x02;  // włącz pin change interrupt dla 1 grupy (A0..A5)
  PCMSK1 = 0x03;  // włącz przerwanie dla A0, A1

  Serial.begin(9600);

  w.attach(2,3,4,5,6,7);
  w.setSpeed(150);

  /*for(int angle = 0; angle <= 180; angle += 30) {
    lookAndTellDistance(angle);
    delay(500);
  }*/
}

void loop(){

  serwo.write(78);
  dis = look(78);

  w.forward();

  
  while(dis > 27){
    dis = lookAndTellDistance(75);
  }


  w.stop();


  while(1){
  
      delay(500);
      
      right = look(0);
      left  = look(156);
      
      if(right > 36 || left > 36){
        
        if(right > left){
          delay(500);
          w.rotateLeft(2.2);
          break;
        }
        else{
          delay(500);
          w.rotateRight(2.2);
          break;
        }
      }
      
      else{
        w.goBack(1);
      }
  }
}


int lookAndTellDistance(byte angle) {
  
  unsigned long tot;      // czas powrotu (time-of-travel)
  unsigned int distance;

  Serial.print("Patrzę w kącie ");
  Serial.print(angle);
  serwo.write(angle);
  
/* uruchamia sonar (puls 10 ms na `TRIGGER')
 * oczekuje na powrotny sygnał i aktualizuje
 */
 
  digitalWrite(TRIG, HIGH);
  delay(10);
  digitalWrite(TRIG, LOW);
  
  tot = pulseIn(ECHO, HIGH);

/* prędkość dźwięku = 340m/s => 1 cm w 29 mikrosekund
 * droga tam i z powrotem, zatem:
 */
 
  distance = tot/58;

  Serial.print(": widzę coś w odległości ");
  Serial.println(distance);

  return distance;
}

int look(byte angle) {
  
  unsigned long tot;      // czas powrotu (time-of-travel)
  unsigned int distance;

  Serial.print("Patrzę w kącie ");
  Serial.print(angle);
  serwo.write(angle);
  
  delay(600);
  
/* uruchamia sonar (puls 10 ms na `TRIGGER')
 * oczekuje na powrotny sygnał i aktualizuje
 */
 
  digitalWrite(TRIG, HIGH);
  delay(10);
  digitalWrite(TRIG, LOW);
  
  tot = pulseIn(ECHO, HIGH);

/* prędkość dźwięku = 340m/s => 1 cm w 29 mikrosekund
 * droga tam i z powrotem, zatem:
 */
 
  distance = tot/58;

  Serial.print(": widzę coś w odległości ");
  Serial.println(distance);

  return distance;
}


ISR(PCINT1_vect){
 if( (PINC & (1 << PC0)) ) 
 w.lTicks++;
 if( (PINC & (1 << PC1)) )
 w.rTicks++;
}
