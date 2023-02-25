
int ir0 = 7;
int ir1 = 8;
int ir2 = 9;
int ir3 = 10;
int ir4 = 11;
int ir5 = 12;
int input0 = 0;
int input1 = 0;
int input2 = 0;
int input3 = 0;
int input4 = 0;
int input5 = 0;
int prepos=0;
float Kp = 0.9, Ki = 0.0005, Kd = 1.75 ;
unsigned int line_position = 0;
char path[100] = "";
unsigned char dir;
unsigned char path_length = 0;
int enableA=5;
int enableB=6;
int in1=A3;
int in2=A2;
int in3=A0;
int in4=A1;
int motorspeed;

int sa=0, sb=0;

void setup()
{
  pinMode(ir0,INPUT);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     
  pinMode(ir1,INPUT);
  pinMode(ir2,INPUT);
  pinMode(ir3,INPUT);
  pinMode(ir4,INPUT);
  pinMode(ir5,INPUT);
}

void loop()
{
  pid();
  
}



char slt_turn(unsigned char fnd_l, unsigned char fnd_s, unsigned char fnd_r){
  if(fnd_l)
    return 'l';
  else if(fnd_s)
    return 's';
  else if(fnd_r)
    return 'r';
  else 
    return 'b'; 
  }


void turn(char direct){
  switch(direct){
    case 'l':
    movement(-50,50);
    input1 = digitalRead(ir1);
    input2 = digitalRead(ir2);
    input3 = digitalRead(ir3);
    input4 = digitalRead(ir4);
    input5 = digitalRead(ir5);  
    while(input0 ==0){
      input1 = digitalRead(ir1);
      input2 = digitalRead(ir2);
      input3 = digitalRead(ir3);
      input4 = digitalRead(ir4);
      input5 = digitalRead(ir5);  
      }
    input1 = digitalRead(ir1);
    input2 = digitalRead(ir2);
    input3 = digitalRead(ir3);
    input4 = digitalRead(ir4);
    input5 = digitalRead(ir5); 

    while(input2 == 0 || input3 ==0){
      input1 = digitalRead(ir1);
    input2 = digitalRead(ir2);
    input3 = digitalRead(ir3);
    input4 = digitalRead(ir4);
    input5 = digitalRead(ir5);
      }  

    movement(0,50);
    break;
    
    case 'r':
    movement(50,-50);
    input1 = digitalRead(ir1);
    input2 = digitalRead(ir2);
    input3 = digitalRead(ir3);
    input4 = digitalRead(ir4);
    input5 = digitalRead(ir5);  
    while(input5 ==0){
      input1 = digitalRead(ir1);
      input2 = digitalRead(ir2);
      input3 = digitalRead(ir3);
      input4 = digitalRead(ir4);
      input5 = digitalRead(ir5);  
      }
    input1 = digitalRead(ir1);
    input2 = digitalRead(ir2);
    input3 = digitalRead(ir3);
    input4 = digitalRead(ir4);
    input5 = digitalRead(ir5); 

    while(input2 == 0 || input3 ==0){
      input1 = digitalRead(ir1);
    input2 = digitalRead(ir2);
    input3 = digitalRead(ir3);
    input4 = digitalRead(ir4);
    input5 = digitalRead(ir5);
      }  

    movement(50,0);
    break;

    case 'b':
    movement(100,-100);
    input1 = digitalRead(ir1);
    input2 = digitalRead(ir2);
    input3 = digitalRead(ir3);
    input4 = digitalRead(ir4);
    input5 = digitalRead(ir5);  
    while(input5 ==0){
      input1 = digitalRead(ir1);
      input2 = digitalRead(ir2);
      input3 = digitalRead(ir3);
      input4 = digitalRead(ir4);
      input5 = digitalRead(ir5);  
      }
    input1 = digitalRead(ir1);
    input2 = digitalRead(ir2);
    input3 = digitalRead(ir3);
    input4 = digitalRead(ir4);
    input5 = digitalRead(ir5); 

    while(input2 == 0 || input3 ==0){
      input1 = digitalRead(ir1);
      input2 = digitalRead(ir2);
      input3 = digitalRead(ir3);
      input4 = digitalRead(ir4);
      input5 = digitalRead(ir5);
      }  

    movement(50,0);
    break;

    case 's':
    break;
    
    }
  
  }

void simplify_path()
{

  if (path_length < 3 || path[path_length - 2] != 'b')
    return;

  int total_angle = 0;
  int i;
  for (i = 1; i <= 3; i++)
  {
    switch (path[path_length - i])
    {
      case 'r':
        total_angle += 90;
        break;
      case 'l':
        total_angle += 270;
        break;
      case 'b':
        total_angle += 180;
        break;
    }
  }


  total_angle = total_angle % 360;


  switch (total_angle)
  {
    case 0:
      path[path_length - 3] = 's';
      break;
    case 90:
      path[path_length - 3] = 'r';
      break;
    case 180:
      path[path_length - 3] = 'b';
      break;
    case 270:
      path[path_length - 3] = 'l';
      break;
  }
  path_length -= 2;
}

