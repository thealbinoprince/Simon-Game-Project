//LEDs
const int blueLED = 2;
const int yellowLED = 5;
const int redLED = 8;


//buttons
const int blueButton = 3;
const int yellowButton = 6;
const int redButton = 9;

//buzzer
const int buzzer = 11;
const int blueTone = 1000;
const int yellowTone = 750;
const int redTone = 500;
const int toneTime = 300;

//game variables
const int delayTime = 1000;
const int maxSteps = 20;
int lightSequence[maxSteps];
int difficulty; 
int stepCounter;
int mode = 0;

void setup() {
  //button input
  pinMode(redButton, INPUT);
  pinMode(yellowButton, INPUT);
  pinMode(blueButton, INPUT);
  //LED output
  pinMode(redLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
  //buzzer output
  pinMode(buzzer, OUTPUT);
} 

void loop() {
  switch(mode) {
      case 0:
          setGame();     //sets up for a new game
          break;
      case 1:
          ledSequence(); //plays the LED sequence created in the previous case
          break;
      case 2:
          buttonPress(); //allows the buttons to be pressed to lights LEDs and set off the buzzer
          break;         //there is no escaping this part (yet) without doing the old turn it off and on again
  }
}

//test method, used for Step #4
void buttonPress() {
  setLED(readButtons());
  playTone(readButtons());      
}

//sets everything up for a new game
void setGame() {
  difficulty = 0; //in order to test  random LEDs before finishing the game, change the difficulty here
  stepCounter = 0;

  //creates array of random numbers 1-3
  for(int i = 0; i < maxSteps; i++)
      lightSequence[i] = random(3) + 1;

  mode = 1;
}

//ledSequence lights LEDs based on the random
//number array created in setGame
void ledSequence() { 
  for(int j = 0; j <= difficulty; j++) {
      setLED(lightSequence[j]);
      playTone(lightSequence[j]);
      delay(delayTime);
      offLEDs();
  }

  mode = 2;
}

//readButtons returns a specific number 1-3 for
//each button pressed, and 0 otherwise
int readButtons() {
  if(digitalRead(redButton) == LOW)
      return 1;
  else if(digitalRead(yellowButton) == LOW)
      return 2;
  else if(digitalRead(blueButton) == LOW)
      return 3;
  else
      return 0;
}

//setLED takes in an int and calls setLEDs based on the int
void setLED(int num) {
  switch(num) {
      case 0:
          setLEDs(false, false, false);
          break;
      case 1:
          setLEDs(true, false, false);
          break;
      case 2:
          setLEDs(false, true, false);
          break;
      case 3:
          setLEDs(false, false, true);
          break;
  }
}

//setLEDs takes boolean inputs and uses them to 
//determine which LEDs should be on/off
void setLEDs(boolean red, boolean yellow, boolean blue) {
  if (red) 
      digitalWrite(redLED, HIGH);
  else 
      digitalWrite(redLED, LOW);
  if (yellow) 
      digitalWrite(yellowLED, HIGH);
  else 
      digitalWrite(yellowLED, LOW);
  if (blue) 
      digitalWrite(blueLED, HIGH);
  else 
      digitalWrite(blueLED, LOW);
}

void offLEDs() {
  setLEDs(false, false, false);
}

//playTone takes takes int input and makes 
//a tone or is silent based on the int
void playTone(int num) {
  switch(num) {
      case 0:
          noTone(buzzer);
          break;
      case 1:
          tone(buzzer, redTone, toneTime);
          break;
      case 2:
          tone(buzzer, yellowTone, toneTime);
          break;
      case 3:
          tone(buzzer, blueTone, toneTime);
  }
}


