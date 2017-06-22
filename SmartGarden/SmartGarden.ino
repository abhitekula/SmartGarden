/*
 * Automatic Watering Garden Code
 * By: Abhinav T
 */

int sensorPin = A0;    // select the input pin for the water soil sensor
int ledPin = 13;      // select the pin for the LED
int sensorValue = 0;  // variable to store the value coming from the sensor
int relayPin = 7; // Pin for output relay (turning on water pump/opening water solenoid)

boolean Time = false; //Whether to use a time limit or the stopWateringThreshold to stop watering
int waterThreshold = 750; // When the soil moisture level is above this point start watering
double timeThreshold = 300000; // Time Threshold to stop watering in milliSeconds
int stopWateringThreshold = 400; // When the soil moisture level is below this point stop watering

boolean watering = false;
double startTime;
double currentTime;
double amtDelay;  //Increases the delay when checking the moisture while not watering to save power and decreases the delay when watering to check the current moisture more rapidly

void setup() {
  // declare the ledPin as an OUTPUT:
  pinMode(relayPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // read the value from the sensor:
  sensorValue = analogRead(sensorPin);
  currentTime = millis();
  amtDelay=10000; //Delay for 10 seconds if not watering
  if(watering){ //Checks to see if it is currently watering to know when it should stop watering
    amtDelay=1000; // Change delay to 1 second if watering
    if(Time && (currentTime - startTime)>timeThreshold){ //Check to see if it should use time limit to dictate when to stop watering
      watering=false;
      digitalWrite(relayPin, LOW);
    }
    else if(sensorValue<stopWateringThreshold){
        watering = false;
        digitalWrite(relayPin,LOW);
    }
   }
   else{ //When not watering check to see if soil moisture levl is above water threshold
    if(sensorValue>waterThreshold){
      watering = true;
      digitalWrite(relayPin, HIGH);
      amtDelay=1000;
    }
  }
  delay(amtDelay);
}
