
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
int DigitalPin_L = 3;
int DigitalPin_R = 12;

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


void forward()    // 前進
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

void line_(){
  
  lmp = 100;
  rmp = 110;
  analogWrite(MotorA_PWMA, lmp); //left motor power
  analogWrite(MotorB_PWMB, rmp); //right motor power
  
  //if(digitalRead(DigitalPin_L)==1){
    //if(digitalRead(DigitalPin_R)==1){
      forward();
    //}
    //else{
      //turnR(1);
    //}
  //}
  //else{
   // if(digitalRead(DigitalPin_R)==0){
     //stopRL(5); 
    //}
    //else{
     // turnL(1);
    //}
  //}
}


void IRsensor()
{
  Serial.print("Right digital:");
  Serial.println(digitalRead(DigitalPin_R));
  Serial.print("Left digital:");
  Serial.println(digitalRead(DigitalPin_L));
  
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
    line_();
    //Serial.println("=====");
    //Serial.println(lmp);
    //Serial.println(rmp);
    
}
