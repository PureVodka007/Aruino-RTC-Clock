/* Clock MK-II 
 *  working on this 
 *  JAN 27 2021
 *  Adding a deep sleep mode (To Reduce usage and prevent oled screen burn
 * 
 *  
 */



#include <avr/sleep.h>//this AVR library contains the methods that controls the sleep modes
#define interruptPin 2 //Pin we are going to use to wake up the Arduino
#include <ACROBOTIC_SSD1306.h>// oled library
#include <Wire.h>             // i2c interface
#include <virtuabotixRTC.h>   // rtc clock library 

// Creation of the Real Time Clock Object
virtuabotixRTC myRTC(6, 7, 8);



void setup() {
  // Make Sure the time is set ( To set Time use rtc sketch)
  pinMode(interruptPin,INPUT_PULLUP);//Set pin d2 to input using the buildin pullup resistor
  pinMode(LED_BUILTIN,OUTPUT);
  Wire.begin(); // i2c interface
   oled.init(); // intiating oled
   oled.clearDisplay(); // to clear buffer 
}

void loop() {
 
 
delay(5000);//wait 5 seconds before going to sleep
 
 Going_To_Sleep();
}

void Going_To_Sleep(){
    sleep_enable();//Enabling sleep mode
    attachInterrupt(0, wakeUp, LOW);//attaching a interrupt to pin d2
    oled.clearDisplay();
    digitalWrite(LED_BUILTIN,LOW);
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);//Setting the sleep mode, in our case full sleep
    sleep_cpu();//activating sleep mode
    // after sleep time over
    
  myRTC.updateTime();

oled.setTextXY(0,0);
   oled.putString("Big Watch");
   oled.setTextXY(2,0);
  oled.putString("Time:");
  oled.setTextXY(4,0);
  oled.putNumber(myRTC.hours);
  oled.setTextXY(4,2);
  oled.putString(":");
  oled.setTextXY(4,3);
  oled.putNumber(myRTC.minutes);
  oled.setTextXY(4,6);
  oled.putString(":");
  oled.setTextXY(4,7);
  oled.putNumber(myRTC.seconds);
  digitalWrite(LED_BUILTIN,HIGH);

  }

void wakeUp(){
   sleep_disable();//Disable sleep mode
  detachInterrupt(0); //Removes the interrupt from pin 2;
}
