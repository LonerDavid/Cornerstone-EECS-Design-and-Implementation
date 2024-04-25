/***************************************************************************/
// File       [final_project.ino]
// Author     [Erik Kuo]
// Synopsis   [Code for managing main process]
// Functions  [setup, loop, Search_Mode, Hault_Mode, SetState]
// Modify     [2020/03/27 Erik Kuo]
/***************************************************************************/

#define DEBUG  // debug flag

// for RFID
#include <MFRC522.h>
#include <SPI.h>

/*===========================define pin & create module object================================*/
// BlueTooth
// BT connect to Serial1 (Hardware Serial)
// Mega               HC05
// Pin  (Function)    Pin
// 18    TX       ->  RX
// 19    RX       <-  TX
// TB6612, 請按照自己車上的接線寫入腳位(左右不一定要跟註解寫的一樣)
// TODO: 請將腳位寫入下方(Done)
#define MotorR_I1 2     // 定義 A1 接腳（右）
#define MotorR_I2 3     // 定義 A2 接腳（右）
#define MotorR_PWMR 11  // 定義 ENA (PWM調速) 接腳
#define MotorL_I3 5     // 定義 B1 接腳（左）
#define MotorL_I4 6     // 定義 B2 接腳（左）
#define MotorL_PWML 12  // 定義 ENB (PWM調速) 接腳
// 循線模組, 請按照自己車上的接線寫入腳位
#define IRpin_LL 40
#define IRpin_L 38
#define IRpin_M 36
#define IRpin_R 34
#define IRpin_RR 32
// RFID, 請按照自己車上的接線寫入腳位
#define RST_PIN 9                 // 讀卡機的重置腳位
#define SS_PIN 53                  // 晶片選擇腳位
MFRC522 mfrc522(SS_PIN, RST_PIN);  // 建立MFRC522物件
/*===========================define pin & create module object===========================*/

/*============setup============*/
void setup() {
    // bluetooth initialization
    Serial1.begin(9600);
    // Serial window
    Serial.begin(9600);
    // RFID initial
    SPI.begin();
    mfrc522.PCD_Init();
    // TB6612 pin
    pinMode(MotorR_I1, OUTPUT);
    pinMode(MotorR_I2, OUTPUT);
    pinMode(MotorL_I3, OUTPUT);
    pinMode(MotorL_I4, OUTPUT);
    pinMode(MotorL_PWML, OUTPUT);
    pinMode(MotorR_PWMR, OUTPUT);
    // tracking pin
    pinMode(IRpin_LL, INPUT);
    pinMode(IRpin_L, INPUT);
    pinMode(IRpin_M, INPUT);
    pinMode(IRpin_R, INPUT);
    pinMode(IRpin_RR, INPUT);
#ifdef DEBUG
    Serial.println("Start!");
#endif
}
/*============setup============*/

/*=====Import header files=====*/
#include "RFID.h"
#include "bluetooth.h"
#include "node.h"
#include "track.h"
/*=====Import header files=====*/

/*===========================initialize variables===========================*/
int l2 = 0, l1 = 0, m0 = 0, r1 = 0, r2 = 0;  // 紅外線模組的讀值(0->white,1->black)
int _Tp = 100;                                // set your own value for motor power
bool state = false;     // set state to false to halt the car, set state to true to activate the car
BT_CMD _cmd = NOTHING;  // enum for bluetooth message, reference in bluetooth.h line 2
/*===========================initialize variables===========================*/

/*===========================declare function prototypes===========================*/
void Search();    // search graph
void SetState();  // switch the state
/*===========================declare function prototypes===========================*/

/*===========================define function===========================*/
void loop() {
    if (!state)
        MotorWriting(0, 0);
    else
        Search();
    SetState();
}

void SetState() {
    // TODO:
    // 1. Get command from bluetooth
    // 2. Change state if need
    _cmd = ask_BT()
    if (_cmd == End){
        state = false;
    }
    else{
        state = true;
    }
}

void Search() {
    // TODO: let your car search graph(maze) according to bluetooth command from computer(python
    // code)
    if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
        byte& idSize = mfrc522.uid.size;
        rfid(idSize);
        byte* uid = rfid(idSize);
        send_byte(uid, idSize); // Send the UID over Bluetooth
    }

    l2 = digitalRead(IRpin_LL);
    l1 = digitalRead(IRpin_L);
    m0 = digitalRead(IRpin_M);
    r1 = digitalRead(IRpin_R);
    r2 = digitalRead(IRpin_RR);

    if (l2+l1+m0+r1+r2 == 5){
        switch (_cmd)
        {
        case Front:
            car_front();
            send_msg('n');
            break;
        case Back:
            car_back();
            send_msg('n');
            break;
        case Right:
            car_right();
            send_msg('n');
            break;
        case Left:
            car_left();
            send_msg('n');
            break;
        case Start:
            car_start();
            send_msg('n');
            break;
        case End: //老實說這一個case永遠不會被呼叫到
            car_end();
            send_msg('n')
            break;
        default:
            tracking(l2, l1, m0, r1, r2);
            break;
        }
    }
    else{
        tracking(l2, l1, m0, r1, r2);
    }
}
/*===========================define function===========================*/
