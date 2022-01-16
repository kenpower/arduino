/*
 * created by Rui Santos, https://randomnerdtutorials.com
 * 
 * Complete Guide for Ultrasonic Sensor HC-SR04
 *
    Ultrasonic sensor Pins:
        VCC: +5VDC
        Trig : Trigger (INPUT) - Pin11
        Echo: Echo (OUTPUT) - Pin 12
        GND: GND
 */
 

long duration, cm, inches;
//int count = 0;


#include <LiquidCrystal.h>
 
LiquidCrystal lcd(7, 8, 9, 10, 11 , 12);
 
void setup() { 
  Serial.begin(9600);
  lcd.begin(16, 2);
}

int getDistance(){
  int trigPin =3;    // Trigger
  int echoPin = 2;    // Echo
    // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
 
  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echoPin, INPUT);
  int duration = pulseIn(echoPin, HIGH); 
    // Convert the time into a distance
  int mm = (duration/2) / 2.91;     // Divide by 29.1 or multiply by 0.0343


  return mm;
}
const int NUM_D = 10;
int myDistances[NUM_D];
int count = 0;

void loop() {

  int emptyDistance = 1080;
  int fullDistance = 120;
  float volume = 900;
  float litresPerMM = volume/1040;
  float litresPerDay = 3;
  float usableVolume = 900.0 * (960.0 /1040.0);
  
  int d = getDistance(); 
  myDistances[count] = d;
  count++;
  count = count % NUM_D;

  long total = 0;
  for (int i = 0; i < NUM_D; i++) {
    total += myDistances[i];
  }

  int mm = total / NUM_D;

  int oilLevelAboveEmpty = emptyDistance - mm;

  long volumeRemaining = oilLevelAboveEmpty * litresPerMM;

  int volumeToOrder = usableVolume - volumeRemaining;
  int daysLeft = volumeRemaining /litresPerDay;
  long percentFull= (volumeRemaining*100L) / usableVolume;

  //todo remove
  volumeToOrder=mm;



  lcd.clear();
  lcd.setCursor(0,0);
  
  lcd.print(percentFull);
  lcd.write("%");

  
  lcd.setCursor(8,0);
  lcd.write("Days:");
  lcd.print(daysLeft);
  

  lcd.setCursor(0,1);
  // lcd.write("Order ");
  // lcd.print(volumeToOrder);
  // lcd.write("ltrs");
  lcd.write("Dist ");
  lcd.print(volumeToOrder);
  lcd.write("mm");
  
  
  Serial.print("Distance:");
  Serial.println(mm);
  Serial.print("vol remainig:");
  Serial.println(volumeRemaining);  
  Serial.print("usable Vol:");
  Serial.println(usableVolume);
  Serial.print("%");
  Serial.println(volumeRemaining*100);
  
  delay(1000);  
}