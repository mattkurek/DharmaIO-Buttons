#include <Arduino.h>
#include "DharmaIO_Button.h"


/*
 *
 *
 * 
 */
Button::Button(byte init_pin, bool digitalTrigger, bool enableInternalPullup)
{

    this->pin = init_pin;
    this->digitalTrigger = digitalTrigger;

    // if button is set to react to logic level high then disable the internal pullup
    if (digitalTrigger == HIGH)
    {
        enableInternalPullup = DISABLE_INTERNAL_PULLUP;
    }

    // set the pinMode based on whether or not to use the internal pullup
    if (enableInternalPullup)
    {
        pinMode(init_pin, INPUT_PULLUP);
    }
    else
    {
        pinMode(init_pin, INPUT);
    }
}



/*
 *
 *
 * 
 */
byte Button::currentEvent(bool requireDebounce)
{

    // first make sure enough time has passed so that functions don't execute twice
    if (requireDebounce == DEBOUNCE_REQUIRED && checkEventDebounce() == INVALID_EVENT)
    {
        return NO_EVENT;
    }

    this->updateState();

    byte currentEvent = NO_EVENT;

    if (this->state == TRIGGERED)
    {
        // if current state = TRIGGERED
        if (this->prevState == NOT_TRIGGERED)
        {
            // if button went from NOT_TRIGGERED to TRIGGERED, then a press occured
            currentEvent = PRESSED;
        }
        else
        {
            // if button was TRIGGERED and is still TRIGGERED, then its being held down
            currentEvent = HELD;
        }
    }
    else
    {
        // if current state = NOT_TRIGGERED
        if (this->prevState == TRIGGERED)
        {
            // if button went from TRIGGERED to NON_TRIGGERED, then it was released
            currentEvent = RELEASED;
        }
    }

    if (currentEvent != NO_EVENT)
    {
        this->updateEvent(currentEvent);
    }

    // return the current event, which must be interpreted by the event's byte definition
    // NO_EVENT = (byte)0 , PRESSED = (byte)1
    // HELD = (byte)2 , RELEASED = (byte)3
    return currentEvent;

}



/*
 *
 *
 * 
 */
// updates the objects 'state' property to either TRIGGERED (true) or NOT_TRIGGERED (false)
bool Button::currentState()
{

    if (digitalRead(this->pin) == this->digitalTrigger)
    {
        this->state = TRIGGERED;
    }
    else
    {
        this->state = NOT_TRIGGERED;
    }

    return this->state;

}



/*
 *
 *
 * 
 */
bool Button::updateState()
{

    // save the last state
    this->prevState = this->state;

    // update the current state and also return it    
    return currentState();

}
// requireDebounce = DEBOUNCE_REQUIRED (true) by default
// debounce is "buffer time" between events and prevents double-executing functions
bool Button::isPressed(bool requireDebounce)
{

    // first make sure enough time has passed so that functions don't execute twice
    if (requireDebounce == DEBOUNCE_REQUIRED && checkEventDebounce() == INVALID_EVENT)
    {
        return false;
    }

    // update this button's state information
    this->updateState();

    // on a button press, the state changes from not triggered to triggered
    // if it was already triggered and the current state was triggered again, thats a held down button
    if (this->prevState == NOT_TRIGGERED && this->state == TRIGGERED)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// requireDebounce = DEBOUNCE_REQUIRED (true) by default
// debounce is "buffer time" between events and prevents double-executing functions
bool Button::wasReleased(bool requireDebounce)
{

    // first make sure enough time has passed so that functions don't execute twice
    if (requireDebounce == DEBOUNCE_REQUIRED && checkEventDebounce() == INVALID_EVENT)
    {
        return false;
    }

    // update this button's state information
    this->updateState();

    // on a button press, the state changes from not triggered to triggered
    // if it was already triggered and the current state was triggered again, thats a held down button
    if (this->prevState == TRIGGERED && this->state == NOT_TRIGGERED)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Button::checkEventDebounce()
{

    // determine how much time has passed since the last currentEvent, and
    // if it is greater than the required debounce time then its a valid currentEvent
    unsigned long currentMillis = millis();

    if (this->lastEventMillis > currentMillis) {
        
    }

    if ((unsigned long)(millis() - this->lastEventMillis) >= this->debounceTime)
    {
        return VALID_EVENT;
    }
    else
    {
        return INVALID_EVENT;
    }

}

void Button::updateEvent(byte currentEvent)
{

    unsigned long currentEventTime = millis();

    if (currentEvent == PRESSED)
    {
        // on a press, reset the time held to 0 since this is the beginning of a hold
        this->timeHeld = 0;
    }
    else if (currentEvent == HELD)
    {
        // since we track every button event, simply add the time since the last event to the time held
        this->timeHeld += (unsigned long)(currentEventTime - this->lastEventMillis);
    }

    // store the current time as the time of "the last event"
    this->lastEventMillis = currentEventTime;
}