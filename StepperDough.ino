/* DoughSpiceCode
   v1.0
   last update: feb 24th, 2016
*/

#include <Stepper.h>
#include <LiquidCrystal.h>

// twelve servo objects can be created on most boards
LiquidCrystal lcd(12, 11, 10, 9, 8, 7);
int stepsPerRevolution = 200;
Stepper myStepper(stepsPerRevolution, 2, 4, 3, 5);


int pos = 0; // variable to store the servo position
int value = 10;
int doughAmount = 3;
int whiteAmount = 3;
int tomatoAmount = 3;
int lastState1 = 0;
int lastState2 = 0;


const int buttonPin1 = 13;// the number of the pushbutton pin
const int buttonPin2 = 6;    // the number of the LED pin
int buttonState1 = 0;// variable for reading the pushbutton status
int buttonState2 = 0;
int buttonPosition = 0;


void setup() {

  
  
  pinMode(buttonPin1, INPUT); // initialize the pushbutton pin as an input
  pinMode(buttonPin2, INPUT);
  buttonPosition = 0;
  
  
  lcd.begin(16, 2); // set up the LCD's number of columns and rows:
  lcd.clear();
  lcd.print("1.Dough 3.White");
  lcd.setCursor(0,1);
  lcd.print("2.Tomato");
  lcd.setCursor(7,0);
  
  

}

void loop() {
  
  buttonState1 = digitalRead(buttonPin1); // read the state of the pushbutton value:
  buttonState2 = digitalRead(buttonPin2);
  dough();

  
}


void tomato() {

delay(500);
buttonState2 = digitalRead(buttonPin2);

do 
{
  
  lcd.setCursor(8,1);
  lcd.blink();

  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2);
 
  if(buttonState1 == HIGH && buttonPosition == 1) {
    amountOfBags('T');
  }


  if(buttonState2 == HIGH && buttonPosition == 1) {
    buttonPosition = 2;
    white();
  }
}
while(buttonState1 == LOW);

}

void white() {
  
  delay(500);
  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2);

do 
{
  
  lcd.setCursor(15,0);
  lcd.blink();

  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2);
 
  if(buttonState1 == HIGH && buttonPosition == 2) {
    amountOfBags('W');
  }


  if(buttonState2 == HIGH && buttonPosition == 2) {
    buttonPosition = 0;
    dough();
  }
}
while(buttonState1 == LOW);
  
}

void dough() {

  delay(500);
  buttonState2 = digitalRead(buttonPin2);
  buttonState1 = digitalRead(buttonPin1);

do 
{
  
  lcd.setCursor(7,0);
  lcd.blink();

  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2);
 
  if(buttonState1 == HIGH && buttonPosition == 0) {
    amountOfBags('D');
  }


  if(buttonState2 == HIGH && buttonPosition == 0) {
    buttonPosition = 1;
    tomato();
  }
}
while(buttonState1 == LOW);

}


void amountOfBags(char type) {

  delay(500);
  lcd.clear();
  int amount = 2;
  lcd.setCursor(0,0);
  lcd.print("a.2  c.6  e.10");
  lcd.setCursor(0,1);
  lcd.print("b.4  d.8  f.12"); 
  lcd.setCursor(3,0);

do {
 
  buttonState2 = digitalRead(buttonPin2);
  buttonState1 = digitalRead(buttonPin1);
  lcd.blink();
 
  
  if(buttonState2 == HIGH && amount == 2) {
    lcd.setCursor(3,1);
    amount = 4;
    delay(500);
    buttonState2 = digitalRead(buttonPin2);
    
  }
  
  if(buttonState2 == HIGH && amount == 4) {
    lcd.setCursor(8,0);
    amount = 6;
    delay(500);
    buttonState2 = digitalRead(buttonPin2);
  }

  if(buttonState2 == HIGH && amount == 6) {
    lcd.setCursor(8,1);
    amount = 8;
    delay(500);
    buttonState2 = digitalRead(buttonPin2);
  }

  if(buttonState2 == HIGH && amount == 8) {
    lcd.setCursor(14,0);
    amount = 10;
    delay(500);
    buttonState2 = digitalRead(buttonPin2);
  }

  if(buttonState2 == HIGH && amount == 10) {
    lcd.setCursor(14,1);
    amount = 12;
    delay(500);
    buttonState2 = digitalRead(buttonPin2);
  }

  if(buttonState2 == HIGH && amount == 12) {
    lcd.setCursor(3,0);
    amount = 2;
    delay(500);
    buttonState2 = digitalRead(buttonPin2);
    
  }

  if(buttonState1 == HIGH) {
    dispense(type, amount);
  }

  
}

while(buttonState1 == LOW);

}


