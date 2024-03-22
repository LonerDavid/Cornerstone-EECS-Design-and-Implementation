//腳位設定
int PWMA = 11;
int PWMB = 12;
int AIN1 = 2;
int AIN2 = 3;
int BIN1 = 5;
int BIN2 = 6;

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
  digitalWrite(STBY, HIGH);

  digitalWrite(PWMA, HIGH);
  digitalWrite(PWMB, HIGH);

  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
  delay(5000);

  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH);
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, HIGH);
  delay(5000);

  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, LOW);
  delay(5000);

}
