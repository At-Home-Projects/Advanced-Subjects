
/*
* The following is two sets of code. the first is the more convinent way, the second is the more basic, step by step way
*/

/*******************************************************************************/
/*******************************************************************************/

/*
* Path 1 :
*/


// to use this program type commands into the serial monitor. try asking how its doing, or putting in a pin number to turn on/ off an LED

const int maxMessageLength = 20;   // set the maximum length for the message                   

void setup() {
 Serial.begin(9600);               // setup the serial monitor
 for (int i = 1; i < 14; i++) {    // for every pin on the uno (every PWM on Mega)
   pinMode(i, OUTPUT);             // set the pin to output
 }
}

void loop() {
  if (Serial.available()) { // if there is somthing to be read in the serial monitor

    String message = Serial.readStringUntil('\n'); // variable to get the string verstion of the message

    int charInMessage = 0; // variable for how many chars are in the message

    for (int i = 0; message[i] != '\0'; i++) { // for evry char in the message
      charInMessage ++; // add one to the variable that holds the number of chars in the message
    }

    // turn the pin on/off and print the message
    if (message.toInt()) {                    // if the message is a number
      int num = message.toInt();              // make a variable to hold the number verstion of the message
      if (num < 14 && num > 1) {              // if the number is a pin on the arduino board
        if (digitalRead(num) == LOW) {        // if the pin is off
          digitalWrite(num, HIGH);            // turn the pin on
          Serial.println(message + " On");    // notify the user the pin is on
        } else {                              // if the pin is om
          digitalWrite(num, LOW);             // turn the pin off
          Serial.println(message + " Off");   // notify the user the pin os off
        }
      } else {                                // if the message is not a pin number
        Serial.println(message);              // print the message
      }


    } else if (charInMessage > maxMessageLength) { // if the message exeeds the max length
      Serial.println("Message is too long!");      // notufy the user the message is too long
    
    } else {                     // if anything else
      Serial.println(message);   // print the message
    }

    if (message == "How are you?") {            // if the message is this greeting
      Serial.println("Good. How about you?");   // print 'Good. How about you?'
    }
    
  }
}

/*******************************************************************************/
/*******************************************************************************/

/*
* Path 2 :
*/


/*
* in this code, we use the serial monior to send messages to the arduino. if the message is a string, we will pint the string.
* if the given message is a number we will print the string and turn on an LED pluged into the pin with the number corrosponding to the given number.
* if the pin is already on, we will turn it off.
* if the message does not corospond to a pin, noting will happen exept the message being printed.
* if the message is to long, we will print a message notifying the user.
*
* refrences:
* https://www.programmingelectronics.com/serial-read/
* https://www.youtube.com/watch?v=nSGnCT080d8&t=336s
*/

const int maxMessageLength = 20; // set the max amount of characters the message can be
bool asking = false;             // varialbe for if the arduino is asking the user a question

void setup() {
 Serial.begin(9600);             // setup the serial monitor

 for (int i = 1; i < 13; i++) {  // for all pins on uno (all PWM pins on MEGA)
    pinMode(i, OUTPUT);          // set pin to output
 }
}

void loop() {
  while (Serial.available() > 0) { // Check to see if anything is available in the serial receive buffer
    // Create a place to hold the incoming message (a char array)
    static char message[maxMessageLength]; // a char array for the message string
    static unsigned int messagePos = 0;    // a variable for which char we currently are working with
    /*
    * note that static just means that the variable or array will act like a global variable or aray whare it will not re-enitulize
    * every time it goes back thrugh the function or loop. But they cannot be refrenced outside of the local loop or function.
    * they will also have to re-enitulize if the program restarts, or if void loop resets.
    */

    char inByte = Serial.read(); // Read the next available byte in the serial receive buffer

    // Message coming in (check not terminating character) and guard for over message size
    if (inByte != '\n' && (messagePos < maxMessageLength - 1)) { // if the current char is not a terminateing char and the message is not too long
     
      // Add the incoming byte to our message
      message[messagePos] = inByte; // add the current car to the array
      messagePos++;                 // change the current char in the message
    
    } else { // if the current char is a terminating char (the full message is recived)
      if (messagePos < maxMessageLength - 1) { // if the message is the proper length
        
        message[messagePos] = '\0';            // Add null character to string (array)
        
        if (atoi(message)) {                   // if the given message is a number
          
          int num = atoi(message);             // make a variable to hold the number verstion of the message
          if (num < 14 && (num > 1)) {         // check that the given number is a pin
            
            if (digitalRead(num) == LOW) {     // if the pin is already off
              digitalWrite(num, HIGH);         // set the the message equal to a pin, and set that pin to high
              Serial.println(String(message) + " On");  // tell the user the pin is on
            } else {
              digitalWrite(num, LOW);          // turn the LED in the given pin off
              Serial.println(String(message) + " Off"); // tell the user the pin is off
            }
          } else {                             // if it is not a pin on the board
            Serial.println(message);           // print the message
          }
        } else {                               // if it is not a number
          Serial.println(message);             // print the message
        }
        
      } else {                                   // if the message is over the proper length
        Serial.readStringUntil('\n');            // read the string sent to the arduino until ther terminating char (new line)
        Serial.println("Message is too long!");  // print and indicator that the string is too long
      }
      messagePos = 0; // reset for the next message
    }
  }
}
