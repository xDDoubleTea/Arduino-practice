
#include "Tetriminos.h"
int DS=2;//貨物
int DT=3;//出發
int SH=4;//上貨
int speaker = 5;
int bpm = 120;
long timer = millis();
const int clockwise = 8; //yellow
const int counter_clockwise = 9; //green
const int move_right = 6; //black
const int move_left = 7; //red
int left_bottom_X = 0;
int left_bottom_y = 0;
int right_bottom_X = 0;
int right_bottom_y = 0;
int most_left = 0;
int most_right = 0;
int most_bottom = 0;
int tmp = 0;
int pressed[2] = {0,0};
int block_type = 0;
bool touched_bottom = false;

bool occupied[8][8]={
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0}
};

bool set_address[8][8]={//初始設定
    {0,0,0,0,1,1,0,0},/*開啟顯示器模組*/
    {0,0,0,0,1,0,0,1},/*選用原始碼模式*/
    {0,0,0,0,1,1,1,1},/*關閉測試模式*/
    {0,0,0,0,1,0,1,0},/*設置初始亮度*/
    {0,0,0,0,1,0,1,1},/*8只LED全用*/
    {0,0,0,0,0,0,0,0},/*歸零*/
    {0,0,0,0,0,0,0,0},/*歸零*/
    {0,0,0,0,0,0,0,0}/*歸零*/
};
bool set_data[8][8]={//初始設定
    {0,0,0,0,0,0,0,1},/*開啟顯示器模組*/
    {0,0,0,0,0,0,0,0},/*選用原始碼模式*/
    {0,0,0,0,0,0,0,0},/*關閉測試模式*/
    {0,0,0,0,0,1,1,1},/*設置初始亮度*/
    {0,0,0,0,0,1,1,1},/*8只LED全用*/
    {0,0,0,0,0,0,0,0},/*歸零*/
    {0,0,0,0,0,0,0,0},/*歸零*/
    {0,0,0,0,0,0,0,0}/*歸零*/
};
bool table_address[8][8]={
    {0,0,0,0,0,0,0,1},/*第1行地址*/
    {0,0,0,0,0,0,1,0},/*第2行地址*/
    {0,0,0,0,0,0,1,1},/*第3行地址*/
    {0,0,0,0,0,1,0,0},/*第4行地址*/
    {0,0,0,0,0,1,0,1},/*第5行地址*/
    {0,0,0,0,0,1,1,0},/*第6行地址*/
    {0,0,0,0,0,1,1,1},/*第7行地址*/
    {0,0,0,0,1,0,0,0}/*第8行地址*/
};
bool table_data[8][8]={
    {0,0,0,0,0,0,0,0},/*第0行數值*/
    {0,0,0,0,0,0,0,0},/*第1行數值*/
    {0,0,0,0,0,0,0,0},/*第2行數值*/
    {0,0,0,0,0,0,0,0},/*第3行數值*/
    {0,0,0,0,0,0,0,0},/*第4行數值*/
    {0,0,0,0,0,0,0,0},/*第5行數值*/
    {0,0,0,0,0,0,0,0},/*第6行數值*/
    {0,0,0,0,0,0,0,0}/*第7行數值*/
};




void max7219(bool address[8][8],bool data[8][8]){
    for(int i = 0; i < 8; i++){
        digitalWrite(DT, LOW);//貨車開門
        for (int j = 0; j < 8; j++)  {
            digitalWrite(SH, LOW);//活塞收回
            digitalWrite(DS, address[i][j]);
            digitalWrite(SH, HIGH);//活塞推出
        }
        for (int j = 0; j < 8; j++)  {
            digitalWrite(SH, LOW);//活塞收回
            digitalWrite(DS, data[i][j]);
            digitalWrite(SH, HIGH);//活塞推出
        }
        digitalWrite(DT, HIGH);//貨車出發
    }
}

void spawn(int type){
  //type 0:T,1:I,2:O,3:J,4:L,5:S,6:Z
  if(type == 0){
    for(int i = 0; i < 8;i++){
      for(int j = 0; j < 8;j++){
        table_data[i][j] = T_tetrimino[i][j];
      }
    }
  }
  else if(type == 1){
    for(int i = 0; i < 8;i++){
      for(int j = 0; j < 8;j++){
        table_data[i][j] = I_tetrimino[i][j];
      }
    }
  }
   else if(type == 2){
    for(int i = 0; i < 8;i++){
      for(int j = 0; j < 8;j++){
        table_data[i][j] = O_tetrimino[i][j];
      }
    }
  } else if(type == 3){
    for(int i = 0; i < 8;i++){
      for(int j = 0; j < 8;j++){
        table_data[i][j] = J_tetrimino[i][j];
      }
    }
  } else if(type == 4){
    for(int i = 0; i < 8;i++){
      for(int j = 0; j < 8;j++){
        table_data[i][j] = L_tetrimino[i][j];
      }
    }
  } else if(type == 5){
    for(int i = 0; i < 8;i++){
      for(int j = 0; j < 8;j++){
        table_data[i][j] = S_tetrimino[i][j];
      }
    }
  } else if(type == 6){
    for(int i = 0; i < 8;i++){
      for(int j = 0; j < 8;j++){
        table_data[i][j] = Z_tetrimino[i][j];
      }
    }
  }
}

