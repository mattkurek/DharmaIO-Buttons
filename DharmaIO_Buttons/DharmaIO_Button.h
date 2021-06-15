#ifndef DharmaIO_Button_h
#define DharmaIO_Button_h

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#define ENABLE_INTERNAL_PULLUP true
#define DISABLE_INTERNAL_PULLUP false

#define NOT_TRIGGERED (bool)false
#define TRIGGERED (bool)true

#define NO_EVENT (byte)0
#define PRESSED (byte)1
#define HELD (byte)2
#define RELEASED (byte)3

#define VALID_EVENT (bool)true
#define INVALID_EVENT (bool)false

#define DEBOUNCE_REQUIRED (bool)true
#define NO_DEBOUNCE (bool)false

class Button
{

private:

    byte pin; // the pin to assign the button to
    bool digitalTrigger; // determines whether the button reacts to a digital state of logic high or logic low

    // state corresponds to a button being pressed
    // state = true -> button is currently pressed
    // state = false -> button is currently released
    bool state = false;
    bool prevState = false;

    unsigned long lastEventMillis = 0;

    const unsigned int debounceTime = 50;

public:

    unsigned long timeHeld = 0;

    /* Object Declaration */
    // Examples
    // Button(13) -> creates a button on pin 13 with default values, so it reacts to a logic level of LOW and uses the internal pullup
    // Button(10, HIGH) -> creates a button on pin 12 that reacts to a logic level of high, the class will automatically disable the pullup resistor
    // Button(11, LOW, DISABLE_INTERNAL_PULLUP) or Button(11, LOW, FALSE)
    Button(byte init_pin, bool digitalTrigger = LOW, bool enableInternalPullup = ENABLE_INTERNAL_PULLUP);

    // functions related to the button state
    bool currentState();
    void getState();
    bool updateState();

    // functions related to event handling
    byte currentEvent(bool requireDebounce = DEBOUNCE_REQUIRED);
    bool IsHeld();      // detects if button is continiously held down
    bool isPressed(bool requireDebounce = DEBOUNCE_REQUIRED);  // detects if button was pressed (but not necessarily released)
    bool wasReleased(bool requireDebounce = DEBOUNCE_REQUIRED); // detects if button was released from a held down state

    // function that prevent button events from being registered more than one time
    bool checkEventDebounce();
    void updateEvent(byte currentEvent);

};

#endif /* DharmaIO_Button_h */
