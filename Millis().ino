/*
* **This is work in progress!**
*
* The millis() function is incredibly useful for timeing actions in your code.
* what it does is when the arduino starts, the millis() function will start counting. (in milliseconds)
* we can use this to time actions in our code. but also alowing us to do two things at once (tecnicly not but we will get into that later.)
*/


unsigned long lastTime; // unsighnd long just means a really big int. the max number is big enough for millis to count to almost 50 days! (when it gets to max it roles over and starts back at 0)


void setup() {
Serial.begin(9600); // setup serial monitor
}

void loop() {
  
  // code to do somthing every 500 ms (or half sec)  
  if ((millis() - lastTime) > 500) {
  lastTime = millis();
    
  Serial.println("Did it!")
    
  }

}
