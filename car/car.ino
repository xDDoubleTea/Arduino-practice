// L298N 馬達驅動板
// 宣告 MotorA 為右邊
// 宣告 MotorB 為左邊

#define MotorA_I1     A0  //定義 I1 接腳
#define MotorA_I2     A1  //定義 I2 接腳
#define MotorB_I3     A2  //定義 I3 接腳
#define MotorB_I4     A3 //定義 I4 接腳
#define MotorA_PWMA   A4 //定義 ENA (PWM調速) 接腳
#define MotorB_PWMB   A5  //定義 ENB (PWM調速) 接腳



void setup()
{
  Serial.begin(9600);
  
  pinMode(MotorA_I1,  OUTPUT);
  pinMode(MotorA_I2,  OUTPUT);
  pinMode(MotorB_I3,  OUTPUT);
  pinMode(MotorB_I4,  OUTPUT);
  pinMode(MotorA_PWMA, OUTPUT);
  pinMode(MotorB_PWMB, OUTPUT);
  

}

void advance()    // 前進
{
    digitalWrite(MotorA_I1,LOW);   //馬達（右）順時針轉動
    digitalWrite(MotorA_I2,HIGH);
    digitalWrite(MotorB_I3,HIGH);   //馬達（左）逆時針轉動
    digitalWrite(MotorB_I4,LOW);
    delay(100);
}

void turnR(int d)    //右轉
{
    digitalWrite(MotorA_I1,LOW);    //馬達（右）逆時針轉動
    digitalWrite(MotorA_I2,HIGH);
    digitalWrite(MotorB_I3,LOW);   //馬達（左）逆時針轉動
    digitalWrite(MotorB_I4,HIGH);
    delay(d * 100);
}

void turnL(int e)    //左轉
{
    digitalWrite(MotorA_I1,HIGH);   //馬達（右）順時針轉動
    digitalWrite(MotorA_I2,LOW);
    digitalWrite(MotorB_I3,HIGH);    //馬達（左）順時針轉動
    digitalWrite(MotorB_I4,LOW);
    delay(e * 100);
}    

void stopRL(int f)  //停止
{
    digitalWrite(MotorA_I1,HIGH);   //馬達（右）停止轉動
    digitalWrite(MotorA_I2,HIGH);
    digitalWrite(MotorB_I3,HIGH);   //馬達（左）停止轉動
    digitalWrite(MotorB_I4,HIGH);
    delay(f * 100);
}

void back(int g)    //後退
{
    digitalWrite(MotorA_I1,HIGH);    //馬達（右）逆時針轉動
    digitalWrite(MotorA_I2,LOW);
    digitalWrite(MotorB_I3,LOW);    //馬達（左）順時針轉動
    digitalWrite(MotorB_I4,HIGH);
    delay(g * 100);     
}

void loop() 
{



    analogWrite(MotorA_PWMA,200);    //設定馬達 (右) 轉速
    analogWrite(MotorB_PWMB,200);    //設定馬達 (左) 轉速
    advance();
}
