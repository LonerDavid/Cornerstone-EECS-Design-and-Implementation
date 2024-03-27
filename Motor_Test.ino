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

//IR sensor pin setting
void Tracking() {
  int l3 = digitalRead(L3);
  int l2 = digitalRead(L2);
  int m = digitalRead(M);
  int r2 = digitalRead(R2);
  int r3 = digitalRead(R3);
  int w2 = 1;
  int w3 = 2;
  int Kp = 48;
  int TpL = 100;
  int TpR = 46;
  
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
}

void setup() {
  pinMode(PWMA, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT); 
  //腳位定義
}

void loop() {
  Tracking();
}