void move(){
  if(digitalRead(move_left) == HIGH && touched_bottom == false){
    for(int i = 0; i < 7;i++){
      for(int j = 0; j < 8;j++){
        if(table_data[i][j]==1){
          left_bottom_X = i;
          left_bottom_y = j;
          break;
      }
      }
    }
    for (int i = 6; i>=0; i--){
      for(int j = 0;j<8;j++){
        if (table_data[i][j] == 1){
          most_left = j;
          break;
        }
      }
      delay(203);
}

    Serial.print("leftx:");
    Serial.print(left_bottom_X);
    Serial.print("lefty:");
    Serial.println(left_bottom_y);
    Serial.print("most left:");
    Serial.println(most_left);
    if(left_bottom_y >=1&&most_left>=1){
      for(int i = 6; i >= 0;i--){
      for(int j = 0; j < 8;j++){
        if(table_data[i][j]==1 && j>=1){
          table_data[i][j-1] = 1;
          table_data[i][j] = 0;
      }
      }
    }
    }
    
    
  }
if(digitalRead(move_right) == HIGH && touched_bottom == false){
    for(int i = 0; i < 7;i++){
      for(int j = 7;j>=0;j--){
        if(table_data[i][j]==1){
          right_bottom_X = i;
          right_bottom_y = j;
          break;
      }
      }
    }
    for (int i = 6; i>=0; i--){
      for(int j = 7;j>=0;j--){
        if (table_data[i][j] == 1){
          most_right = j;
          break;
        }
      }
}

    Serial.print("rightx:");
    Serial.print(right_bottom_X);
    Serial.print("righty:");
    Serial.println(right_bottom_y);
    Serial.print("most right:");
    Serial.println(most_right);
    if(right_bottom_y <=6 && most_right<=6){
      for(int i = 6; i >= 0;i--){
      for(int j = 7;j>=0;j--){
        if(table_data[i][j]==1 && j<=6){
          table_data[i][j+1] = 1;
          table_data[i][j] = 0;
      }
      }
    }
    }
    
    
  }
}


void drop(){
  for(int i = 0; i < 7;i++){
      for(int j = 0; j < 8;j++){
        if(table_data[i][j]==1){
          left_bottom_X = i;
          left_bottom_y = j;
          break;
      }
      }
    }
   
    for(int i = 0; i < 7 ;i++){
      for(int j = 7; j >0;j--){
        if(table_data[i][j]==1){
          right_bottom_X = i;
          right_bottom_y = j;
          break;
      }
      }
    }
    Serial.print("left bottom x:");
    Serial.print(left_bottom_X);
    Serial.print("left bottom y:");
    Serial.println(left_bottom_y);
    Serial.print("right bottom x:");
    Serial.print(right_bottom_X);
    Serial.print("right bottom y:");
    Serial.println(right_bottom_y);
    Serial.println(touched_bottom);
  if(left_bottom_X < 6 && left_bottom_X >= 0){
    for(int i=6;i>=0;i--){
    for(int j=0;j<8;j++){
      if(table_data[i][j]==1){
      table_data[i+1][j]=1;
      table_data[i][j]=0;}
    }
  }
  }
  else if(left_bottom_X == 6 && right_bottom_X == 6 && touched_bottom == false){
    touched_bottom = true;
    Serial.println(touched_bottom);
    
  
      for(int i=6;i>=0;i--){
      for(int j=0;j<8;j++){
        if(table_data[i][j]==1){
        table_data[i+1][j]=1;
        table_data[i][j]=0;}
      }}
  max7219(table_address, table_data);
  
  delay(110);
  block_type = random(0,7);
  spawn(block_type);
  delay(100);
  touched_bottom = false;
  }
  }



void touch_bottom(){
  //若方塊底部碰到已存入之方格或底部，則回傳true
}

/*

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
unsigned int beats[250] = {
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
    tone(speaker, melody[i]);
    delay((bpm/60)*100*beats[i]-35);
    noTone(speaker);
    delay(35);
  }
}
*/
void setup() {
    pinMode(speaker, OUTPUT);
    pinMode(DS,OUTPUT);
    pinMode(DT,OUTPUT);
    pinMode(SH,OUTPUT); 
    pinMode(clockwise, INPUT);
    pinMode(counter_clockwise, INPUT);
    pinMode(move_right, INPUT);
    pinMode(move_left, INPUT);
    max7219(set_address,set_data);
    Serial.begin(9600);
    block_type = random(0,7);
    spawn(block_type);
    max7219(table_address, table_data);
}

void loop() {  
  delay(1000);
  //music();
  drop();
  move();
  max7219(table_address, table_data);
}