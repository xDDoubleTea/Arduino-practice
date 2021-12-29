int DS=2;//貨物DIN
int DT=3;//出發CS
int SH=4;//上貨CLK
int left_s=8;
int right_s=9;
int l_button=7;//red
int r_button=6;//black
int point=0;
int center[2]={1,4};
int direct;//0:左 1:上 2:右 3:下
int speaker=5;
int bpm=120;
char shape='o';//ljzsoit
bool droping[8][8]=
{
    {0,0,0,1,1,0,0,0},
    {0,0,0,1,1,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0}
};
bool address[8][8]=
{
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
    {0,0,0,0,1,1,0,0},/*開啟或關閉顯示器模組*/
    {0,0,0,0,1,0,0,1},/*選用原始碼或解碼模式*/
    {0,0,0,0,1,1,1,1},/*開啟或關閉測試模式*/
    {0,0,0,0,1,0,1,0},/*亮度0~15*/
    {0,0,0,0,1,0,1,1},/*行數限制0~7*/
    {0,0,0,0,0,0,0,0},/*歸零*/
    {0,0,0,0,0,0,0,0},/*歸零糕*/
    {0,0,0,0,0,0,0,0}/*當歸鴨*/
};
bool set_data[8][8]={//初始設定
    {0,0,0,0,0,0,0,1},/*開啟(1)或關閉(0)顯示器模組*/
    {0,0,0,0,0,0,0,0},/*原始碼(0)解碼(1)模式*/
    {0,0,0,0,0,0,0,0},/*開啟(1)關閉(0)測試模式*/
    {0,0,0,0,1,1,1,1},/*設置初始亮度0*/
    {0,0,0,0,0,1,1,1},/*8行LED全用*/
    {0,0,0,0,0,0,0,0},/*歸零*/
    {0,0,0,0,0,0,0,0},/*歸零糕*/
    {0,0,0,0,0,0,0,0}/*當歸鴨*/
};
bool table_address[8][8]={
    {0,0,0,0,0,0,0,1},/*第1行地址*/
    {0,0,0,0,0,0,1,0},/*第2行地址*/
    {0,0,0,0,0,0,1,1},/*第3行地址*/
    {0,0,0,0,0,1,0,0},/*第4行地址*/
    {0,0,0,0,0,1,0,1},/*第5行地址*/
    {0,0,0,0,0,1,1,0},/*第6行地址*/
    {0,0,0,0,0,1,1,1},/*第7行地址*/
    {0,0,0,0,1,0,0,0} /*第8行地址*/
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
void setup() {
    pinMode(DS,OUTPUT);
    pinMode(DT,OUTPUT);
    pinMode(SH,OUTPUT); 
    pinMode(l_button,INPUT);
    pinMode(r_button,INPUT);
    pinMode(left_s,INPUT);
    pinMode(right_s,INPUT);
    //pinMode(,INPUT);
    max7219(set_address,set_data);
    Serial.begin(9600);
    max7219(table_address, droping);
   
    //lcd.init();
    //lcd.backlight();
    //lcd.setCursor(0,0);
    //lcd.print("score");
    //random   shape
}
/*void music(){
  for(int i = 0;i<153; i++){
    Serial.println(i);
    tone(speaker, melody[i]);
    delay((bpm/60)*100*beats[i]-35);
    noTone(speaker);
    delay(35);
  }
}*/
/*void spawn(){
  int x=rand()%7;
  center[1]=4;
  if(x==0){
    shape='l';
    droping[center[0]-1][center[1]]=1;
    droping[center[0]][center[1]]=1;
    droping[center[0]+1][center[1]]=1;
    droping[center[0]+1][center[1]+1]=1;
  }
  if(x==1){
    shape='j';
    center[0]=1;
    direct=3;
    droping[center[0]-1][center[1]]=1;
    droping[center[0]][center[1]]=1;
    droping[center[0]+1][center[1]]=1;
    droping[center[0]+1][center[1]-1]=1;
  }
  if(x==2){
    shape='z';
    center[0]=1;
    direct=3;
    droping[center[0]-1][center[1]]=1;
    droping[center[0]-1][center[1]-1]=1;
    droping[center[0]][center[1]]=1;
    droping[center[0]][center[1]+1]=1;
  }
  if(x==3){
    shape='s';
    center[0]=1;
    direct=3;
    droping[center[0]-1][center[1]]=1;
    droping[center[0]+1][center[1]-1]=1;
    droping[center[0]][center[1]]=1;
    droping[center[0]][center[1]-1]=1;
  }
  if(x==4){
    shape='o';
    center[0]=1;
    droping[center[0]][center[1]-1]=1;
    droping[center[0]-1][center[1]]=1;
    droping[center[0]-1][center[1]-1]=1;
  }
  if(x==5){
    shape='i';
    center[0]=0;
    direct=3;
    for(int i=-1;i<3;i++){
    droping[center[0]][center[1]+i]=1;
    }
  }
  if(x==6){
    shape='t';
    center[0]=0;
    direct=3;
    droping[center[0]-1][center[1]]=1;
    droping[center[0]][center[1]-1]=1;
    droping[center[0]][center[1]]=1;
    droping[center[0]][center[1]+1]=1;
  }
}
void in(){
  for(int i=0;i<8;i++){
    for(int j=0;j<8;j++){
      if(droping[i][j]==1){
      address[i][j]==1;
      droping[i][j]==0;}
    }
  }
}*/
void left_move(){
    center[1]=center[1]-1;
  for(int i=0;i<8;i++){
    for(int j=0;j<8;j++){
      if(droping[i][j]==1){
      droping[i][j-1]=1;
      droping[i][j]=0;}
    }
  }
}
void right_move(){
    center[1]=center[1]+1;
  for(int i=0;i<8;i++){
    for(int j=7;j>=0;j++){
      if(droping[i][j]==1){
      droping[i][j+1]=1;
      droping[i][j]=0;}
    }
  }
}
void score(){
  point++;
  //lcd.setCursor(0,1);
  //lcd.print(point); 
}
/*void spin(){
  if(shape=='o'){
    return;
  }
  if (shape=='i' )//0:左 1:上 2:右 3:下
    if(direct==3 or direct==1){
      for(int i=-1;i<3;i++){
        droping[center[0]][center[1]+i]=1;
      }
    }
    if(direct==2 or direct==0){
      for(int i=-1;i<3;i++){
        droping[center[0]+i][center[1]]=1;
      }
    }  
  
}*/
void moving(){
  center[0]=center[0]+1;
  for(int i=6;i>=0;i--){
    for(int j=0;j<8;j++){
      if(droping[i][j]==1){
      droping[i+1][j]=1;
      droping[i][j]=0;}//if(address[i+1][j]=1){/*in();spawn();*/ return;}    
    }
  }
  for(int i=0;i<8;i++){
    for(int j=0;j<8;j++){
      Serial.print(droping[i][j]);
    }
    Serial.println("  droping");
  }
}
void loop() {
    //music();
    delay(1000);
    /*
    if (digitalRead(l_button)==HIGH){
      left_move();}
    if (digitalRead(l_button)==HIGH){
      right_move;}
    if (digitalRead(left_s)==HIGH){
      direct--;
      spin;}
    if (digitalRead(right_s)==HIGH){
      direct++;
      spin;}*/
    //music();
    /*if(){
    direct=;
    spin;}*/
    moving();
    Serial.println("");
   
    max7219(table_address,droping);
    
    //max7219(table_address,address);
    
}