int DS=2;//貨物
int DT=3;//出發
int SH=4;//上貨
int vrx = A1;//搖桿x
int vry = A2;//搖桿y
int sw = A3;//搖桿按鈕
int level = 4;
int direct[4] = {0,1,2,3}; 
//0up,1right,2down,3left
int now_direct = 0;
int snake_x[64]={3,3,3,3};/*蛇的身體位置紀錄表*/
int snake_y[64]={3,4,5,6};/*0是尾巴*/
long timer = millis();
int head_x=3,head_y=5;  /*頭的位置*/
int food_x = 9;
int food_y = 9;
int before_food_x = 9;
int before_food_y = 9;
int speed = 500;




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
    {0,0,0,1,1,1,1,0},/*第3行數值*/
    {0,0,0,0,0,0,0,0},/*第4行數值*/
    {0,0,0,0,0,0,0,0},/*第5行數值*/
    {0,0,0,0,0,0,0,0},/*第6行數值*/
    {0,0,0,0,0,0,0,0}/*第7行數值*/
};

bool game_over[8][8] = {
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





void read_way(){
  int x = analogRead(vrx);
  int y = analogRead(vry);
  //0up,1right,2down,3left
  if(x > 768 && now_direct != 2){
    now_direct = 0;
  }
  if(x < 256){
    if(now_direct != 0)
      now_direct = 2;
  }
  if(y > 768){
    if(now_direct != 3)
      now_direct = 1;
  }
  if(y < 256){
    if(now_direct != 1)
      now_direct = 3;
  }


}
void change_way(){
  
  
  if(now_direct == 0){
    head_y = (head_y+1)%8;
  }
  else if (now_direct == 1){
    head_x = (head_x+1)%8;
  }
  else if(now_direct == 2){
    head_y = (head_y+7)%8;
  }
  else if(now_direct == 3){
    head_x = (head_x+7)%8;
  }
}


void go(){
    read_way();
    for(int i = 0; i<level-1; i++){
      if(head_x == snake_x[level] && head_y == snake_y[level]){
        max7219(table_address,game_over);
        delay(1000000);
      }
    }
      
    table_data[snake_x[0]][snake_y[0]]=0;/*尾巴的點暗*/
    /*先從尾巴開始縮*/
    for(int i=0;i<level-1;i++){
        snake_x[i]=snake_x[i+1];
        snake_y[i]=snake_y[i+1];
    }
    /*依照方向移動頭部座標*/
    change_way();
    /*紀錄頭部位置*/
    snake_x[level-1]=head_x;
    snake_y[level-1]=head_y;
    table_data[head_x][head_y]=1;/*頭的點亮*/
    
    if(head_x == food_x && head_y == food_y){
      food();
      level += 1;
    }
}

void food(){
  //隨機取2數當作座標  (x,y) 
    food_x = rand()%8;
    food_y = rand()%8;
      if(table_data[food_x][food_y]){
        food();
      }
    table_data[food_x][food_y] = 1;
}



void setup() {
    pinMode(DS,OUTPUT);
    pinMode(DT,OUTPUT);
    pinMode(SH,OUTPUT); 
    pinMode(vrx,INPUT);
    pinMode(vry,INPUT);
    pinMode(sw,INPUT);
    max7219(set_address,set_data);
    Serial.begin(9600);
    food();
    
}

void loop() {  
    
    for(int i = 0; i < level-1; i++){
      if(head_x == snake_x[i] && head_y == snake_y[i]){
           max7219(table_address,game_over);
      }
      else{
        go();
        max7219(table_address,table_data);//更新版面 
        Serial.print("food_x=");
        Serial.print(food_x);
        Serial.print(", food_y=");
        Serial.print(food_y);
        Serial.print(", level");
        Serial.println(level);
        speed = 500-30*(level-1);
        delay(speed);
      }
    }
    
}
