char val;  // 儲存接收資料的變數

void setup() {
  Serial.begin(9600);   // 與電腦序列埠連線
  Serial.println("BT begin!");

  // 設定藍牙模組的連線速率
  // 如果是HC-05要進AT mode，請改成38400
  // 一般模式都是9600!!
  // 18TX 19RX
  Serial1.begin(9600);
}

void loop() {
  // 若收到「序列埠監控視窗」的資料，則送到藍牙模組
  if (Serial.available()) {
    val = Serial.read();
    Serial1.print(val);
  }

  // 若收到藍牙模組的資料，則送到「序列埠監控視窗」
  if (Serial1.available()) {
    val = Serial1.read();
    Serial.print(val);
  }
}