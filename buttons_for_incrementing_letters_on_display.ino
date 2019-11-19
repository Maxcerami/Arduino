// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int numRows = 2;
const int numCols = 16;

int curCol = 0; //column counter
int curRow = 0; //row counter

int thisLetter = 64; //character before a
int buttonValue1 = LOW; 
int leftPin = 9;
int buttonValue2 = LOW;
int rightPin = 8;
int buttonValue3 = LOW;
int letterPin = 7;

 //cannot read from display - i am using an array to store the letters that are on the LCD display.
  const int arraySize=numRows*numCols;
  int myArray[arraySize];
  int currentLetter = 0;
  int count;

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(numCols, numRows);
  //initialized the serial
  Serial.begin(9600);
  //for my push buttons, i used a pullup digital input - connected button to ground.
  pinMode(leftPin, INPUT_PULLUP);
  pinMode(rightPin, INPUT_PULLUP);
  pinMode(letterPin, INPUT_PULLUP);
  //need this for cursor function to work
  lcd.cursor();

//need to fill my array with teh starting character -1
  for (count=0;count < arraySize+1;count++) {
   myArray[count]=64;
  } 
  //have to initialize currentletter outside of global context
  currentLetter=0;
}


void loop() {
  
  //read analog value of buttons
  buttonValue1=digitalRead(leftPin);
  buttonValue2=digitalRead(rightPin);
  buttonValue3=digitalRead(letterPin);
  
  // push button change letter
   if (buttonValue2 == LOW){
    //looking at the array to see what letter is there
    thisLetter = myArray[currentLetter]; 
          //check to see if we have reached the end of the alphabet
          if (thisLetter <='Y'){ //since the structure is always +1
              //increment the letter
              thisLetter++;
          }
          else {thisLetter = 'A'; //will start over
                   }
      //store the letter in the array
        myArray[currentLetter] = thisLetter;
    
    //write letter to the screen
    lcd.write(thisLetter);
    //cursor will naturally advace so i set it back to the current position
    lcd.setCursor(curCol, curRow);
    delay(250); //this delay seems natural
  
   }
  
  
  
  //push button to increase column
  if (buttonValue3 == LOW){
    //this allows you to scroll to the next column
    if(curCol==15){
      curRow=1;
      //since i am adding +1 below i subtract
      curCol=-1;
    }
    (curCol = curCol+1);
    lcd.setCursor(curCol, curRow);
    //store currentletter in the array
        // checks if we are on the top row or not
        if (curRow==0) {
           currentLetter=curCol;
           }
        else {currentLetter = curCol+numCols;
            }
    delay(250);
  }
 
  
  
  //push button to decrese column
  if (buttonValue1 == LOW){
      //this allows you to scroll to the upper column
      if(curCol==0){
      curRow=0;
      //since i am subtracting 1 below i add
      curCol=16;
    }
    (curCol = curCol-1);
    lcd.setCursor(curCol, curRow);
    //store currentletter in the array
        if (curRow==0) {
           currentLetter=curCol;
           }
        else {currentLetter = curCol+numCols;
            }
    delay(250);
  }
}