void maze(){
  while(1){
    pid();
    unsigned char fnd_l = 0;
    unsigned char fnd_r = 0;
    unsigned char fnd_s = 0;
    input0 = digitalRead(ir0);
  input1 = digitalRead(ir1);
  input2 = digitalRead(ir2);
  input3 = digitalRead(ir3);
  input4 = digitalRead(ir4);
  input5 = digitalRead(ir5);  
    if(input0 == 1){
      fnd_l = 1;
      }
    else if(input5 == 1){
      for(int i = 0; i<100; i++){
        input1 = digitalRead(ir1);
        input2 = digitalRead(ir2);
        input3 = digitalRead(ir3);
        input4 = digitalRead(ir4);
        input5 = digitalRead(ir5);  
        if(input0 == 1){
          fnd_l = 1;
          delay(200);
          goto bailout;
          }
        
        }
        fnd_r = 1;
      } 
      if(fnd_l == 1){
        delay(200);
        }
    
  
  
  


bailout:
  input1 = digitalRead(ir1);
  input2 = digitalRead(ir2);
  input3 = digitalRead(ir3);
  input4 = digitalRead(ir4);
  input5 = digitalRead(ir5);  
  if(input1 == 1 || input2 == 1 || input3 == 1 || input4 ==1){
    fnd_s = 1;
    }
input1 = digitalRead(ir1);
  input2 = digitalRead(ir2);
  input3 = digitalRead(ir3);
  input4 = digitalRead(ir4);
  input5 = digitalRead(ir5);  
if(input0 == 1 && input1 == 1 && input2 == 1 && input3 == 1 && input4 == 1 && input5 == 1)
break;

  unsigned char dir = slt_turn(fnd_l, fnd_s, fnd_r);

  turn(dir);
  path[path_length] = dir;
  path_length ++;


  simplify_path();


  }
  while (1)
  {
    
    movement(0,0);
    for (int i = 0; i < 10; i++){
      digitalWrite(13, HIGH);
    }
    delay(200);
       digitalWrite(13, LOW );
        delay(200);
}


    for (int i = 0; i < path_length; i++)
    {

      pid();
      if (path[i] == 's')
      { 
        delay(130);                           //TIME  THE BOT TRAVELS STRAIGHT ON AN INTERSECTION DURING ACTUAL pid
      }
      else if (path[i] == 'r')
      {
        delay(120);                          //TIME  BEFORE TAKING RIGHT TURN DURING ACTUAL  pid
      }
      else {
       
        delay(120);                       //TIME  BEFORE TAKING LEFT TURN DURING ACTUAL pid
      }

      turn(path[i]);
    }


    pid();
}

void pid(){

 //while(1){
  float sum =0, pos,t=0;
  input0 = digitalRead(ir0);
  input1 = digitalRead(ir1);
  input2 = digitalRead(ir2);
  input3 = digitalRead(ir3);
  input4 = digitalRead(ir4);
  input5 = digitalRead(ir5);  
 
  sum=(-300*input0)+(-200*input1)+(-100*input2)+(100*input3)+(200*input4)+(300*input5);
  t=input0+input1+input2+input3+input4+input5;
  pos=(sum/t);
  
  int P=pos;
  int I=pos+I;
  int D=pos-prepos;
  prepos=pos;

  
  
  motorspeed=P*Kp + I*Ki + D*Kd;
  sa=220+motorspeed;
  sb=220-motorspeed;

  if(sa>255){
    sa = 255;
    }
  if(sb>255){
    sb = 255;
    }
  if(sa<-75){
    sa = -75;
  }
  if(sb<-75){
    sb = -75;    
    }  
   
  movement(sa, sb);
    
  
  
  if(input0 == 1 || input5 == 1){
    movement(50, 50);
    return;
    }
  if(input0 == 0 && input1 == 0 && input2 == 0 && input3 == 0 && input4 == 0 && input5 == 0){
    movement(50, 50);
    return;
    }
  
  //} 
}


void movement(int SA, int SB){

  if(SA < 0){
    SA = -SA;
    digitalWrite(in1,LOW);
    digitalWrite(in2,HIGH);
    analogWrite(enableA,SA);
    }
  else{
    digitalWrite(in1,HIGH);
    digitalWrite(in2,LOW);
    analogWrite(enableA,SA); 
    }
  if(SB < 0){
    SB = -SB;
    digitalWrite(in3,LOW);
    digitalWrite(in4,HIGH);
    analogWrite(enableB,SB); 
    }
  else{
    digitalWrite(in3,HIGH);
    digitalWrite(in4,LOW);
    analogWrite(enableB,SB); 
    }
  }
