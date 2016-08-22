//MAMULENGO - Holofote



#include <Servo.h> 

Servo srv[4];

int aberto[] = {
  170, //
  170, //
  170, //
  170  //


};

int fechado[] = {
  50, //Aok
  50, //ok
  45, //ok
  55  //ok

};

int nextGate;
int currGate;

boolean bootar = true;

void setup() 
{ 
  srv[0].attach(A0);
  srv[1].attach(A1);
  srv[2].attach(A2);
  srv[3].attach(A3);
} 


void loop(){
  boot();

  while(nextGate == currGate){
    nextGate = int(random(0,7));
    //se for 0, 1, 2, ou 3 = cor, se for 4, 5, 6 ou 7 = natural
    //para mais ou menos natural, aumentar ou diminuir o "7"
  }

  currGate = nextGate;

  abreTodos();
  
  if(currGate<5){
    fecha(currGate);
    delay(6*1000*random(3,5));//tempo de cor
  }
  else{
    abreTodos();
    delay(6*1000*random(5,10));//tempo natural
  }


}


void abreTodos(){
  //abre todos os canais
  for(int i=0;i<4;i++){
    srv[i].write(aberto[i]);
  }
  delay(300);
}


void fecha(int i){
  //fecha 1 canal
  srv[i].write(fechado[i]);
  delay(100);
}

void boot(){
  if(bootar){
    abreTodos();
    delay(500);
    bootar = false;
  }
}

