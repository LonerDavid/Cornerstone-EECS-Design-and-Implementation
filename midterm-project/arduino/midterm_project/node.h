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

}

void car_back(){

}

void car_right(){

}

void car_left(){

}

void car_start(){

}

void car_end(){
    
}
