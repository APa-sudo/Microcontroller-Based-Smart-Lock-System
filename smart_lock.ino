#include <Servo.h>

// Pin Definitions
const int button1Pin = 2;      // First button
const int button2Pin = 4;      // Second button
const int button3Pin = 7;      // Reset button

const int greenLEDPin = 10;    // Green LED
const int redLEDPin = 11;      // Red LED

const int rgbRedPin = 3;       // RGB Red pin
const int rgbGreenPin = 5;     // RGB Green pin
const int rgbBluePin = 6;      // RGB Blue pin

const int potentiometerPin = A0;

// Code sequence for unlocking
const int correctCode[] = {1, 3};
int inputCode[2];
int inputIndex = 0;

// Servo setup
Servo lockServo;

const int lockedPosition = 45;
const int unlockedPosition = 135;

// Debounce timing
unsigned long lastButtonPress = 0;
const long buttonCooldown = 150;

// Button state tracking
int lastButton1State = HIGH;
int lastButton2State = HIGH;
int lastButton3State = HIGH;

bool isSystemUnlocked = false;

void setup()
{
    pinMode(button1Pin, INPUT_PULLUP);
    pinMode(button2Pin, INPUT_PULLUP);
    pinMode(button3Pin, INPUT_PULLUP);

    pinMode(greenLEDPin, OUTPUT);
    pinMode(redLEDPin, OUTPUT);

    pinMode(rgbRedPin, OUTPUT);
    pinMode(rgbGreenPin, OUTPUT);
    pinMode(rgbBluePin, OUTPUT);

    lockServo.attach(9);
    lockServo.write(lockedPosition);

    digitalWrite(redLEDPin, HIGH);
    digitalWrite(rgbRedPin, LOW);
}

void loop()
{
    if (!isSystemUnlocked)
    {
        int potValue = analogRead(potentiometerPin);

        int servoPosition = map(
            potValue,
            0,
            1023,
            lockedPosition,
            unlockedPosition);

        lockServo.write(servoPosition);
    }

    int button1State = digitalRead(button1Pin);
    int button2State = digitalRead(button2Pin);
    int button3State = digitalRead(button3Pin);

    // Button 1
    if (button1State == LOW &&
        lastButton1State == HIGH &&
        millis() - lastButtonPress > buttonCooldown)
    {
        lastButtonPress = millis();

        if (inputIndex < 2)
        {
            inputCode[inputIndex] = 1;
            inputIndex++;
        }
    }

    // Button 2
    if (button2State == LOW &&
        lastButton2State == HIGH &&
        millis() - lastButtonPress > buttonCooldown)
    {
        lastButtonPress = millis();

        if (inputIndex < 2)
        {
            inputCode[inputIndex] = 3;
            inputIndex++;
        }
    }

    // Reset Button
    if (button3State == LOW &&
        lastButton3State == HIGH &&
        millis() - lastButtonPress > buttonCooldown)
    {
        lastButtonPress = millis();
        resetSystem();
    }

    // Check entered code
    if (inputIndex == 2)
    {
        if (inputCode[0] == correctCode[0] &&
            inputCode[1] == correctCode[1])
        {
            unlockSystem();
        }
        else
        {
            digitalWrite(rgbRedPin, HIGH);
            delay(100);
            digitalWrite(rgbRedPin, LOW);
            delay(100);

            digitalWrite(rgbRedPin, HIGH);
            delay(100);
            digitalWrite(rgbRedPin, LOW);
            delay(100);

            digitalWrite(rgbRedPin, HIGH);
            delay(100);
            digitalWrite(rgbRedPin, LOW);

            lockSystem();
        }

        inputIndex = 0;
    }

    lastButton1State = button1State;
    lastButton2State = button2State;
    lastButton3State = button3State;
}

void unlockSystem()
{
    isSystemUnlocked = true;

    lockServo.write(unlockedPosition);

    digitalWrite(redLEDPin, LOW);

    digitalWrite(rgbRedPin, LOW);
    digitalWrite(rgbGreenPin, HIGH);
    delay(50);

    digitalWrite(rgbGreenPin, LOW);
    delay(50);

    digitalWrite(rgbGreenPin, HIGH);
    delay(50);

    digitalWrite(rgbGreenPin, LOW);
    delay(50);

    digitalWrite(rgbGreenPin, HIGH);
    delay(50);

    digitalWrite(rgbGreenPin, LOW);
    delay(50);

    digitalWrite(greenLEDPin, HIGH);
}

void lockSystem()
{
    isSystemUnlocked = false;

    lockServo.write(lockedPosition);

    digitalWrite(greenLEDPin, LOW);
    digitalWrite(redLEDPin, HIGH);

    digitalWrite(rgbRedPin, LOW);
    digitalWrite(rgbGreenPin, LOW);
    digitalWrite(rgbBluePin, LOW);
}

void resetSystem()
{
    isSystemUnlocked = false;

    inputIndex = 0;

    lockServo.write(lockedPosition);

    digitalWrite(greenLEDPin, LOW);

    digitalWrite(rgbRedPin, HIGH);
    digitalWrite(rgbGreenPin, HIGH);
    delay(50);

    digitalWrite(rgbRedPin, LOW);
    digitalWrite(rgbGreenPin, LOW);
    delay(50);

    digitalWrite(rgbRedPin, HIGH);
    digitalWrite(rgbGreenPin, HIGH);
    delay(50);

    digitalWrite(rgbRedPin, LOW);
    digitalWrite(rgbGreenPin, LOW);
    delay(50);

    digitalWrite(rgbRedPin, HIGH);
    digitalWrite(rgbGreenPin, HIGH);
    delay(50);

    digitalWrite(rgbRedPin, LOW);
    digitalWrite(rgbGreenPin, LOW);

    digitalWrite(redLEDPin, HIGH);
}
