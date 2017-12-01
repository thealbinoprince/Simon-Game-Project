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
const int gameOverTone = 250;
const int toneTime = 300;


//game variables
const int delayTime = 1000;
const int maxSteps = 20;
int lightSequence[maxSteps];
int difficulty; 
int stepCheck;
int mode = 0;

void setup()
{
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

void loop()
{
  switch(mode) {
  	case 0:
    	setGame();       //sets up for a new game
        break;
    case 1:
        ledSequence(); //plays the LED sequence created in the previous case
        break;
    case 2:
        userInput(); //takes button input and determines whether the correct sequence was pressed
        break; 
    case 3:
        gameOver(); //CREATE GAMEOVER METHOD
        break;
  }
}

//setGame resets everything for a new game
void setGame() {
  difficulty = 0; //the difficulty is what "level" you are on, increases as you go
  stepCheck = 0;
                  
  //creates array of 20 random numbers 1-3
  for(int i = 0; i < maxSteps; i++){
      lightSequence[i] = random(3) + 1;
  }

  mode = 1;  //once the game is ready, mode switches to playing the lights
}

//ledSequence lights LEDs based on the random
//number array created in setGame
void ledSequence() { 
  delay(delayTime);
  
  for(int j = 0; j <= difficulty; j++) {
      setLED(lightSequence[j]);
      playTone(lightSequence[j]);
      delay(delayTime);
      offLEDs();
  }

  mode = 2; //once the sequence has played, mode switches to taking user inupt
}

//userInput does stuff 
void userInput() {
  int buttonPressed = readButtons(); 

  if(buttonPressed > 0) {                             //checks that a button is being pressed
      if(buttonPressed == lightSequence[stepCheck]) { //correct input
          setLED(buttonPressed);
          playTone(buttonPressed);
          delay(delayTime);
          offLEDs();

          if(stepCheck == difficulty) { //correct sequence was input in its entirety
              stepCheck = 0;            //reset the checker and
              difficulty++;             //move onto the next step/level
              mode = 1;
              setLEDs(true,true,true); //all LEDs with no sound indicate correct sequence was entered
              delay(delayTime);
              offLEDs();
          }
          else { //check the next one
              stepCheck++;
          }
          //delay(10);
      }
      else {        //incorrect input
          mode = 3; //move onto gameOver()
      }
  }
  //delay(10);
}

//gameOver flashes the LEDs and plays a tone 3 times before starting a new game
void gameOver() {
  for(int i = 0; i < 3; i++) {
      setLEDs(true, true, true);
      tone(buzzer, gameOverTone, toneTime);
      delay(delayTime);
      offLEDs();
  }
  delay(delayTime);
  mode = 0; //starts a new game
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

//offLEDs uses setLEDs to turn off all the LEDs
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
          break;
      case 4:
          tone(buzzer, gameOverTone, toneTime * 4);
          break;
  }
}