void dispense(char type, int amount) {
  
  lcd.noBlink();
  
  switch (type) {

    case 'D':
    doughAmount = amount;
    
      {
        for (int count = doughAmount; doughAmount > 0; doughAmount -= 1) {
          updateStatus(type);
          handleMovement(type);
          updateStatus(type);
        }
        emptyDevice();
      }
      break;

    case 'T':
    tomatoAmount = amount;
      {
        for (int count = tomatoAmount; tomatoAmount > 0; tomatoAmount -= 1) {
          updateStatus(type);
          handleMovement(type);
          updateStatus(type);
        }
        emptyDevice();
      }
      break;

    case 'W':
    whiteAmount = amount;
      {
        for (int count = whiteAmount; whiteAmount > 0; whiteAmount -= 1) {
          updateStatus(type);
          handleMovement(type);
          updateStatus(type);
        }
        emptyDevice();
      }
      break;

    default:
      {
        lcd.clear();
        lcd.print("Error@dispense");
      }
      break;
  }

}


void updateStatus(char type) {
  switch (type) {

    case 'D':
      {
        lcd.clear();
        String string1 = "Dough: ";
        String string2 = string1 + doughAmount;
        lcd.print(string2);
        delay(1000);
      }
      break;

    case 'T':
      {
        lcd.clear();
        String string1 = "Tomato: ";
        String string2 = string1 + tomatoAmount;
        lcd.print(string2);
        delay(1000);
      }
      break;

    case 'W':
      {
        lcd.clear();
        String string1 = "White: ";
        String string2 = string1 + whiteAmount;
        lcd.print(string2);
        delay(1000);
      }
      break;

    default:
      {
        lcd.clear();
        lcd.print("Error@updateStatus");
        break;
      }
  }
}

void emptyDevice() {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("a.Continue");
  lcd.setCursor(0, 1);
  lcd.print("b.Refill");
  int position = 0;
  lcd.setCursor(10,0);

  do {
 
  buttonState2 = digitalRead(buttonPin2);
  buttonState1 = digitalRead(buttonPin1);
  lcd.blink();
 
  
  if(buttonState2 == HIGH && position == 0) {
    lcd.setCursor(8,1);
    position = 1;
    delay(500);
    buttonState2 = digitalRead(buttonPin2);
    
  }
  
  if(buttonState2 == HIGH && position == 1) {
    lcd.setCursor(10,0);
    position = 0;
    delay(500);
    buttonState2 = digitalRead(buttonPin2);
  }

  if(buttonState1 == HIGH && position == 1) {
    setup();
  }

  if(buttonState1 == HIGH && position == 0) {
    setup();
  }
 
} while(buttonState1 == LOW);
}

void handleMovement(char type) {
  
  switch (type) {

    case 'D':
      {
        if (doughAmount % 2 == 0) {
          cwTurn();
          delay(1000);
          cwTurn();
          delay(1000);
          cwTurn();
          delay(1000);
          cwTurn();
          delay(1000);
          cwTurn();
          delay(1000);
          cwTurn();
        } else {
          delay(1000);
          ccTurn();
          delay(1000);
          ccTurn();
          delay(1000);
          ccTurn();
          delay(1000);
          ccTurn();
          delay(1000);
          ccTurn();
          delay(1000);
        }
      }
      break;

    case 'T':
      {
        if (tomatoAmount % 2 == 0) {
          cwTurn();
          delay(100);
          cwTurn();
          delay(100);
          cwTurn();
          delay(100);
          cwTurn();
          delay(100);
          cwTurn();
          delay(100);
          cwTurn();
          delay(100);
        } else {
          delay(1000);
          ccTurn();
          delay(1000);
          ccTurn();
          delay(1000);
          ccTurn();
          delay(1000);
          ccTurn();
          delay(1000);
          ccTurn();
          delay(1000);
        }
      }
      break;

    case 'W':
      {
        if (whiteAmount % 2 == 0) {
          cwTurn();
          delay(1000);
          cwTurn();
          delay(1000);
          cwTurn();
          delay(1000);
          cwTurn();
          delay(1000);
          cwTurn();
          delay(1000);
          cwTurn();
          delay(1000);
        } else {
          delay(1000);
          ccTurn();
          delay(1000);
          ccTurn();
          delay(1000);
          ccTurn();
          delay(1000);
          ccTurn();
          delay(1000);
          ccTurn();
          delay(1000);
        }
      }
      break;

    default:
      {
        lcd.clear();
        lcd.print("Error@handleMovement");
      }
  }
}

void cwTurn() {
    myStepper.setSpeed(90);
    myStepper.step(227);
}

void ccTurn() {
    myStepper.setSpeed(90);
    myStepper.step(-227);
  
}






