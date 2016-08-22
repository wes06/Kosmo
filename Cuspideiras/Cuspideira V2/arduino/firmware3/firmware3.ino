const int qrdCorte = A0;
const int qrdPapel = A1;

const int botao = 10;

//const int ledVerm =4; 
const int led =  9;

//Stepper Corte
const int pinCorteEN = 12;
const int pinCorteDIR = 5;
const int pinCorteSTEP = 6;

//Stepper Papel
const int pinPapelEN = 11;
const int pinPapelDIR = 7;
const int pinPapelSTEP =8;

const int minPulseMicros = 2400; 
int stepPulseMicros = 2400; 
const int autoStepMicros = 1600;

boolean direcao =  HIGH;

boolean start = true;

int etapa = 99;

boolean corte;

long int pulseMicros;

boolean isHigh;

void setup(){
  pinMode(qrdCorte, INPUT);
  pinMode(qrdPapel, INPUT);
  pinMode(botao, INPUT_PULLUP);
  //pinMode(ledVerm, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(pinCorteEN, OUTPUT);
  pinMode(pinCorteDIR, OUTPUT);
  pinMode(pinCorteSTEP, OUTPUT);
  pinMode(pinPapelEN, OUTPUT);
  pinMode(pinPapelDIR, OUTPUT);
  pinMode(pinPapelSTEP, OUTPUT);


    analogWrite(led, 255);

 

  digitalWrite(pinPapelEN, HIGH);
  digitalWrite(pinCorteEN, HIGH);
  digitalWrite(pinPapelDIR, HIGH);
  digitalWrite(pinCorteDIR, HIGH); //era HIGH


    //Serial.begin(300);
}

void loop(){

  //delay(10);


  //Serial.println(analogRead(qrdPapel));

  if(etapa==99){
    cortar();
  }

  //se esta esperando e buttonPressed, anda
  if(etapa == 0 && digitalRead(botao) == LOW){
    etapa =1;

    direcao=HIGH;
    digitalWrite(pinCorteDIR, direcao);
    analogWrite(led, 255);
    //digitalWrite(ledVerm,HIGH);
    //digitalWrite(ledVerd,LOW);
  }


  if(etapa==1){
    papelRun(true);
    for(int i=0;i<50;i++){
      digitalWrite(pinPapelSTEP, LOW);
      delayMicroseconds(autoStepMicros);
      digitalWrite(pinPapelSTEP, HIGH);
      delayMicroseconds(autoStepMicros);
    }
    
    etapa=2;  
  }

  if(analogRead(qrdPapel)>500 && etapa == 2){
    //da alguns passos depois de ver a tarja preta
    papelRun(false);
    etapa=3;
  }

  if(etapa == 3){
    cortar();
  }

  if(etapa ==4){// contagem do intervalo

   // digitalWrite(ledVerm,HIGH);
    //digitalWrite(ledVerd,LOW);
    delay(100);
    etapa = 0;  
      for(int i = 0;i<6;i++){
        analogWrite(led,255);
        delay(300);
        analogWrite(led,127);
        delay(300);
      }    
    
    //digitalWrite(ledVerm,LOW);
    //digitalWrite(ledVerd,HIGH);
  }
  runAll();
}

void cortar(){

  if(direcao == HIGH && start == true){ //se a direcao eh HIGH, aciona o corte
    //Serial.println("ble");
    corteRun(true, direcao); 

    for(int i=0;i<50;i++){
      digitalWrite(pinCorteSTEP, LOW);
      delayMicroseconds(autoStepMicros);
      digitalWrite(pinCorteSTEP, HIGH);
      delayMicroseconds(autoStepMicros);
    }
    start = false;
  }

  if(analogRead(qrdCorte) < 300 && direcao == HIGH){ // se chegar no fim e estiver com direcao = HIGH
    direcao = LOW; //muda de direcao
    corteRun(true, direcao); 

    //da alguns passos para desativar o QRD
    for(int i=0;i<50;i++){
      digitalWrite(pinCorteSTEP, LOW);
      delayMicroseconds(autoStepMicros);
      digitalWrite(pinCorteSTEP, HIGH);
      delayMicroseconds(autoStepMicros);
    }

    //e continua descendo
  }

  //ate ativar o QRD de novo
  if(analogRead(qrdCorte) <300 && direcao == LOW){
    direcao = HIGH;
    corteRun(false, direcao); //para de andar
    if(etapa==99){//se esta vindo do boot
      //acende o LED do botao
      analogWrite(led, 127);
     // digitalWrite(ledVerm,LOW);
      //digitalWrite(ledVerd,HIGH);
      etapa = 0;//vai para standby
    }
    if(etapa == 3){//se esta vindo de funcionamento normal
      etapa =4;//inicia contagem do intervalo
    }
    start = true;

  }
}



void papelRun(boolean action){
  corte = false;
  digitalWrite(pinCorteEN, HIGH);
  digitalWrite(pinPapelEN, !action);
}

void corteRun(boolean action, boolean _direcao){
  corte = true;
  digitalWrite(pinPapelEN, HIGH);
  digitalWrite(pinCorteEN, !action);
  digitalWrite(pinCorteDIR, _direcao);
}

void runAll(){
  if(corte == false){
    stepPulseMicros = minPulseMicros*1.3;
  }
  else if (corte == true){
    stepPulseMicros = minPulseMicros;
  }
  if(micros() - pulseMicros > stepPulseMicros)
  {
    // digitalWrite(corte ?  pinCorteSTEP : pinPapelSTEP, isHigh ? LOW : HIGH); //condition ? result1 (true) : result2 
    if(corte){
      digitalWrite(pinCorteSTEP, isHigh ? LOW : HIGH);//condition ? result1 (true) : result2 
    } 
    else{
      digitalWrite(pinPapelSTEP, isHigh ? LOW : HIGH);
    }
    isHigh = !isHigh;

    if(isHigh)
    {
      pulseMicros = micros();
    }
  }
}





