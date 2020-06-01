#include <Wire.h>
int times;
void setup() {
 // Инициализация всех систем управления
 InitialControll();
 InitialSensors();
 times = millis();
}

void loop() {
  delay(20);
  updateSensors();
  if(millis()-500>times){
  Serial.print("x-");
  Serial.println(getRotateX());
  Serial.print("y-");
  Serial.println(getRotateY());
  }
}
