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
double x = 1.5;
double adj_R = 0.5, adj_L = 1;

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
    MotorWriting(adj_L*_Tp * x,adj_R*_Tp * x);
    delay(1000/x);
}

void car_back(){
    MotorWriting(adj_L*_Tp*x, -adj_R*_Tp*x);
    delay(1800/x);
}

void car_right(){
    MotorWriting(adj_L*_Tp * x,adj_R*_Tp*x);
    delay(700/x);
    MotorWriting(adj_L*_Tp*x,0);
    delay(1400/x);
}

void car_left(){
    MotorWriting(adj_L*_Tp*x,adj_R*_Tp*x);
    delay(700/x);
    MotorWriting(0,adj_R*_Tp*1.2*x);
    delay(1200/x);
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
