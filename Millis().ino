/*
* The millis() function is incredibly useful for timeing actions in your code.
* what it does is when the arduino starts, the millis() function will start counting. (in milliseconds)
* we can use this to time actions in our code. but also alowing us to do two things at once (tecnicly not but we will get into that later.)
*/


unsigned long lastTime; // unsighnd long just means a really big int. the max number is big enough for millis to count to almost 50 days! (when it gets to max it roles over and starts back at 0)


void setup() {
Serial.begin(9600); // setup serial monitor
}

void loop() {
  
  Serial.println(millis()); // print the durrent millis
  
  // code to do somthing every 500 ms (or half sec)
  if ((millis() - lastTime) > 500) { // subtract the current millis by the last recorded millis, then check if it is larger than 500
  lastTime = millis(); // record the current millis (this will not change untill recorded again)
    
  Serial.println("Did it!"); // show that it has been done
    
  }

}


/*
* an example of a way this is uesed in a practical situation is if you have an LED that needs to blink, while also checking the state of a button
* millis alows us to do both at once. Well, not realy. what we can do is, instead of having delays, use the millis function, and it will do what we want at the given interval
*
/*
