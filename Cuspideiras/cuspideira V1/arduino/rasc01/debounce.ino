void debounceBot() {

  int readingBot = digitalRead(botao);

  if (readingBot != lastButtonStateBot) {
    lastDebounceTimeBot = millis();
  } 

  if ((millis() - lastDebounceTimeBot) > debounceDelay) {
    buttonStateBot = readingBot;
  }

  lastButtonStateBot = readingBot;

}

void debounceHome() {
  int readingHome = digitalRead(stopHome);

  if (readingHome != lastButtonStateHome) {
    lastDebounceTimeHome = millis();
  } 

  if ((millis() - lastDebounceTimeHome) > debounceDelay) {
    buttonStateHome = readingHome;
  }

  lastButtonStateHome = readingHome;

}

void debounceMeio() {

  int readingMeio = digitalRead(stopMeio);

  if (readingMeio != lastButtonStateMeio) {
    lastDebounceTimeMeio = millis();
  } 

  if ((millis() - lastDebounceTimeMeio) > debounceDelay) {
    buttonStateMeio = readingMeio;
  }

  lastButtonStateMeio = readingMeio;

}

