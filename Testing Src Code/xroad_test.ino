/*
Declartion from David, 28/03/2024
這段code還需要經過調整才能用，
而且我覺得這種寫法可能會有隱性的嚴重bug，很有可能導致車輛失控，
在upload前請謹慎檢查。
*/

//IR sensor pin setting
#define L3 40
#define L2 38
#define M 36
#define R2 34
#define R3 32

//腳位設定
int PWMA = 11; //left motor 200
int PWMB = 12; //right motor 93
int AIN1 = 2;
int AIN2 = 3;
int BIN1 = 5;
int BIN2 = 6;

int w2 = 1;
int w3 = 2;
int Kp = 45;
int TpL = 100;
int TpR = 47;
int turn = 30;

//下一步的行動
enum action{
  straight, right, left, uTurn, stop
};

//利用array儲存action
static int actionNumber = 0;
const int route[6] = {1,3,0,3,2,4};

//判斷是否偵測到node
bool nodeDetected = false;

//馬達控制
void MotorWriting(double vL, double vR) {
  if(vR >= 0){
    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW);
  }
  else if(vR < 0){
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, HIGH);
    vR = -vR;
  }

  if(vL >= 0){
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
  }
  else if(vL < 0){
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH);
    vL = -vL; 
  }

  analogWrite(PWMA, vL);
  analogWrite(PWMB, vR);
}

//循跡控制
void Tracking() {
	//IR sensor pin setting
  int l3 = digitalRead(L3);
  int l2 = digitalRead(L2);
  int m = digitalRead(M);
  int r2 = digitalRead(R2);
  int r3 = digitalRead(R3);
  
  if((l3 + l2 + m + r2 + r3) != 0){
    double error = (l3*(-w3) + l2*(-w2) + r2*w2 + r3*w3)/(l3 + l2 + m + r2 + r3);
    double powerCorrection = Kp * error; // ex. Kp = 100, 也與w2 & w3有關
    double vR = (TpR - powerCorrection); // ex. Tp = 150, 也與w2 & w3有關
    double vL = (TpL + powerCorrection);
    if(vR >= 255) vR = 255;
    if(vL >= 255) vL = 255;
    if(vR <= -255) vR = -255;
    if(vL <= -255) vL = -255;
    MotorWriting(vL, vR); //Feedback to motors
  }
  else MotorWriting(TpL, TpR);
	
	//偵測node
  if ((l3 && l2 && m && r2 && r3) == 1){
    nodeDetected = true;
  }
}

//functions for actions, needed to be modified.
void Straight(){
  MotorWriting(TpL,TpR);
  delay(2000);
  actionNumber++;
  nodeDetected = false;
}

void RightTurn(){
  double vR = TpR - turn;
  double vL = TpL + turn;
  MotorWriting(vL,vR);
  delay(1000);
      actionNumber++;
    nodeDetected = false;
}

void LeftTurn(){
  MotorWriting(TpL,TpR);
  delay(1000);
  MotorWriting(0,0);
  delay(500);
  double vR = TpR + turn;
  double vL = TpL - turn;
  MotorWriting(vL,vR);
      actionNumber++;
    nodeDetected = false;
}

void UTurn(){
  MotorWriting(TpL,TpR);
  delay(1000);
  MotorWriting(0,0);
  delay(500);
  MotorWriting(-TpL,TpR);
  delay(900);
      actionNumber++;
    nodeDetected = false;
}

//pin definition
void setup() {
  pinMode(PWMA, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT); 
}

void loop() {
  if(nodeDetected){
    int a=0;
    switch(route[actionNumber]){
      case 0:
        Straight();
        break;
      case 1:
        RightTurn();
        break;
      case 2:
        LeftTurn();
        break;
      case 3:
        UTurn();
        break;
      case 4:
        MotorWriting(0,0);
        break;
      }
    MotorWriting(0,0);
    delay(10000);
    Tracking();
  }
  else{
    Tracking();
  }
}