// Include Servo Librarie
#include <Servo.h>
// include LCD library
#include <LiquidCrystal_I2C.h>
// include  Keypad Library
#include <Keypad.h>

//Servo
Servo servo;
#define servoPin A0

//LCD
LiquidCrystal_I2C lcd(0x27,16,2);

//Keypad
const byte numRows= 4; //number of rows on the keypad
const byte numCols= 4; //number of columns on the keypad

//keymap defines the key pressed according to the row and columns just as appears on the keypad
char keymap[numRows][numCols]= 
{
{'1', '2', '3', 'A'}, 
{'4', '5', '6', 'B'}, 
{'7', '8', '9', 'C'},
{'*', '0', '#', 'D'}
};

//Code that shows the the keypad connections to the arduino terminals
byte rowPins[numRows] = {9,8,7,6}; //Rows 0 to 3
byte colPins[numCols]= {5,4,3,2}; //Columns 0 to 3

//initializes an instance of the Keypad class
Keypad kpd= Keypad(makeKeymap(keymap), rowPins, colPins, numRows, numCols);


//State Data
bool locked;
bool canTakeInput = true;

//Block
bool blocked = false;
int tries = 0;
const int maxTries = 3;
char deleteKey = '*';
String clearInputString = "0000";


//Graphic Variables
int inputXPos = 6;
int inputYPos = 1;

//Password Variables
String password;
int maxLength = 4;

//Input
String input = "";

void setup()
{
  Serial.begin(9600);
  
  //LCD Setup
  lcd.begin();
  lcd.clear();         
  lcd.backlight();      // Make sure backlight is on

  //Servo
  servo.attach(servoPin);
  servo.write(0);
  
  //Unlock Safe
  unlockSafe(false);
}

void loop()
{
  //In the loop function we're going to check the input
  
  //First of all we look at whether we can even take input
  if (canTakeInput){

    //When these conditions are met, we can read the input, if there is any   
    char key = kpd.getKey();
    if(key != NO_KEY)  // Check for a valid key.
    {   
       if (!blocked){
         //If 'D' is not pressed, we can add key to input
         if(key != 'D'){
           if (input.length() < maxLength){
             input += key;
             lcd.print("*");
             Serial.println(input); //Debug
           }
         }
        else {
           //D equals an "OK" Button
           if (locked)
             tryUnlocking(input); 
           else
             tryLocking(input);
         } 
       }
       else {
         //If key equals delete key, we delete all the invisible input
         if (key == deleteKey){
           resetInput(false);
           return;
         }
         //Add Input 
         input += key;
         
         //Check whether code is correct
         if (input.equals(clearInputString))
          unblockSafe(); 
       }
      }
     }
    
}


//State Functions

	// Password Functions
void tryUnlocking(String pw){  
  if (pw.length() < maxLength){
    
    //Play Error Message: Password is too short
    lcdPwTooShort();
    
    //Get back to previous locked state
    lockSafe(false);
    return;
  }
  
  if (pw.equals(password)){
    //Unlock safe if pw is correct
    //resetInput();
   	unlockSafe(true); 
  } else{
    //Password is wrong message
    lcdPlayStateSwitchAnim(1, 0, "PASSWORD WRONG", 3, 1, "CAN'T OPEN", true);
    tries++;	//increase amount of tries
    
    //Check whether max amount of tries is reached
    if (tries == maxTries){
      blockSafe();
      return;
    }
    
    lockSafe(false);
  }
}

void tryLocking(String pw){    
  if (pw.length() < maxLength){
    
    //Play Error Message: Password is too short
    lcdPwTooShort();
    unlockSafe(false);
  }
  else {
    password = pw;
    
    //Switch to locked State
    lockSafe(true);
  }
}



//	2 Functions to unlock and lock the Safe
//	When being un/locked the servo is going to be rotated into one direction which will eventually open the door
//	Afterwards we're going to switch to the new State
//	anim: chooses whether to use an Transition Animation or not

void unlockSafe(bool anim){
 locked = false;
  
 //Reset the input and the amount of tries
 resetInput(true); 
 tries = 0;
  
 servo.write(10); //Switch Servo to opened State
  
 lcdUnlockSafe(anim); //Change LCD Display to opened
}


void lockSafe(bool anim){
 locked = true; 
  
 resetInput(true);
  
 servo.write(130); //Switch Servo to closed State
  
 lcdLockSafe(anim); //Change LCD Display to closed
}

// Resets the given input
// clearLcd: whether the input text should be released as well
void resetInput(bool clearLcd){
 input = ""; 
  
 // Because we know that there will never be more than 4 char in our input,
 // we can reset it with filling in 4 spaces 
  if (clearLcd){ 
     lcd.setCursor(inputXPos, inputYPos);
     lcd.print("    ");
  }
}


//Blocking Methods
void blockSafe(){
  //Ban user from trying to unlock
  blocked = true;
  lcdPlayStateSwitchAnim(1, 0, "ALL TRIES USED", 5, 1, "BLOCKED", false);
  resetInput(false);
}

void unblockSafe(){
  //Unban user from trying to unlock
  tries = 0;
  blocked = false;
  lcdPlayStateSwitchAnim(5,0, "UNBLOCKED", 5, 1, "OPENING", false);
  resetInput(false);
  
  //Go back to opened state
  unlockSafe(false);
}


//LCD 

void lcdLockSafe(bool anim){
  
  //Play locking Animation
  if (anim)
  	lcdPlayStateSwitchAnim(1, 0, "PASSWORD SAVED", 0, 1, "", true);
  
  lcd.setCursor(1,0);   //Set cursor to character 2 on line 0
  lcd.print("ENTER PASSWORD");
  
  //Cursor gets set to starting point for Input
  lcd.setCursor(inputXPos, inputYPos);
}


void lcdUnlockSafe(bool anim){
  //Play Unlocking Animation First
  if (anim)
  	lcdPlayStateSwitchAnim(0, 0, "PASSWORD CORRECT", 2, 1, "OPEN THE SAFE", true);
  
  //Change to unlocked State
  lcd.setCursor(2,0);   //Set cursor to character 1 on line 0
  lcd.print("SET PASSWORD");

  //Clear second row
  lcd.setCursor(0,1);   //Set cursor to character 1 on line 0
  lcd.print("                ");
  
  //Cursor gets set to starting point for Input
  lcd.setCursor(inputXPos, inputYPos);
}

//	Playing an animation between switching states, which will only last for a small delay, while which you cant take any input
//	fcx:   first Cursor X Value
//	fcy:   first Cursor Y Value
//	fText: first text
//	scx:   second Cursor X Value
//	scy:   second Cursor Y Value
//	sText: second text
//  clear: should animation be cleared after delay?  
void lcdPlayStateSwitchAnim(int fcx, int fcy, String fText, int scx, int scy, String sText, bool clear){
  
  //Clear previous animation
  lcd.clear();
  
  //Can't Take Input While Unlocking Text Plays
  canTakeInput = false;
  
  //Print unlocking Text
  lcd.setCursor(fcx,fcy);   //Set cursor to character 1 on line 0
  lcd.print(fText);

  lcd.setCursor(scx, scy);
  lcd.print(sText);
  
  //Delay for the animation to play
  delay(2000);
  
  
  if (clear){
  	//Clear unlocking animation
  	lcd.clear();
  }
  
  
  //Switching again so now we can take input
  canTakeInput = true;
  
}

void lcdPwTooShort(){
	lcdPlayStateSwitchAnim(6, 0, "ERROR", 1, 1, "NEED 4 LETTERS", true);
}



