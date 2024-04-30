/***************************************************************************/
// File			  [bluetooth.h]
// Author		  [Erik Kuo]
// Synopsis		[Code for bluetooth communication]
// Functions  [ask_BT, send_msg, send_byte]
// Modify		  [2020/03/27 Erik Kuo]
/***************************************************************************/

/*if you have no idea how to start*/
/*check out what you have learned from week 2*/

enum BT_CMD {
    NOTHING,
    // TODO: add your own command type here
    Front,
    Back,
    Right,
    Left,
    GoGo,
    StopAction
};

BT_CMD ask_BT() {
    BT_CMD message;
// TODO:
// 1. get cmd from Serial1(bluetooth serial)
// 2. link bluetooth message to your own command type
    char cmd;
    if (Serial1.available()) {
        cmd=Serial1.read();
      //Serial.println(cmd);
        switch(cmd){
            case 'f':
                message = Front;
                break;
            case 'b':
                message = Back;
                break;
            case 'r':
                message = Right;
                break;
            case 'l':
                message = Left;
                break;
            case 's':
                message = GoGo;
                break;
            case 'e':
                message = StopAction;
                break;
            default:
                message = NOTHING;
                break;
        }
#ifdef DEBUG
        Serial.print("cmd : ");
        Serial.println(cmd);
#endif
    }
    return message;
}  // ask_BT

// send msg back through Serial1(bluetooth serial)
// can use send_byte alternatively to send msg back
// (but need to convert to byte type)
void send_msg(const char& msg) {
    // TODO:
    Serial1.write(msg);
    Serial1.write('\n');
}  // send_msg

// send UID back through Serial1(bluetooth serial)
void send_byte(byte* id, byte& idSize) {
    for (byte i = 0; i < idSize; i++) {  // Send UID consequently.
        Serial1.write(id[i]);
    }
    Serial1.write('\n');
#ifdef DEBUG
    Serial.print("Sent id: ");
    for (byte i = 0; i < idSize; i++) {  // Show UID consequently.
        Serial.print(id[i], HEX);
    }
    Serial.println();
#endif
}  // send_byte