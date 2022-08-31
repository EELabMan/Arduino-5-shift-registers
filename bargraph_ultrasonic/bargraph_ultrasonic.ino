/*
Arduino 5 Shift registers modified.
*/

//A bar graph that responds to how close you are

#define echoPin 2 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 3 //attach pin D3 Arduino to pin Trig of HC-SR04
const int SER   =8;    //Serial Output to Shift Register
const int LATCH =9;    //Shift Register Latch Pin
const int CLK   =10;   //Shift Register Clock Pin
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement
//Possible LED settings
int vals[9] = {0,1,3,7,15,31,63,127,255};

//Maximum value provided by sensor
int maxVal = 35;

//Minimum value provided by sensor
int minVal = 5;

void setup()
{
  //set ultrasonic sensor pins
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
    //Set shift register pins as outputs
  pinMode(SER, OUTPUT);
  pinMode(LATCH, OUTPUT);
  pinMode(CLK, OUTPUT);
  Serial.begin(9600); // // Serial Communication is starting with 9600 of baudrate speed

}

void loop()
{
    
  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // LED's
  distance = map(distance, maxVal, minVal, 0, 8);
    distance = constrain(distance,0,8);
    digitalWrite(LATCH, LOW);                 //Latch low - start sending
    shiftOut(SER, CLK, MSBFIRST, vals[distance]); //Send data, MSB first
    digitalWrite(LATCH, HIGH);                //Latch high - stop sending
    delay(10);                                //Animation speed

}
