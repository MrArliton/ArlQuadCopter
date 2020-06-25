
// Пины управления моторами
#define Prop_a 10 // y-- x--
#define Prop_w 11 // y-- x++
#define Prop_s 5 // y++ x--
#define Prop_d 6 // y++ x++
//
#define deltaForceMax 50.0
#define wtLF 200
#define wtLB 200
#define wtRF 200
#define wtRB 200
#define cofStart 2
// Переменные регуляции скорости для стабилизации
float forceLF = 0; //s
float forceLB = 0; //d
float forceRF = 0; //w
float forceRB = 0; //a
// Переменные управления квадрокоптером 
float engine = 0; // Общая мощность двигателей 0-100% 0-200 PWM
float pitch = 0; // Тангаж %наклона -20-20 градусов
float roll = 0; // Крен %наклона -20-20 градусов
float yaw = 0; // Рысканье % разворот 360

GyverPID rP(2, 0.05, 0.01);
GyverPID rR(2, 0.05, 0.01);
GyverPID rY(2, 0.05, 0.01);
//Инициализация управления моторами
bool InitialControll(){
  rP.setLimits(-255,255);
  rR.setLimits(-255,255);
  rY.setLimits(-255,255);

  Serial.begin(9600);
  pinMode(Prop_a,OUTPUT);
  pinMode(Prop_w,OUTPUT);
  pinMode(Prop_s,OUTPUT);
  pinMode(Prop_d,OUTPUT);
  analogWrite(Prop_a,0);
  analogWrite(Prop_w,0);
  analogWrite(Prop_s,0);
  analogWrite(Prop_d,0);
  Serial.println("InitControll-Okey");
  return true;
}
// Обновляем ускорение двигателей относительно датчиков

void updateForce(){
 float x,y;
 getCommand(); // Получаем команды
 x = getRotateX();
 y = getRotateY();
 rP.input = x;
 rR.input = y;
 rP.setpoint= pitch;
 rR.setpoint = roll;
//  rY.input();
// Моя система регуляции
// forceLF = engine-(x/90.0+y/90.0)*deltaForceMax;
// forceLB = engine+(x/90.0-y/90.0)*deltaForceMax;
// forceRF = engine+(-x/90.0+y/90.0)*deltaForceMax;
// forceRB = engine+(x/90.0+y/90.0)*deltaForceMax;
  forceRF = engine*(wtRF/100);
  forceLF = engine*(wtLF/100);
  forceRB = engine*(wtLB/100);
  forceLB = engine*(wtLB/100);
  forceRF += (rP.getResultTimer()-rR.getResultTimer())/2; // Среднее по PID-ам
  forceRB += -(rP.getResultTimer()+rR.getResultTimer())/2;
  forceLF += (rP.getResultTimer()+rR.getResultTimer())/2;
  forceLB += (-rP.getResultTimer()+rR.getResultTimer())/2;
// Serial.print("=");
// Serial.print(forceLF);
// Serial.print(" ");
//// Serial.print(forceRF);
// Serial.println("=");
// Serial.print("=");
 //Serial.print(forceLB);
// Serial.print(" ");
 //Serial.print(forceRB);
 //Serial.println("=");
// Serial.println("");

 _setDW_(forceRB,forceRF,forceLF,forceLB);
}
// Функция опроса Serial на команды
bool getCommand(){
while(Serial.available()){
  int com = Serial.read();
  if(com=='p'){
  pitch = Serial.parseInt();  
  }else
  if(com=='r'){
  roll = Serial.parseInt();
  }else
  if(com=='y'){
  yaw = Serial.parseInt();
  }else
  if(com=='e'){
  engine = Serial.parseInt();
  }
}  
}
// Функция прямого изменения тяги
void _setDW_(int a,int w,int s,int d){
  analogWrite(Prop_a,clamp(a,0.0,255.0));
  analogWrite(Prop_w,clamp(w,0.0,255.0));
  analogWrite(Prop_s,clamp(s,0.0,255.0));
  analogWrite(Prop_d,clamp(d,0.0,255.0));
}
