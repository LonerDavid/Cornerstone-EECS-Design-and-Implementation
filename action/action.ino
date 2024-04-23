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

//下一步的行動
enum action{
  straight, right, left, uTurn, stop
};

double _Tp = 100;
double adj_R = 0.5, adj_L = 1;  // 馬達轉速修正係數。MotorWriting(_Tp,_Tp)如果歪掉就要用參數修正。

//利用array儲存action
int actionNumber = 0;
int route[6] = {1,3,0,3,2,4};

//判斷是否偵測到node
bool NodeDetected = false;
bool halt = false;

//馬達控制
void MotorWriting(double vL, double vR) {
    // TODO: use TB6612 to control motor voltage & direction
    if(vR >= 255) vR = 255;
    if(vL >= 255) vL = 255;
    if(vR <= -255) vR = -255;
    if(vL <= -255) vL = -255;

    if(vR < 0){
        digitalWrite(BIN1, LOW);
        digitalWrite(BIN2, HIGH);
        vR = -vR; 
    }
    else{
        digitalWrite(BIN1, HIGH);
        digitalWrite(BIN2, LOW);   
    }

    if(vL < 0){
        digitalWrite(AIN1, LOW);
        digitalWrite(AIN2, HIGH);
        vL = -vL; 
    }
    else if(vL >= 0){
        digitalWrite(AIN1, HIGH);
        digitalWrite(AIN2, LOW);
    }

    analogWrite(PWMA, vL);
    analogWrite(PWMB, vR);
}  // MotorWriting


//循跡控制
void Tracking() {
	//IR sensor pin setting
  int l3 = digitalRead(L3);
  int l2 = digitalRead(L2);
  int m = digitalRead(M);
  int r2 = digitalRead(R2);
  int r3 = digitalRead(R3);
  int w2 = 1;
  int w3 = 4;
  double _Kp = 45;  // p term parameter
  double _Kd = 25;  // d term parameter (optional)

  
  if((l3 + l2 + m + r2 + r3) != 0){
    double error = (l3*(-w3) + l2*(-w2) + r2*w2 + r3*w3)/(l3 + l2 + m + r2 + r3);
    static double lastError;
    double dError = error - lastError;
    double vR, vL;  // 馬達左右轉速原始值(從PID control 計算出來)。Between -255 to 255.


    double powerCorrection = _Kp * error + _Kd*dError;
    vR = _Tp - powerCorrection;
    vL = _Tp + powerCorrection;
    lastError = error;
    // end TODO
    MotorWriting(adj_L * vL, adj_R * vR);
  }
  else MotorWriting(adj_L * _Tp, adj_R * _Tp);
	
	//偵測node
  if ((l3 && l2 && m && r2 && r3) == 1){
    NodeDetected = true;
  }
}

//functions for actions, needed to be modified.
void Straight(){
  MotorWriting(adj_L*_Tp,adj_R*_Tp);
  delay(1000);
}

void RightTurn(){
  MotorWriting(adj_L*_Tp,adj_R*_Tp);
  delay(700);
  MotorWriting(adj_L*_Tp,0);
  delay(1400);
}

void LeftTurn(){
  MotorWriting(adj_L*_Tp,adj_R*_Tp);
  delay(700);
  MotorWriting(0,adj_R*_Tp*1.2);
  delay(1200);
}

void UTurn(){
  MotorWriting(adj_L*_Tp, -adj_R*_Tp);
  delay(1800);
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
  if(!halt){
    if(NodeDetected){
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
        halt = true;
        break;   
      default:
        MotorWriting(adj_L*_Tp,adj_R*_Tp);
        break;  
      }
    
    actionNumber++;
    //delay(1500);

    NodeDetected = false;
  }
  else{
    Tracking();
  }
  }
  else {
    MotorWriting(0,0);
  }
}