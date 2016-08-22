

// falta

//       DEFINIR PINOUT (A0, A1, A2....)


//       CALIBRAR VERTICAIS (angulos)



//       testar!






#include <Servo.h> 

Servo srv[4];

int aberto[] = {
  45, //A
  45, //
  45, //
  45  //
};
  
int fechado[] = {
  120, //
  120, //
  120, //
  120  //
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
    nextGate = int(random(0,4));// arredonda para...?
  }

  currGate = nextGate;

  abreTodos();

  fecha(currGate);
  
  delay(random(1,3)*1000*60);
}


void abreTodos(){
  for(int i=0;i<4;i++){
    srv[i].write(aberto[i]);
  }
  delay(500);
}


void fecha(int i){
    srv[i].write(fechado[i]);
    delay(100);
}

void boot(){
  if(bootar){
  //abre todos os canais
  abreTodos();
  bootar = false;
  }
}
