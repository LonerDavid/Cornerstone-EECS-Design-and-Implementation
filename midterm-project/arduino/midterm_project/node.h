/***************************************************************************/
// File			  [node.h]
// Author		  [Erik Kuo, Joshua Lin]
// Synopsis		[Code for managing car movement when encounter a node]
// Functions  [/* add on your own! */]
// Modify		  [2020/03/027 Erik Kuo]
/***************************************************************************/

/*===========================import variable===========================*/
int extern _Tp;
/*===========================import variable===========================*/

// TODO: add some function to control your car when encounter a node
// here are something you can try: left_turn, right_turn... etc.
double turn = 30;
bool in_node = false;

void action(int cmd){
    switch (cmd)
    {
    case 0:
        break;
    case 1:  //Front
        car_front();
        break;
    case 2:  //Back
        car_back();
        break;
    case 3:  //Right
        car_right();
        break;
    case 4:  //Left
        car_left();
        break;
    case 5:  //Start
        car_start();
        break;
    case 6:  //End
        car_end();
        break;
    default:
        break;
    }
}

void car_front(){
    MotorWriting(_Tp,_Tp);
    delay(2000);
}

void car_back(){
    MotorWriting(_Tp,-_Tp);
    delay(2500);
    MotorWriting(_Tp, _Tp);
    delay(800);
    in_node = car_in_node();
    while (in_node){
        MotorWriting(_Tp, -_Tp);
        delay(10);
        in_node = car_in_node();
    }
    MotorWriting(0, 0);
    delay(200);
}

void car_right(){
    double vR = _Tp - turn;
    double vL = _Tp + turn;
    MotorWriting(vL,vR);
    delay(800);
    in_node = car_in_node();
    while(in_node){
        MotorWriting(vL,vR);  
        delay(10);
        in_node = car_in_node();
    }
    MotorWriting(0, 0);
    delay(200);
}

void car_left(){
    double vR = _Tp + turn;
    double vL = _Tp - turn;
    MotorWriting(vL,vR);
    delay(800);
    in_node = car_in_node();
    while(in_node){
        MotorWriting(vL,vR);  
        delay(10);
        in_node = car_in_node();
    }
    MotorWriting(0, 0);
    delay(200);
}

void car_start(){
    MotorWriting(_Tp,_Tp);
    delay(1000);
}

void car_end(){
    MotorWriting(0,0);
    delay(1000);
}

bool car_in_node(){
    int ll = digitalRead(IRpin_LL);
    int l = digitalRead(IRpin_L);
    int m = digitalRead(IRpin_M);
    int r = digitalRead(IRpin_R);
    int rr = digitalRead(IRpin_RR);

    if (ll+l+m+r+rr == 5) {
        return true;
        }
    else {
        return false;
        }
}
