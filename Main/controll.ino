// Пины управления моторами
#define Prop_a 11 // y-- x--
#define Prop_w 10 // y-- x++
#define Prop_s 6 // y++ x--
#define Prop_d 5 // y++ x++
// Переменные регуляции скорости для стабилизации
float forceLF = 0; //6
float forceLB = 0; //5
float forceRF = 0; //10
float forceRB = 0; //11
// Переменные управления квадрокоптером 
float pitch = 0; // Тангаж %наклона 0-45 градусов
float roll = 0; // Крен %наклона 0-45 градусов
float yaw = 0; // Рысканье % разворот 360

//Инициализация управления моторами
bool InitialControll(){
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
int[] updateForce(){
  
}
// Функция прямого изменения тяги
void setDW(int a,int w,int s,int d){
  analogWrite(Prop_a,a);
  analogWrite(Prop_w,w);
  analogWrite(Prop_s,s);
  analogWrite(Prop_d,d);
}
