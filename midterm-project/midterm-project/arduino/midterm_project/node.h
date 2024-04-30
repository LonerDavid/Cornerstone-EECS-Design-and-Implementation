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
#include "track.h"
// TODO: add some function to control your car when encounter a node
// here are something you can try: left_turn, right_turn... etc.
double x = 2;
double adj_R = 0.49, adj_L = 1;

void car_front(){
    MotorWriting(adj_L*_Tp*x, adj_R*_Tp*x);
    delay(1000/x);
}

void car_back(){
    MotorWriting(adj_L*_Tp*x, -adj_R*_Tp*x);
    delay(1400/x);
}

void car_right(){
    MotorWriting(adj_L*_Tp * x,adj_R*_Tp*x);
    delay(600/x);
    MotorWriting(adj_L*_Tp*x,0);
    delay(1300/x);
}

void car_left(){
    MotorWriting(adj_L*_Tp*x, adj_R*_Tp*x);
    delay(700/x);
    MotorWriting(0, adj_R*_Tp*1.2*x);
    delay(1100/x);
}

void car_start(){
    MotorWriting(adj_L*_Tp*x, adj_R*_Tp*x);
    delay(800);
}

void car_end(){
    MotorWriting(0,0);
    delay(1000);
}