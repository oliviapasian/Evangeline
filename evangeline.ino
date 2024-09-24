/*
Experiment 1: Pressure 

"Please Be Gentle With Me"

Olivia Pasian

OCADU DIGF-6037 Creation & Computation

For 1 sensor and 4 LEDs (two different LED colours).
The pressure sensor value indicates which of the LED colour pairs should be on, and if there is no value then all the LEDs should be off.

References:
  "Analog Mapping - 1 Sensor Value" from class example: https://github.com/DigitalFuturesOCADU/CC2024/blob/main/experiment1/analogThreshold_1value/analogThreshold_1value.ino
    - Referenced for code structure, calibration routine, working with thresholds and one sensor

  "Analog Thresholds - 5 Sensor Values" from class example: https://github.com/DigitalFuturesOCADU/CC2024/blob/main/experiment1/fsr_led_thresholds/fsr_led_thresholds.ino
    - Referenced for arrays of LEDs
*/

// number of LEDs (4 total, but 2 sections, each duo controlled as one since they have the same movements)
int numLED = 2;

// initial sensor value set to 0
int sensorValue = 0;

//A0 on Arduino is being used
int sensorPin = A0;

// create arrays to hold the LED "duos", red LEDs on slots 2 and 3, the green are on 4 and 5
const int LEDpinRed[] = { 2, 3 };
const int LEDpinGreen[] = { 4, 5 };

//threshold min and max values, determined in testing/calibration
int threshold = 260;
int threshold2 = 900;


void setup() {
  // initialize serial communication
  Serial.begin(9600);

  //loop through the two LED colour sets to activate multiple at once
  for (int i = 0; i < numLED; i++) {
    //set the two LED colours to be outputs
    pinMode(LEDpinRed[i], OUTPUT);
    pinMode(LEDpinGreen[i], OUTPUT);
  }
}

void loop() {

  //loop through the two LED colour sets to activate multiple at once
  for (int i = 0; i < numLED; i++) {

    // reading the light sensor pin and store value in a variable
    sensorValue = analogRead(sensorPin);

    // calibration stuff (print the sensor values to adjust the thresholds)
    Serial.print("Sensor Value: ");
    Serial.print(sensorValue);
    Serial.print(" (Threshold: ");
    Serial.print(threshold);
    Serial.print("), LED: ");

    //series of if statements: setting the parameters upon which of the LEDs should be turned on, then turning them on if the parameters are met
    if (sensorValue >= threshold2) {
      digitalWrite(LEDpinRed[i], HIGH);
      digitalWrite(LEDpinGreen[i], LOW);
      Serial.println("Red on!");
    } else if (sensorValue > threshold && sensorValue < threshold2) {
      digitalWrite(LEDpinRed[i], LOW);
      digitalWrite(LEDpinGreen[i], HIGH);
      Serial.println("Green on!");
    } else {
      digitalWrite(LEDpinRed[i], LOW);
      digitalWrite(LEDpinGreen[i], LOW);
      Serial.println("Both off");
    }
  }

  // add small delay between readings
  delay(20);
}