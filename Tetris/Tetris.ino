#include <pitches.h>
int DS=2;//貨物
int DT=3;//出發
int SH=4;//上貨
int speaker = 5;
int bpm = 120;


int melody[250] = {
  E6,B5,C6,D6,C6,B5,A5,A5,C6,E6,D6,C6,B5,C6,D6,E6,C6,A5,A5,
  D6,F6,A6,G6,F6,E6,C6,E6,D6,C6,B5,C6,D6,E6,C6,A5,A5,
  E6,B5,C6,D6,C6,B5,A5,A5,C6,E6,D6,C6,B5,C6,D6,E6,C6,A5,A5,
  D6,F6,A6,G6,F6,E6,C6,E6,D6,C6,B5,C6,D6,E6,C6,A5,A5,
  E6,C6,D6,B5,C6,A5,G5_,B5,E6,C6,D6,B5,C6,E6,A6,G6_,
  E6,F6,E6,B5,E6,F6,E6,B5,
  E6,F6,E6,A5,E6,F6,E6,A5,
  E6,F6,E6,B5,E6,F6,E6,B5,
  C6,A5,E6,A5,F6,E6,C6,A5,
  D6,F6,A6,G6,F6,E6,C6,E6,D6,C6,B5,C6,D6,E6,C6,A5,A5,
  E6,C6,D6,B5,C6,A5,G5_,B5,E6,C6,D6,B5,C6,E6,A6,G6_
  };
//2 是四分音符
float beats[250] = {
  2,1,1,2,1,1,2,1,1,2,1,1,3,1,2,2,2,2,5,
  2,1,2,1,1,3,1,2,1,1,3,1,2,2,2,2,4,
  2,1,1,2,1,1,2,1,1,2,1,1,3,1,2,2,2,2,5,
  2,1,2,1,1,3,1,2,1,1,3,1,2,2,2,2,4,
  4,4,4,4,4,4,4,4,4,4,4,4,2,2,4,8,
  1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,3,
  2,1,2,1,1,3,1,2,1,1,3,1,2,2,2,2,4,
  4,4,4,4,4,4,4,4,4,4,4,4,2,2,4,8
};




void music(){
  for(int i = 0;i<153; i++){
    Serial.println(i);
    tone(speaker, melody[i]);
    delay((bpm/60)*100*beats[i]-35);
    noTone(speaker);
    delay(35);
  }
}

void setup() {

    Serial.begin(9600);
}

void loop() {  
  music();
}