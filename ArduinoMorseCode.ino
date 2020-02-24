/*
  Arduino Morse Code

  When the push button is pressed, the LED lights up as an indicator. The Morse Code conversion algorithm is composed of 4 timed components. A simple button press (less than 150 ms) means a `dot` is generated, while a longer press (less than 400 ms) produces a `dash`. For differentiating between each letter, a time-gap between each sequence (of `dots` and `dashes`) is calculated. If this time is less than 650 ms, then a letter is generated (only if the combination/sequence is valid). For any more time-gap, the program assumes that the word has been formed and goes to print on the next line.

  - `dash` is approximately 3 times as long as the `dot`
  -  time-gap between letters is approximately 9 times as long as the `dot`
  -  time-gap between words is approximately 13 times as long as the `dot`


  
  The circuit:
  - LED attached from pin 7 to ground
  - 10 kilohm resistor attached from pin 7 to ground
  - pushbutton attached from pin 2 to +5V
  - 10 kilohm resistor attached from pin 2 to ground

  created 24 Feb 2020
  by Hritik Aggarwal

  This code is in the public domain.
*/

const int ledPin =  7;
const int buttonPin =  2;

const unsigned long dotInterval = 50;
const unsigned long dashInterval = 150;
const unsigned long letterInterval = 425;
const unsigned long wordInterval = 650;

unsigned long currentMillis;
unsigned long prevMillis;

int millisFlag;
int letterFlag;
int wordFlag;
int wordBreak;

String wordFull;

void setup() {
  Serial.begin(9600);
  
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  
  millisFlag = 0;
  prevMillis = 0;
  
  wordFull = "";
  wordBreak = 0;
}

void loop() {
  
  int buttonState = digitalRead(buttonPin);
  
  if (buttonState == HIGH) {
    digitalWrite(ledPin, HIGH);
    if (millisFlag == 0) {
      prevMillis = millis();
      millisFlag = 1;
    }
  } else {
    currentMillis = millis();
    digitalWrite(ledPin, LOW);
    
    long diff = currentMillis - prevMillis;
    
    if (wordFlag == 1 && diff >= wordInterval) {
      Serial.println();
      
      // self
      wordFlag = 0;
      wordFull = "";
      
      // lower ones
      letterFlag = 0;
      wordBreak = 0;
      prevMillis = millis();
      millisFlag = 0;
    }
    
    if (letterFlag == 1 && (wordBreak == 4 || diff >= letterInterval)) {
      // Serial.println("word is = ");
      Serial.print(getLetter(wordFull));
      wordFull = "";
      
      // upper ones
      wordFlag = 1;
      
      //self
      letterFlag = 0;
      wordBreak = 0;
      
      // lower ones
      prevMillis = millis();
      millisFlag = 0;
    }
    
    if (millisFlag == 1) {
      if (diff >= dashInterval) {
        // Serial.println("dash");
        wordFull += "dash";
        wordBreak++;
      } else if (diff >= dotInterval) {
        // Serial.println("dot");
        wordFull += "dot";
        wordBreak++;
      }
      
      // upper ones
      letterFlag = 1;
      
      // self
      prevMillis = millis();
      millisFlag = 0;
    }
  }
}

char getLetter(String checkWord) {
  if (checkWord == "dot") {
    return 'E';
  } else if (checkWord == "dotdot") {
    return 'I';
  } else if (checkWord == "dash") {
    return 'T';
  } else if (checkWord == "dotdotdot") {
    return 'S';
  } else if (checkWord == "dotdash") {
    return 'A';
  } else if (checkWord == "dashdot") {
    return 'N';
  } else if (checkWord == "dotdotdotdot") {
    return 'H';
  } else if (checkWord == "dotdotdash") {
    return 'U';
  } else if (checkWord == "dotdashdot") {
    return 'R';
  } else if (checkWord == "dashdotdot") {
    return 'D';
  } else if (checkWord == "dashdash") {
    return 'M';
  } else if (checkWord == "dotdashdash") {
    return 'W';
  } else if (checkWord == "dashdashdot") {
    return 'G';
  } else if (checkWord == "dotdotdotdash") {
    return 'V';
  } else if (checkWord == "dotdashdotdot") {
    return 'L';
  } else if (checkWord == "dotdotdashdot") {
    return 'F';
  } else if (checkWord == "dashdotdotdot") {
    return 'B';
  } else if (checkWord == "dashdotdash") {
    return 'K';
  } else if (checkWord == "dashdashdash") {
    return 'O';
  } else if (checkWord == "dotdashdashdot") {
    return 'P';
  } else if (checkWord == "dashdotdotdash") {
    return 'X';
  } else if (checkWord == "dashdotdashdot") {
    return 'C';
  } else if (checkWord == "dashdashdotdot") {
    return 'Z';
  } else if (checkWord == "dotdashdashdash") {
    return 'J';
  } else if (checkWord == "dashdotdashdash") {
    return 'Y';
  } else if (checkWord == "dashdashdotdash") {
    return 'Q';
  } else {
    return '_';
  }
}