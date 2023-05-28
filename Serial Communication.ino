
/*
in this code, we use the serial monior to send messages to the arduino. if the message is a string, we will pint the string.
if the given message is a number we will print the string and turn on an LED pluged into the pin with the number corrospondin to the given number.
if the message does not corospond to a pin, noting will happen exept the message being printed.
if the message is to long, we will print a message notifying the user.

refrences:
 https://www.programmingelectronics.com/serial-read/
 https://www.youtube.com/watch?v=nSGnCT080d8&t=336s
*/

const int maxMessageLength = 20; // set the max amount of characters the message can be

void setup() {
 Serial.begin(9600); // setup the serial monitor

 for (int i = 1; i < 13; i++) { // for all pins on uno (all PWM pins on MEGA)
    pinMode(i, OUTPUT);         // set pin to output
 }
}

void loop() {
  while (Serial.available() > 0) { // Check to see if anything is available in the serial receive buffer
    // Create a place to hold the incoming message (a char array)
    static char message[maxMessageLength]; // a char array for the message string
    static unsigned int messagePos = 0;    // a variable for which char we currently are working with
    // note that static just means that the variable or array will act like a global variable or aray whare it will not re-enitulize
    // every time it goes back thrugh the function or loop. But they cannot be refrenced outside of the local loop or function.
    // they will also have to re-enitulize if the program restarts, or if void loop resets.

    char inByte = Serial.read(); // Read the next available byte in the serial receive buffer

    // Message coming in (check not terminating character) and guard for over message size
    if (inByte != '\n' && (messagePos < maxMessageLength - 1)) { // if the current char is not a terminateing char and the message is not too long
     
      // Add the incoming byte to our message
      message[messagePos] = inByte; // add the current car to the array
      messagePos++;                 // change the current char in the message
    
    } else { // if the current char is a terminating char (the full message is recived)
      if (messagePos < maxMessageLength - 1) { // if the message is the proper length
        
        message[messagePos] = '\0';            // Add null character to string (array)
        
        if (atoi(message)) {       // if the given message is a number
          int num = atoi(message); // make a variable to hold the message
          if (num < 14 && (num > 1)) { // check that the given number is a pin
            digitalWrite(num, HIGH); // set the the message equal to a pin, and set that pin to high
          }
        }
        
      Serial.println(message); // Print the message
        
      } else {                                   // if the message is over the proper length
        Serial.readStringUntil('\n');            // read the string sent to the arduino until ther terminating char (new line)
        Serial.println("Message is too long!");  // print and indicator that the string is too long
      }
      messagePos = 0; // reset for the next message
    }
  }
}
