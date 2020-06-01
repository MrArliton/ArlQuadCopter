
//#include "Adafruit_BMP085.h"
#include "I2Cdev.h"
#include "MPU6050.h"
// Константа преобразования силы притяжения к градусам
#define TO_DEG 57.29577951308232087679815481410517033f
// Коф компламентарного фильтра
#define FK 0.1 
// Использовать барометр будем после готовой работы с акселерометром
//Adafruit_BMP085 bmp; // Барометр

MPU6050 mpu; // Акселерометр / гироскоп 

int16_t ax_raw, ay_raw, az_raw, gx_raw, gy_raw, gz_raw;
float angle_gx,angle_gy,angle_gz;
long int t_b; // Хранение прошлого состояния времени для гироскопа
// Функциия ограничения значения
float clamp(float v, float minv, float maxv){
    if( v>maxv )
        return maxv;
    else if( v<minv )
        return minv;
    return v;
}

// Инициализация работы сенсоров
bool InitialSensors(){
  t_b = millis();

//if(!bmp.begin()){
 // Serial.println("Error with init BMP180");
  //return false;    
//} 
 
  mpu.initialize();
  if(!mpu.testConnection()){
    Serial.println("Error with init MPU-6050");
  }
  Serial.println("InitSensors-Okey");
  return true;
}
// Получаем значения с сенсора
void updateSensors(){
  int t;
  mpu.getMotion6(&ax_raw, &ay_raw, &az_raw, &gx_raw, &gy_raw, &gz_raw);
  t = millis();
  int gx,gy,gz;
  
  // Расчёт углов относительно всех осей гироскопа
  gx = gx_raw/134; // Получаем градусы в секунду
  angle_gx = angle_gx + gx*(t-t_b)/1000.0; // По гироскопу x

  gy = gy_raw/134; // Получаем градусы в секунду
  angle_gy = angle_gy + gy*(t-t_b)/1000.0; // По гироскопу y

  gz = gz_raw/134; // Получаем градусы в секунду
  angle_gz = angle_gz + gz*(t-t_b)/1000.0; // По гироскопу z
  
  t_b = t; // Присваеваем новое старое значение
} 
// Функции компламентарного фильтра с использованием данных акселерометра 
float getRotateX(){
  float ay;
  float angle_ax;
  
  ay = ay_raw / (4096.0*4.0); // Получаем значения ускорения
  ay = clamp(ay,-1.0,1.0);
  angle_ax = 90-TO_DEG*acos(ay); // По акселерометру
  
  angle_gx = angle_gx*(1-FK) + angle_ax*FK; // Коректировка с использованием аккселерометра
  return angle_gx;
}
float getRotateY(){
   float ax;
  float angle_ay;
  
  ax = ax_raw / (4096.0*4.0); // Получаем значения ускорения
  ax = clamp(ax,-1.0,1.0);
  angle_ay = 90-TO_DEG*acos(ax); // По акселерометру
  
  angle_gy = angle_gy*(1-FK) + angle_ay*FK; // Коректировка с использованием аккселерометра
  return angle_gy;
}
float getRotateZ(){
  return angle_gz;
}
