#define m1 5 // Right Motor MA1
#define m2 4 // Right Motor MA2
#define m3 3 // Left Motor MB1
#define m4 2 // Left Motor MB2
#define e1 9 // Right Motor Enable Pin EA
#define e2 10 // Left Motor Enable Pin EB
 
//**********5 Channel IR Sensor Connection**********//
#define ir1 A0 // Leftmost IR sensor
#define ir2 A1 // Left IR sensor
#define ir3 A2 // Middle IR sensor
#define ir4 A3 // Right IR sensor
#define ir5 A4 // Rightmost IR sensor
//*************************************************//
 
void setup() {
  Serial.begin(9600); // Initialize serial communication
  
  // Set motor pins as output
  pinMode(m1, OUTPUT);
  pinMode(m2, OUTPUT);
  pinMode(m3, OUTPUT);
  pinMode(m4, OUTPUT);
  pinMode(e1, OUTPUT);
  pinMode(e2, OUTPUT);

  // Set IR sensor pins as input
  pinMode(ir1, INPUT);
  pinMode(ir2, INPUT);
  pinMode(ir3, INPUT);
  pinMode(ir4, INPUT);
  pinMode(ir5, INPUT);
}
 
void loop() {
  // Reading sensor values (invert logic as required)
  int s1 = digitalRead(ir1); // Leftmost sensor
  int s2 = digitalRead(ir2); // Left sensor
  int s3 = digitalRead(ir3); // Middle sensor
  int s4 = digitalRead(ir4); // Right sensor
  int s5 = digitalRead(ir5); // Rightmost sensor

  // Print sensor values to the Serial Monitor
  Serial.print(s1);
  Serial.print(s2);
  Serial.print(s3);
  Serial.print(s4);
  Serial.println(s5);

  // If only the middle sensor detects the black line, move forward
  if ((s1 == 1) && (s3 == 0) && (s5 == 1)) {
    Serial.println("hello");
    analogWrite(e1, 20); // Set right motor speed to full
    analogWrite(e2, 20); // Set left motor speed to full
    digitalWrite(m1, HIGH); // Right motor forward
    digitalWrite(m2, LOW);
    digitalWrite(m3, HIGH); // Left motor forward
    digitalWrite(m4, LOW);
  }

  // // If only the left sensor detects the black line, turn right
  // if ((s1 == 1) && (s2 == 0) && (s3 == 1) && (s4 == 1) && (s5 == 1)) {
  //   analogWrite(e1, 20); // Set motor speeds
  //   analogWrite(e2, 20);
  //   digitalWrite(m1, HIGH); // Right motor forward
  //   digitalWrite(m2, LOW);
  //   digitalWrite(m3, LOW);  // Left motor stop
  //   digitalWrite(m4, LOW);
  // }

  // If only the leftmost sensor detects the black line, sharp right
  if ((s1 == 0) && (s3 == 1) && (s5 == 1)) {
    analogWrite(e1, 20); 
    analogWrite(e2, 20);
    digitalWrite(m1, HIGH); // Right motor forward
    digitalWrite(m2, LOW);
    digitalWrite(m3, LOW);  // Left motor reverse
    digitalWrite(m4, LOW);
  }

  // // If only the right sensor detects the black line, turn left
  // if ((s1 == 1) && (s2 == 1) && (s3 == 1) && (s4 == 0) && (s5 == 1)) {
  //   analogWrite(e1, 20);
  //   analogWrite(e2, 20);
  //   digitalWrite(m1, LOW);  // Right motor stop
  //   digitalWrite(m2, LOW);
  //   digitalWrite(m3, HIGH); // Left motor forward
  //   digitalWrite(m4, LOW);
  // }

  // If only the rightmost sensor detects the black line, sharp left
  if ((s1 == 1) && (s3 == 1) && (s5 == 0)) {
    analogWrite(e1, 20);
    analogWrite(e2, 20);
    digitalWrite(m1, LOW);  // Right motor reverse
    digitalWrite(m2, LOW);
    digitalWrite(m3, HIGH); // Left motor forward
    digitalWrite(m4, LOW);
  }

  // Additional conditions for combined sensor detections:
  
  // // Middle and right sensor detect black line
  // if ((s1 == 1) && (s2 == 1) && (s3 == 0) && (s4 == 0) && (s5 == 1)) {
  //   analogWrite(e1, 20);
  //   analogWrite(e2, 20);
  //   digitalWrite(m1, LOW);  // Right motor stop
  //   digitalWrite(m2, LOW);
  //   digitalWrite(m3, HIGH); // Left motor forward
  //   digitalWrite(m4, LOW);
  // }

  // // Middle and left sensor detect black line
  // if ((s1 == 1) && (s2 == 0) && (s3 == 0) && (s4 == 1) && (s5 == 1)) {
  //   analogWrite(e1, 20);
  //   analogWrite(e2, 20);
  //   digitalWrite(m1, HIGH); // Right motor forward
  //   digitalWrite(m2, LOW);
  //   digitalWrite(m3, LOW);  // Left motor stop
  //   digitalWrite(m4, LOW);
  // }

  // All sensors on the black line (stop condition)
  if ((s1 == 1) && (s2 == 1) && (s3 == 1) && (s4 == 1) && (s5 == 1)) {
    digitalWrite(m1, LOW); // Stop motors
    digitalWrite(m2, HIGH);
    digitalWrite(m3, LOW);
    digitalWrite(m4, HIGH);
  }
}
