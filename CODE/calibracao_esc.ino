void setup() {
  // Set the PWM frequency for pin 10 to 500 Hz
  analogWriteFrequency(2, 500);
  // Set the PWM resolution to 8 bits (values between 0-255)
  analogWriteResolution(8);

  // Begin calibration sequence
  // Output a PWM signal with a duty cycle close to 100% (full throttle)
  analogWrite(2,255);
  // Wait for the ESC to recognize the full throttle signal
  delay(4000);
  // Output a PWM signal with a duty cycle close to 0% (zero throttle)
  analogWrite(2,127);
  // Wait for the ESC to recognize the zero throttle signal and complete calibration
  delay(2000);

  // Calibration is now complete
}

void loop() {
  // Your main code here, to run repeatedly after calibration
}