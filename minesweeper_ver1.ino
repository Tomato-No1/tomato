#define   SW1   3
#define   SW2   2
#define   BZ    5
#define   CHATA_CHECK 30

int pin[] = {6,9,10,11,12,13};
bool mine[] = {true,true,true,true,true,true};
int temp[] = {};
int mine_set = 0,mineIs = 0,sizepin;

void setup()
{
  Serial.begin(9600);
  for(int i = 0;i < sizeof(pin)/sizeof(pin[0]);i++){
    pinMode(pin[i], OUTPUT);
    //点灯確認(本使用の際はLOWへ)
    digitalWrite(pin[i], HIGH);
    delay(200);
  }
  randomSeed(analogRead(A7));
  pinMode(SW1, INPUT_PULLUP);
  pinMode(SW2, INPUT_PULLUP);
  pinMode(BZ, OUTPUT);

  //初期配列の個数を計算（今回なら6）
  //なので，1引いて使いやすく
  sizepin = (sizeof(pin)/sizeof(pin[0])) - 1;
  Serial.print("sizepin is ");
  Serial.println(sizepin);
}

void loop()
{
  
  int choice_mine = 0;
  int cnt = 0,select_mine = 0,pinCnt = -1;
  int SelectMine;
  
  Serial.print("now sizepin ");
  Serial.println(sizepin);
  //mineの決定
  if(mine_set == 0){
    choice_mine = random(0,sizepin);
    mineIs = pin[choice_mine];
    mine_set = 1;
  }
  Serial.print("mine is ");
  Serial.println(mineIs);
  //
  do
  {
    if(digitalRead(SW1) == 0){
      if(CHATA_CHECK >= cnt){
        cnt++;
      }
    }else{
      cnt = 0;
    }
    if(cnt == CHATA_CHECK) select_mine++;
    if(select_mine > sizepin ) select_mine = 0;

    for(int j = 0;j <= sizepin;j++){
      //選択されているLEDはOFF
      digitalWrite(pin[j], (j == select_mine) ? LOW : HIGH);
    }
  } while (digitalRead(SW2) == 1);
  Serial.println("Your choice is...");
  SelectMine = pin[select_mine];
  delay(1000); 

  //Check mine
  if(SelectMine == mineIs){
    Serial.println("Bomb!!");
    //GameOver
    Bomb();
  }else{
    Serial.println("Safe!");
    for(int y = 0;y <= sizepin;y++){
      temp[y] = pin[y];
    }
    for(int x = 0;x <= sizepin;x++){
      if(temp[x] != SelectMine){
        pinCnt++;
        pin[pinCnt] = temp[x];
      }
    }
    sizepin = sizepin - 1;
  }
  delay(1000);
  for(int a = 0;a < sizeof(pin)/sizeof(pin[0]);a++){
    Serial.print("pin : ");
    Serial.println(pin[a]);
  }
  Serial.println("NEXT TIME");
  
}

void ALL_RESET( void ){

}

void Bomb( void ){
  /*
  while(true){
    tone(BZ, 1000, 200);
    delay(200);
    tone(BZ, 0, 200);
    delay(200);
  }
  */
}