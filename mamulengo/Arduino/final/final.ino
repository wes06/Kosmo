//MAMULENGO - Holofote



#include <Servo.h> 

Servo srv[4];

int aberto[] = {
  175, //
  175, //
  175, //
  175  //


};

int fechado[] = {
  45, //A
  45, //
  45, //
  45  //

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
    nextGate = int(random(0,7));// arredonda para...?
  }

  currGate = nextGate;

  abreTodos();
  
  if(currGate<5){
    fecha(currGate);
    delay(6*1000*random(3,5));
  }
  else{
    abreTodos();
    delay(6*1000*random(5,10));
  }


}


void abreTodos(){
  for(int i=0;i<4;i++){
    srv[i].write(aberto[i]);
  }
  delay(300);
}


void fecha(int i){
  srv[i].write(fechado[i]);
  delay(100);
}

void boot(){
  if(bootar){
    //abre todos os canais
    abreTodos();
    delay(500);
    bootar = false;
  }
}

