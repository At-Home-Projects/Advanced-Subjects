

/*
Work in progress! has many bugs!
*/


// this program will show you how to find how many characters are in a string (the length) includeing spaces.

const String str = "Hello, GitHub" // variable to hold our string

void setup() {
  Serial.begin(9600); // setup serial monitor
}

void loop() {
 
  int charInMessage = 0; // variable to hold how long the string is

  for (int i = 0; message[i] != '\0'; i++) {charInMessage ++;} // count every char, and save it to the varialble

  Serial.println(charInMessage) // print the number of char in this string
 
  while(true); // stop the program so it only runs once

}
