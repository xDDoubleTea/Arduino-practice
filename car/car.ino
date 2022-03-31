
//#include <LiquidCrystal_I2C.h>
// L298N 馬達驅動板
// 宣告 MotorA 為右邊
// 宣告 MotorB 為左邊

#define MotorA_I1     8  //定義 I1 接腳
#define MotorA_I2     9  //定義 I2 接腳
#define MotorB_I3     10  //定義 I3 接腳
#define MotorB_I4     11 //定義 I4 接腳
#define MotorA_PWMA   6 //定義 ENA (PWM調速) 接腳
#define MotorB_PWMB   5 //定義 ENB (PWM調速) 接腳

int DigitalPin_R = A1;
int DigitalPin_L = A0; 
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
  pinMode(DigitalPin_R, INPUT);
  pinMode(DigitalPin_L, INPUT);


  
  
  pinMode(MotorA_PWMA, OUTPUT);
  pinMode(MotorB_PWMB, OUTPUT);
  

}


void forward()    // 前進
{
    digitalWrite(MotorA_I1,HIGH);   
    digitalWrite(MotorA_I2,LOW);
    digitalWrite(MotorB_I3,LOW);   
    digitalWrite(MotorB_I4,HIGH);
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

void line_(){
  //r_ana = analogRead(AnalogPin_R);
  //l_ana = analogRead(AnalogPin_L);
  //右邊在偵測到黑色時訊號值會是300多,左邊在偵測到黑色時訊號是195多
  //(希望變化量差不多)
  
  lmp = 100;
  rmp = 100;
  analogWrite(MotorA_PWMA, lmp); //left motor power
  analogWrite(MotorB_PWMB, rmp); //right motor power
  forward();
  //if(digitalRead(DigitalPin_L)==1)
}


void IRsensor()
{
  Serial.print("Left analog:");
  Serial.println(digitalRead(DigitalPin_L));
  Serial.print("Right analog:");
  Serial.println(digitalRead(DigitalPin_R));

  
  delay(50);
}

/*
void back(int g)    //後退
{
    digitalWrite(MotorA_I1,HIGH);    //馬達（右）逆時針轉動
    digitalWrite(MotorA_I2,LOW);
    digitalWrite(MotorB_I3,LOW);    //馬達（左）順時針轉動
    digitalWrite(MotorB_I4,HIGH);
    delay(g * 100);     
}
*/
void loop() {
    //lmp = 200;
    //rmp = 200;
    //analogWrite(MotorA_PWMA, lmp); //left motor power
    //analogWrite(MotorB_PWMB, rmp); //right motor power
    //forward(10);
    //IRsensor();
    //stopRL(5);
    //line_();
    IRsensor();
    
    //Serial.println("=====");
    //Serial.println("lana");
    //Serial.println(l_ana);
    //Serial.println("rana");
    //Serial.println(r_ana);
    
    delay(50);
}
