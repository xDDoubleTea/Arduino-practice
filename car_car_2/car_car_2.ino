#include <Servo.h>

Servo myservo;  // 建立SERVO物件

const int trigger = 2;
const int echo = 3;
long distance = 0;
long echo_time = 0;
int test_time = 10;

#define MotorA_I1     8  //定義 I1 接腳
#define MotorA_I2     9  //定義 I2 接腳
#define MotorB_I3     10  //定義 I3 接腳
#define MotorB_I4     11 //定義 I4 接腳
#define MotorA_PWMA   6 //定義 ENA (PWM調速) 接腳
#define MotorB_PWMB   5 //定義 ENB (PWM調速) 接腳

///int AnalogPin_R = 3; 
//LiquidCrystal_I2C lcd(0x27,16,2);


int r_ana,l_ana,rmp,lmp;

void setup()
{
  Serial.begin(9600);
  
  //lcd.init();
  //lcd.backlight();
  
  pinMode(MotorA_I1,  OUTPUT);
  pinMode(MotorA_I2,  OUTPUT);
  pinMode(MotorB_I3,  OUTPUT);
  pinMode(MotorB_I4,  OUTPUT);
//  pinMode(AnalogPin_R, INPUT);
  //pinMode(AnalogPin_L, INPUT);
  pinMode(DigitalPin_R, INPUT);
  pinMode(DigitalPin_L, INPUT);
  
  
  pinMode(MotorA_PWMA, OUTPUT);
  pinMode(MotorB_PWMB, OUTPUT);
  

}


void forward(int a)    // 前進
{
    digitalWrite(MotorA_I1,HIGH);   
    digitalWrite(MotorA_I2,LOW);
    digitalWrite(MotorB_I3,LOW);   
    digitalWrite(MotorB_I4,HIGH);
    delay(100);
}

void turnL(int d)    
{
    digitalWrite(MotorA_I1,LOW);    
    digitalWrite(MotorA_I2,HIGH);
    digitalWrite(MotorB_I3,LOW);   
    digitalWrite(MotorB_I4,HIGH);
    delay(d * 100);
}

void turnR(int e)    
{
    digitalWrite(MotorA_I1,HIGH);   
    digitalWrite(MotorA_I2,LOW);
    digitalWrite(MotorB_I3,HIGH);    
    digitalWrite(MotorB_I4,LOW);
    delay(e * 100);
}    

void stopRL(int f)  //停止
{
    digitalWrite(MotorA_I1,HIGH);   //馬達停止轉動
    digitalWrite(MotorA_I2,HIGH);
    digitalWrite(MotorB_I3,HIGH);   //馬達停止轉動
    digitalWrite(MotorB_I4,HIGH);
    delay(f * 100);
}



void ultrasound_sensor(){
  digitalWrite(trigger, LOW);
  digitalWrite(trigger, HIGH);
  delay(test_time);
  digitalWrite(trigger,LOW);
  echo_time = pulseIn(echo, HIGH);
  distance = (echo_time/2)/29.1;
  Serial.print("Distance = ");
  Serial.print(distance);
  Serial.println("cm");
  
}

void Servo_motor(int degree){
  myservo.write(degree);  
  
}

void truning(){
  for(int i=0;i<180;i++){
      Servo_motor(i);
      delay(10);
    }
    for(int i=180;i>0;i--){
      Servo_motor(i);
      delay(10);
    }
}

void setup() {
  // put your setup code here, to run once:
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  Serial.begin(9600);
  myservo.attach(12);  // 設定要將伺服馬達接到哪一個PIN腳
}

void loop() {
  // put your main code here, to run repeatedly:
  
    
  
}
