# Arduino Morse Code Converter

This Arduino project is my first work on Arduino, and thus involves a lot of beginner level programming and design. The tool uses a push-button to take in morse code input and outputs through an LED. The input morse code is converted to human-readable, English language and displayed on the console window *`Serial.print()`*.

## Understanding the Algorithm

When the push button is pressed, the LED lights up as an indicator. The Morse Code conversion algorithm is composed of 4 timed components. A simple button press (less than 150 ms) means a *`dot`* is generated, while a longer press (less than 400 ms) produces a *`dash`*. For differentiating between each letter, a time-gap between each sequence (of *`dots`* and *`dashes`*) is calculated. If this time is less than 650 ms, then a letter is generated (only if the combination/sequence is valid). For any more time-gap, the program assumes that the word has been formed and goes to print on the next line.

## Building your own Converter

### Hardware Components

- Push Button = 1
- LED = 1
- Arduino Uno = 1
- Breadboard (half-sized) = 1
- Jumper Cables
- Resistor (10 kilohm) = 2

### Connections

Look at the Connection.png and design your system accordingly.
