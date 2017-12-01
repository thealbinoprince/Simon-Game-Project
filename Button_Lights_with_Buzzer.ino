//LEDs
const int blueLED = 12;
const int yellowLED = 9;
const int redLED = 7;

//buttons
const int blueButton = 11;
const int yellowButton = 8;
const int redButton = 6;

//buzzer
const int buzzer = 2;
const int blueTone = 1000;
const int yellowTone = 750;
const int redTone = 500;
const int toneTime = 300;

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
  setLED(readButtons());
  playTone(readButtons());      
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
