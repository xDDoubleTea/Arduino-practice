#include <Servo.h>

Servo myservo;  // 建立SERVO物件

const int trigger = 2;
const int echo = 3;
long distance = 0;
long echo_time = 0;
int test_time = 10;

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
