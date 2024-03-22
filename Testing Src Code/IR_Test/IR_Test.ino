#define analogPin 32 //定義 analogPin 來自於 32
//這邊先測試單一個IR元件，之後可以再一起定義全部的元件

void setup() {
  pinMode(analogPin , INPUT); // 目前預設該接腳作為輸入
  Serial.begin(9600);
}

void loop(){
  int value = analogRead(analogPin);

  Serial.println(value);
  delay (500);
}
