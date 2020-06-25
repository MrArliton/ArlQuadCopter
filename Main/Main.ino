#include "GyverPID.h"
long int times;

#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

void setup() {
 // Инициализация всех систем управления
sbi(ADCSRA,ADPS2) ;
cbi(ADCSRA,ADPS1) ;
cbi(ADCSRA,ADPS0) ;

 InitialControll();
 InitialSensors();
 times = millis();

 
}

void loop() {
  updateSensors();
  //if(millis()-300>times){
    getCommand();
    updateForce();
    times = millis();
  //Serial.print("x-");
 // Serial.println(getRotateX());
 // Serial.print("y-");
 // Serial.println(getRotateY());
 // }
}
