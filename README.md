# DharmaIO-Buttons
 
An easy-to-use Arduino library for handling buttons in an efficient and effective manner

## Description

Will add later - An in-depth paragraph about your project and overview of use.

## Getting Started

### Dependencies

* Arduino IDE (or PlatformIO or another compatible IDE)

### Installing

* Download the .zip and extract - for Windows users I recommend using 7zip for all your archiving needs
* Place the folder "DharmaIO_Buttons" inside your libraries folder 
* Arduino default libraries folder, where Matt is changed to your username: C:\Users\Matt\Documents\Arduino\libraries
* If the Arduino IDE is currently open, close all your windows and re-open it. Otherwise just open the Arduino IDE 
* Should be good to go :)

### How to Use DharmaIO_Button

* Include the library in your sketch
```
// place at the top of your sketch file
#include <DharmaIO_Button.h>
```

* Easiest Way to Declare a Button
```
// swap 'yourBtnNameHere' with whatever name you would like to refer to your button with
// swap 'pinNumber' with the pin that you would like to use, do not use an analog pin such as A1, A2, etc
Button yourBtnNameHere(pinNumber);

Button myCustomBtn(10); // would create a button that is attached to pin 10
```

* Full Explanation of How to Declare a Button
```
Button myButtonName(byte pinNumber, bool digitalTrigger, bool enableInternalPullup);

// pinNumber is the digital pin number, it must be a digital pin
// most analog pins can be used as digital pins as well, by simply referring to it as a number
// example: A1 would cause an error, however 15 would work fine and refers to the same pin as A1

// digitalTrigger is the digital logic level that corresponds to a button being pressed down
// your options are LOW or HIGH (also acceptable is 0 or 1, however LOW/HIGH is better for readability)
// the default value is LOW and is recommended for ease of use as it results in a minimalist circuit

// enableInternalPullup allows you to utilize the internal pullup resistors, rather than manually placing 10k resistors
// your options are ENABLE_INTERNAL_PULLUP or DISABLE_INTERNAL_PULLUP (true or false)
// the default value is ENABLE_INTERNAL_PULLUP and is recommended in conjuction with digitalTrigger = LOW for a minimalist circuit
// if you use digitalTrigger = HIGH, the library will automatically force DISABLE_INTERNAL_PULLUP 

//
//      examples
//

// three ways to declare the exact same button, because LOW and ENABLE_INTERNAL_PULLUP are default values
Button myButton1(9);
Button myButton1(9, LOW);
Button myButton1(9, LOW, ENABLE_INTERNAL_PULLUP);

// three ways to declare the exact same button, because no matter what if digitalTrigger = HIGH then the button will force DISABLE_INTERNAL_PULLUP
Button myButton2(10, HIGH);
Button myButton2(10, HIGH, ENABLE_INTERNAL_PULLUP);
Button myButton2(10, HIGH, DISABLE_INTERNAL_PULLUP);

```

## Help

Any advise for common problems or issues. (i'll do this later)
```
command to run if program contains helper info
```

## Authors

Created by Matt Kurek

[Dharma Engineering](https://dharmaengineering.com/)

## Version History

(Will edit later, this is from readme template)

* 0.2
    * Various bug fixes and optimizations
    * See [commit change]() or See [release history]()
* 0.1
    * Initial Release

## License

This project is licensed under the MIT License - see the LICENSE.md file for details

## Acknowledgments

Obviously the Arduino crew gets a shoutout
* [Arduino](https://www.arduino.cc/)

Support these two companies whenever you can, as they actually develop new open-source components/libraries
* [Adafruit](https://www.adafruit.com/)
* [Sparkfun](https://www.sparkfun.com/)