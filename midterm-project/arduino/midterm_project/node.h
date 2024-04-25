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
double x = 1.5;
double adj_R = 0.48, adj_L = 1;

void car_front(){
    MotorWriting(adj_L*_Tp*x, adj_R*_Tp*x);
    delay(1000/x);
}

void car_back(){
    MotorWriting(adj_L*_Tp*x, -adj_R*_Tp*x);
    delay(1600/x);
}

void car_right(){
    MotorWriting(adj_L*_Tp * x,adj_R*_Tp*x);
    delay(700/x);
    MotorWriting(adj_L*_Tp*x,0);
    delay(1400/x);
}

void car_left(){
    MotorWriting(adj_L*_Tp*x, adj_R*_Tp*x);
    delay(700/x);
    MotorWriting(0, adj_R*_Tp*1.2*x);
    delay(1200/x);
}

void car_start(){
    MotorWriting(_Tp*x, _Tp*x);
    delay(500);
}

void car_end(){
    MotorWriting(0,0);
    delay(1000);
}
