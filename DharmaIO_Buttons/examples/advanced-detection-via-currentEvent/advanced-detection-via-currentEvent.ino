#include <Arduino.h>

// include the DharmaIO_Button library in order to be allowed to use it
#include <DharmaIO_Button.h>

// declare a button called 'myButtonName' to be used on Digital Pin 10
// Button whateverNameYouWant(PinNumber)
Button myCustomButton(10);

void CheckMyCustomButton()
{

  switch (myCustomButton.currentEvent())
  {
  case (NO_EVENT):
    //Serial.println("NO EVENT");
    break;

  case (PRESSED):
    Serial.println("PRESSED");
    break;

  case (HELD):
    Serial.print("HELD - ");
    Serial.println(myCustomButton.timeHeld);
    break;

  case (RELEASED):
    Serial.println("RELEASED");
    break;

  default:
    Serial.println("ERROR - NO TRACKABLE EVENT WAS RETURNED");
    break;
  }

}

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Starting");
  
}

void loop()
{
  // put your main code here, to run repeatedly:
  CheckMyCustomButton();

}
