int stopHome = A3;//corrigidos
int stopMeio = A2;

int motPapel = 6;

int releVai = 12;
int releVolta = 11;


int ledVerd = 5;
int ledVerm = 4;

int botao = A1;

int qrd = A0;

int etapa = 99;

long debounceDelay = 50;

int buttonStateMeio = LOW;
int lastButtonStateMeio = LOW;

long lastDebounceTimeMeio = 0; 

int buttonStateHome = LOW;
int lastButtonStateHome = LOW;

long lastDebounceTimeHome = 0; 

int buttonStateBot = LOW;
int lastButtonStateBot = LOW;

long lastDebounceTimeBot = 0; 

boolean direcao =  HIGH;

void setup(){
  pinMode(stopHome, INPUT);
  pinMode(stopMeio, INPUT);
  pinMode(botao, INPUT);

  pinMode(motPapel, OUTPUT);
  pinMode(releVai, OUTPUT);
  pinMode(releVolta, OUTPUT);
  pinMode(ledVerd, OUTPUT);
  pinMode(ledVerm, OUTPUT);
}

void loopi(){

  motorVai();

  delay(1000);
  motorVolta();


  delay(1000);
  motorPara();
  delay(1000);
}

void loop(){
  //Serial.println("alouu");
  debounceHome();
  debounceMeio();
  debounceBot();

  if(etapa==99){
    corte();
  }

  if(etapa == 0 && buttonStateBot == LOW){
    etapa =1;
    direcao=HIGH;
    digitalWrite(ledVerm,HIGH);
    digitalWrite(ledVerd,LOW);
  }

  if(etapa==1){
    digitalWrite(motPapel, HIGH);
    delay(100);
    etapa=2;  
  }

  if(analogRead(qrd)<600 && etapa == 2){
    digitalWrite(motPapel, LOW);
    etapa=3;

  }
  
  if(etapa == 3){
    corte();
 }

  if(etapa ==4){

    digitalWrite(ledVerm,HIGH);
    digitalWrite(ledVerd,LOW);
    delay(10000);
    etapa = 0;  
    digitalWrite(ledVerm,LOW);
    digitalWrite(ledVerd,HIGH);
  }

}

void corte(){
if(direcao){
  motorVai();
}
  //Serial.println('4');

  //Serial.println(buttonStateMeio && direcao);
  //Serial.println(direcao);
  if(buttonStateMeio && direcao){
    motorVolta();
    direcao = LOW;
  }

  if(buttonStateHome && direcao ==LOW){
   // Serial.println('2');
    motorPara();
    direcao = HIGH;
    if(etapa==99){

      //Serial.println('1');
      digitalWrite(ledVerm,LOW);
      digitalWrite(ledVerd,HIGH);
      etapa = 0; 
    }
    if(etapa == 3){
      etapa =4;
    }
  }

}

void motorVai(){
  digitalWrite(motPapel, LOW);
  digitalWrite(releVai, LOW);
  digitalWrite(releVolta, HIGH);
}

void motorVolta(){
  digitalWrite(motPapel, LOW);
  digitalWrite(releVai, HIGH);
  digitalWrite(releVolta, LOW);
}

void motorPara(){
  digitalWrite(releVai, LOW);
  digitalWrite(releVolta, LOW);
}

