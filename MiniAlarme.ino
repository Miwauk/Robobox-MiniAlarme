int ledPin = 5;           //output Pin from LED
int inputPin = 2;         //input pin from movement detector
int pinSpeaker = 6;       //output pin from Buzzer
//int pirState = LOW;
int val = 0;
int counter = 0;
int previousLedState = LOW;   //lors du premier lancement la LED est forcément éteinte
int currentLedState;
int playing = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(inputPin, INPUT);
  pinMode(pinSpeaker, OUTPUT);

}

void loop() {
  val = digitalRead(inputPin);
  currentLedState = digitalRead(ledPin);

  if (val == HIGH){ 
    digitalWrite(ledPin, HIGH);       // mouvement détecté => allumage de la LED
    
    if (previousLedState != currentLedState){    // si La LED change d'état
        if (currentLedState == HIGH){            // si la led passe de LOW à HIGH <=> mouvement détecté
          counter++;                                //(passer la main devant le détecteur équivaut à un statut HIGH sur plusieurs loop ce qui augmenterait plus le conteur que ce que l'on souhaite)
                                                    //(permet de d'éviter de mettre un delay pile égal au "temps de rechargement" du détecteur)
        }
        previousLedState = currentLedState;     //actualisation de l'état de la LED
    }
    
    if (counter == 3 || playing == 1){        //si 3 mouvements détectés ou si le son a été joué la loop précédente (et que donc le capteur de mouvement est toujours actif), on joue le son
      playSound(150, 200);
      playSound(150, 300);
      playSound(150, 100);
      counter = 0;
      playing = 1;
    }
  }

  else{
    digitalWrite(ledPin, LOW);
    playing = 0;  //ce n'est que lorsque le détecteur de mouvement redevient inactif que l'on arrête de jouer le son (cela permet de jouer le son sur plusieurs loop), et que l'on attent de redétecter 3 mouvements
  }

  delay(300);
}

/*
 * duration in miliseconds
 * frequence in Hertz
 */
void playSound(long duration, int frequence){
  duration *= 1000;
  int period = (1.0/frequence)*100000;
  long time_played = 0;

  while (time_played < duration){
    digitalWrite(pinSpeaker, HIGH);
    delayMicroseconds(period/2);
    digitalWrite(pinSpeaker, LOW);
    delayMicroseconds(period/2);

    time_played += period;
  }
}

