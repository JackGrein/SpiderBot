#include "Servotor32.h"

Servotor32 hexa; // create a servotor32 object

// int RotMiddlemove = 200; //rotation range of motion for middle parts
// int RotSidesmoves = 1000; //rotation range for the sides

int h0 = 0; //regular height of 
int h1 = 500;

int d = 1500; //default setting

int steps1 = 100;

int stepr2 = 50;

int stps3 = 26;

int i1L1 = 0;
int i2L1 = 0;
int i3L1 = 10;
int i4L1 = 30;
int i5L1 = 0;
int i6L1 = 0;

int i1L2 = 0;
int i2L2 = 0;
int i3L2 = 10;
int i4L2 = 30;
int i5L2 = 0;
int i6L2 = 0;
boolean l1status = LOW;
boolean l2status = LOW;

//offsets
int f1 = -350; /*was 500*/ int f2 = -500; //was 350
int f3 = -350; /*was 350*/ int f4 = -350; //was 500
int f5 = -350; /*was 350*/ int f6 = -350; //was 500

void setup() {
  //Connection to Board
  pinMode(STATUS_LED, OUTPUT);  // set LED pin as output
  //digitalWrite(STATUS_LED, HIGH);    // switch off LED pin
  //delay(2000);
  digitalWrite(STATUS_LED, LOW);
  Serial1.begin(9600);  // initialize UART with baud rate of 9600

  //Hexapod Start.
  hexa.begin();
  // Make sure all servos are off

  // Leg1 (Top Left Leg)
  hexa.changeServo(0,-1); //Bottom of leg
  hexa.changeServo(1,-1); //Middle of leg
  hexa.changeServo(2,-1); //Top of leg

  // Leg2 (Top Right)
  hexa.changeServo(31,-1);
  hexa.changeServo(30,-1);
  hexa.changeServo(29,-1);

  // Leg3
  hexa.changeServo(4,-1);
  hexa.changeServo(5,-1);
  hexa.changeServo(6,-1);

  // Leg4
  hexa.changeServo(27,-1);
  hexa.changeServo(26,-1);
  hexa.changeServo(25,-1);

  // Leg5
  hexa.changeServo(15,-1);
  hexa.changeServo(14,-1);
  hexa.changeServo(13,-1);

  // Leg6
  hexa.changeServo(16,-1);
  hexa.changeServo(17,-1);
  hexa.changeServo(18,-1);

  // == Move to initial position
  // Leg1 (Top Left Leg)
  hexa.changeServo(0,1500); //Bottom of leg
  //hexa.changeServo(1,1500); //Middle of leg
  hexa.changeServo(2,1500); //Top of leg
  hexa.delay_ms(1000);

  // Leg2 (Top Right)
  hexa.changeServo(31,1500);
  //hexa.changeServo(30,1500);
  hexa.changeServo(29,1500);
  hexa.delay_ms(1000);

  // Leg3
  hexa.changeServo(4,1500);
  //hexa.changeServo(5,1500);
  hexa.changeServo(6,1500);
  hexa.delay_ms(1000);

  // Leg4
  hexa.changeServo(27,1500);
  //hexa.changeServo(26,1500);
  hexa.changeServo(25,1500);
  hexa.delay_ms(1000);

  // Leg5
  hexa.changeServo(15,1500);
  //hexa.changeServo(14,1500);
  hexa.changeServo(13,1500);
  hexa.delay_ms(1000);

  // Leg6
  hexa.changeServo(16,1500);
  //hexa.changeServo(17,1500);
  hexa.changeServo(18,1500);
  hexa.delay_ms(1000);

  // Modified Initial POSITION

  // Leg1 (Top Left Leg)
  hexa.changeServo(0,1500 - f1); //Bottom of leg
  hexa.changeServo(1,1500 - f1); //Middle of leg
  hexa.changeServo(2,1500); //Top of leg
  hexa.delay_ms(1000);

  // Leg2 (Top Right)
  hexa.changeServo(31,1500 + f2);
  hexa.changeServo(30,1500 + f2);
  hexa.changeServo(29,1500);
  hexa.delay_ms(1000);

  // Leg3
  hexa.changeServo(4,1500 - f3);
  hexa.changeServo(5,1500 - f3);
  hexa.changeServo(6,1500);
  hexa.delay_ms(1000);

  // Leg4
  hexa.changeServo(27,1500 + f4);
  hexa.changeServo(26,1500 + f4);
  hexa.changeServo(25,1500);
  hexa.delay_ms(1000);

  // Leg5
  hexa.changeServo(15,1500 - f5);
  hexa.changeServo(14,1500 - f5);
  hexa.changeServo(13,1500);
  hexa.delay_ms(1000);

  // Leg6
  hexa.changeServo(16,1500 + f6);
  hexa.changeServo(17,1500 + f6);
  hexa.changeServo(18,1500);
  hexa.delay_ms(1000);

  //like butter on toast
  hexa.changeServo(2, 1000); hexa.changeServo(29, 2000); //500
  hexa.changeServo(6, 1300); hexa.changeServo(25, 1700); //200
  hexa.changeServo(13, 2000); hexa.changeServo(18, 1000); //500
}

void loop() {
  
  if (Serial1.available() >= 0) {
    char receivedData = Serial1.read();  // read one byte from serial buffer and save to receivedData
    ///*
    //if (receivedData == '1') {
    //  //Serial1.println('1');
    //  Serial1.println('1');
    //  digitalWrite(STATUS_LED, HIGH);  // switch LED On
    //} 
    //else if (receivedData == '0') {
    //  Serial1.println('0');
    //  digitalWrite(STATUS_LED, LOW);  // switch LED Off
    //}
    //
    
    // Initial and resting position 
    if (receivedData == '0') {
      initialPosition();
    }

    else if (receivedData == '1') {
      // Move forward
      moveLeg1();
      moveLeg4();
      moveLeg5();
      if (l1status == HIGH) {
        moveLeg2();
        moveLeg3();
        moveLeg6();
      }
    }
    else if (receivedData == '5') {
      // Rotate left
      moveLeg1();
      moveLeg3();
      moveLeg5Rev();
      if (l1status == HIGH) {
        moveLeg2();
        moveLeg4Rev();
        moveLeg6Rev();
      }
    }
    else if (receivedData == '6') {
      // Rotate right
      moveLeg1Rev();
      moveLeg3Rev();
      moveLeg5();
      if (l1status == HIGH) {
        moveLeg2Rev();
        moveLeg4();
        moveLeg6();
      }
    }
    else if (receivedData == '2') {
      // Move reverse
      moveLeg1Rev();
      moveLeg4Rev();
      moveLeg5Rev();
      if (l1status == HIGH) {
        moveLeg2Rev();
        moveLeg3Rev();
        moveLeg6Rev();
      }
    }
  }
  //delay(10000);
}

void moveLeg1() {
  // Swign phase - move leg though air - from initial to final position
  // Rise the leg
  if (i1L1 <= 10) {
    hexa.changeServo(0,-f1 + d - i1L1 * 33.5); //Bottom of leg
    hexa.changeServo(1,-f1 + d + i1L1 * 50); //Middle of leg
    i1L1++;
  }
  // Rotate the leg
  if (i2L1 <= 30) {
    hexa.changeServo(2,d - i2L1 * 16.66); //Top of leg
    i2L1++;
  }
  // Move back to touch the ground
  if (i2L1 > 20 & i3L1 >= 0) {
    hexa.changeServo(0,-f1 + d - i3L1 * 33.5); //Bottom of leg
    hexa.changeServo(1,-f1 + d + i3L1 * 50); //Middle of leg
    i3L1--;
  }
  // Stance phase - move leg while touching the ground
  // Rotate back to initial position
  if (i2L1 >= 30) {
    hexa.changeServo(2,d - i4L1 * 16.66);
    i4L1--;
    l1status = HIGH;
  }
  // Reset the counters for repeating the process
  if (i4L1 <= 0) {
    i1L1 = 0;
    i2L1 = 0;
    i3L1 = 10;
    i4L1 = 30;
    i5L1 = 0;
  }
  // Each iteration or step is executed in the main loop section where there is also a delay time for controlling the speed of movement
}

void moveLeg2() {
  // Rise the leg
  if (i1L2 <= 10) {
    hexa.changeServo(31,f2 + d + i1L2 * 33.5); //Bottom of leg
    hexa.changeServo(30,f2 + d - i1L2 * 50); //Middle of leg
    i1L2++;
  }
  // Rotate the leg
  if (i2L2 <= 30) {
    hexa.changeServo(29,d + i2L2 * 16.66); //Top of leg
    i2L2++;
  }
  // Move back to touch the ground
  if (i2L2 > 20 & i3L2 >= 0) {
    hexa.changeServo(31,f2 + d + i3L2 * 33.5); //Bottom of leg
    hexa.changeServo(30,f2 + d - i3L2 * 50); //Middle of leg
    i3L2--;
  }
  // Stance phase - move leg while touching the ground
  // Rotate back to initial position
  if (i2L2 >= 30) {
    hexa.changeServo(29,d + i4L2 * 16.66);
    i4L2--;            
  }
  // Reset the counters for repeating the process
  if (i4L2 <= 0) {
    i1L2 = 0;
    i2L2 = 0;
    i3L2 = 10;
    i4L2 = 30;
    i5L2 = 0;
  }
}


void moveLeg3() {
  // Rise the leg
  if (i1L2 <= 10) {
    hexa.changeServo(4,-f3 + d - i1L2 * 33.5); //Bottom of leg
    hexa.changeServo(5,-f3 + d + i1L2 * 50); //Middle of leg
    i1L2++;
  }
  // Rotate the leg
  if (i2L2 <= 30) {
    hexa.changeServo(6,d - i2L2 * 6.66); //Top of leg
    i2L2++;
  }
  // Move back to touch the ground
  if (i2L2 > 20 & i3L2 >= 0) {
    hexa.changeServo(4,-f3 + d - i3L2 * 33.5); //Bottom of leg
    hexa.changeServo(5,-f3 + d + i3L2 * 50); //Middle of leg
    i3L2--;
  }
  // Stance phase - move leg while touching the ground
  // Rotate back to initial position
  if (i2L2 >= 30) {
    hexa.changeServo(6,d - i4L2 * 6.66);
    i4L2--;
    l1status = HIGH;
  }
}

void moveLeg4() { // SET NEGATIVES
  // Rise the leg
  if (i1L1 <= 10) {
    hexa.changeServo(27,f4 + d + i1L1 * 33.5); //Bottom of leg
    hexa.changeServo(26,f4 + d - i1L1 * 50); //Middle of leg
    i1L1++;
  }
  // Rotate the leg
  if (i2L1 <= 30) {
    hexa.changeServo(25,d + i2L1 * 6.66); //Top of leg
    i2L1++;
  }
  // Move back to touch the ground
  if (i2L1 > 20 & i3L1 >= 0) {
    hexa.changeServo(27,f4 + d + i3L1 * 33.5); //Bottom of leg
    hexa.changeServo(26,f4 + d - i3L1 * 50); //Middle of leg
    i3L1--;
  }
  // Stance phase - move leg while touching the ground
  // Rotate back to initial position
  if (i2L1 >= 30) {
    hexa.changeServo(25,d + i4L1 * 6.66);
    i4L1--;
  }
}

void moveLeg5() {
  // Rise the leg
  if (i1L1 <= 10) {
    hexa.changeServo(15,-f5 + d - i1L1 * 33.5); //Bottom of leg
    hexa.changeServo(14,-f5 + d + i1L1 * 16.66); //Middle of leg
    i1L1++;
  }
  // Rotate the leg
  if (i2L1 <= 30) {
    hexa.changeServo(13,d + 500 - i2L1 * 16.66); //Top of leg
    i2L1++;
  }
  // Move back to touch the ground
  if (i2L1 > 20 & i3L1 >= 0) {
    hexa.changeServo(15,-f5 + d - i3L1 * 33.5); //Bottom of leg
    hexa.changeServo(14,-f5 + d + i3L1 * 50); //Middle of leg
    i3L1--;
  }
  // Stance phase - move leg while touching the ground
  // Rotate back to initial position
  if (i2L1 >= 30) {
    hexa.changeServo(13,d + 500 - i4L1 * 16.66);
    i4L1--;
  }
}

void moveLeg6() {
  // Rise the leg
  if (i1L2 <= 10) {
    hexa.changeServo(16,f6 + d + i1L2 * 33.5); //Bottom of leg
    hexa.changeServo(17,f6 + d - i1L2 * 50); //Middle of leg
    i1L2++;
  }
  // Rotate the leg
  if (i2L2 <= 30) {
    hexa.changeServo(18,d - 500 + i2L2 * 16.66); //Top of leg
    i2L2++;
  }
  // Move back to touch the ground
  if (i2L2 > 20 & i3L2 >= 0) {
    hexa.changeServo(16,f6 + d + i3L2 * 33.5); //Bottom of leg
    hexa.changeServo(17,f6 + d - i3L2 * 50); //Middle of leg
    i3L2--;
  }
  // Stance phase - move leg while touching the ground
  // Rotate back to initial position
  if (i2L2 >= 30) {
    hexa.changeServo(18,d - 500 + i4L2 * 16.66);
    i4L2--;
    l1status = HIGH;
  }
}

void initialPosition() {

  l1status = LOW;
  l2status = LOW;
  
  // Leg1 (Top Left Leg)
  hexa.changeServo(0,1500); //Bottom of leg
  hexa.changeServo(1,1500); //Middle of leg
  //hexa.changeServo(2,1500); //Top of leg

  // Leg2 (Top Right)
  hexa.changeServo(31,1500);
  hexa.changeServo(30,1500);
  //hexa.changeServo(29,1500);

  // Leg3
  hexa.changeServo(4,1500);
  hexa.changeServo(5,1500);
  //hexa.changeServo(6,1500);

  // Leg4
  hexa.changeServo(27,1500);
  hexa.changeServo(26,1500);
  //hexa.changeServo(25,1500);

  // Leg5
  hexa.changeServo(15,1500);
  hexa.changeServo(14,1500);
  //hexa.changeServo(13,1500);

  // Leg6
  hexa.changeServo(16,1500);
  hexa.changeServo(17,1500);
  //hexa.changeServo(18,1500);

  //like butter on toast
  hexa.changeServo(2, 1000); hexa.changeServo(29, 2000); //500
  hexa.changeServo(6, 1300); hexa.changeServo(25, 1700); //200
  hexa.changeServo(13, 2000); hexa.changeServo(18, 1000); //500

  i1L1 = 0;
  i2L1 = 0;
  i3L1 = 10;
  i4L1 = 30;
  i5L1 = 0;
  i6L1 = 0;

  i1L2 = 0;
  i2L2 = 0;
  i3L2 = 10;
  i4L2 = 30;
  i5L2 = 0;
  i6L2 = 0;
}

void moveLeg1Rev() {
  // Rise the leg
  if (i1L1 <= 10) {
    hexa.changeServo(0,-f1 + d - i1L1 * 33.5); //Bottom of leg
    hexa.changeServo(1,-f1 + d + i1L1 * 50); //Middle of leg
    i1L1++;
  }
  // Rotate the leg
  if (i2L1 <= 30) {
    hexa.changeServo(2,(d-500) + i2L1 * 16.66); //Top of leg
    i2L1++;
  }
  // Move back to touch the ground
  if (i2L1 > 20 & i3L1 >= 0) {
    hexa.changeServo(0,-f1 + d - i3L1 * 33.5); //Bottom of leg
    hexa.changeServo(1,-f1 + d + i3L1 * 50); //Middle of leg
    i3L1--;
  }
  // Stance phase - move leg while touching the ground
  // Rotate back to initial position
  if (i2L1 >= 30) {
    hexa.changeServo(2,(d-500) + i4L1 * 16.66);
    i4L1--;
    l1status = HIGH;
  }
  // Reset the counters for repeating the process
  if (i4L1 <= 0) {
    i1L1 = 0;
    i2L1 = 0;
    i3L1 = 10;
    i4L1 = 30;
    i5L1 = 0;
  }
}
void moveLeg2Rev() {
  if (i1L2 <= 10) {
    hexa.changeServo(31,f2 + d + i1L2 * 33.5); //Bottom of leg
    hexa.changeServo(30,f2 + d - i1L2 * 50); //Middle of leg
    i1L2++;
  }
  // Rotate the leg
  if (i2L2 <= 30) {
    hexa.changeServo(29,(d+500) - i2L2 * 16.66); //Top of leg
    i2L2++;
  }
  // Move back to touch the ground
  if (i2L2 > 20 & i3L2 >= 0) {
    hexa.changeServo(31,f2 + d + i3L2 * 33.5); //Bottom of leg
    hexa.changeServo(30,f2 + d - i3L2 * 50); //Middle of leg
    i3L2--;
  }
  // Stance phase - move leg while touching the ground
  // Rotate back to initial position
  if (i2L2 >= 30) {
    hexa.changeServo(29,(d+500) - i4L2 * 16.66);
    i4L2--;            
  }
  // Reset the counters for repeating the process
  if (i4L2 <= 0) {
    i1L2 = 0;
    i2L2 = 0;
    i3L2 = 10;
    i4L2 = 30;
    i5L2 = 0;
  }
}

void moveLeg3Rev() {
  if (i1L2 <= 10) {
    hexa.changeServo(4,-f3 + d - i1L2 * 33.5); //Bottom of leg
    hexa.changeServo(5,-f3 + d + i1L2 * 50); //Middle of leg
    i1L2++;
  }
  // Rotate the leg
  if (i2L2 <= 30) {
    hexa.changeServo(6,(d-200) + i2L2 * 6.66); //Top of leg
    i2L2++;
  }
  // Move back to touch the ground
  if (i2L2 > 20 & i3L2 >= 0) {
    hexa.changeServo(4,-f3 + d - i3L2 * 33.5); //Bottom of leg
    hexa.changeServo(5,-f3 + d + i3L2 * 50); //Middle of leg
    i3L2--;
  }
  // Stance phase - move leg while touching the ground
  // Rotate back to initial position
  if (i2L2 >= 30) {
    hexa.changeServo(6,(d-200) + i4L2 * 6.66);
    i4L2--;
    l1status = HIGH;
  }
}

void moveLeg4Rev() {
  if (i1L1 <= 10) {
    hexa.changeServo(27,f4 + d + i1L1 * 33.5); //Bottom of leg
    hexa.changeServo(26,f4 + d - i1L1 * 50); //Middle of leg
    i1L1++;
  }
  // Rotate the leg
  if (i2L1 <= 30) {
    hexa.changeServo(25,(d+200) - i2L1 * 6.66); //Top of leg
    i2L1++;
  }
  // Move back to touch the ground
  if (i2L1 > 20 & i3L1 >= 0) {
    hexa.changeServo(27,f4 + d + i3L1 * 33.5); //Bottom of leg
    hexa.changeServo(26,f4 + d - i3L1 * 50); //Middle of leg
    i3L1--;
  }
  // Stance phase - move leg while touching the ground
  // Rotate back to initial position
  if (i2L1 >= 30) {
    hexa.changeServo(25,(d+200) - i4L1 * 6.66);
    i4L1--;
  }
}

void moveLeg5Rev() {
  if (i1L1 <= 10) {
    hexa.changeServo(15,-f5 + d - i1L1 * 33.5); //Bottom of leg
    hexa.changeServo(14,-f5 + d + i1L1 * 16.66); //Middle of leg
    i1L1++;
  }
  // Rotate the leg
  if (i2L1 <= 30) {
    hexa.changeServo(13,(d-500) + 500 + i2L1 * 16.66); //Top of leg
    i2L1++;
  }
  // Move back to touch the ground
  if (i2L1 > 20 & i3L1 >= 0) {
    hexa.changeServo(15,-f5 + d - i3L1 * 33.5); //Bottom of leg
    hexa.changeServo(14,-f5 + d + i3L1 * 50); //Middle of leg
    i3L1--;
  }
  // Stance phase - move leg while touching the ground
  // Rotate back to initial position
  if (i2L1 >= 30) {
    hexa.changeServo(13,(d-500) + 500 + i4L1 * 16.66);
    i4L1--;
  }
}

void moveLeg6Rev() {
  if (i1L2 <= 10) {
    hexa.changeServo(16,f4 + d + i1L2 * 33.5); //Bottom of leg
    hexa.changeServo(17,f4 + d - i1L2 * 50); //Middle of leg
    i1L2++;
  }
  // Rotate the leg
  if (i2L2 <= 30) {
    hexa.changeServo(18,(d+500) - 500 - i2L2 * 16.66); //Top of leg
    i2L2++;
  }
  // Move back to touch the ground
  if (i2L2 > 20 & i3L2 >= 0) {
    hexa.changeServo(16,f4 + d + i3L2 * 33.5); //Bottom of leg
    hexa.changeServo(17,f4 + d - i3L2 * 50); //Middle of leg
    i3L2--;
  }
  // Stance phase - move leg while touching the ground
  // Rotate back to initial position
  if (i2L2 >= 30) {
    hexa.changeServo(18,(d+500) - 500 - i4L2 * 16.66);
    i4L2--;
    l1status = HIGH;
  }
}
/*
void moveLeg1Right() {
  if (i1L1 <= 10) {
    s18.write(60 - i1L1 * 2);
    s17.write(90 - i1L1 * 3);
    i1L1++;
  }
  if (i2L1 <= 30) {
    s16.write(70 + i2L1);
    i2L1++;

  }
  if (i2L1 > 20 & i3L1 <= 10) {
    s18.write(40 + i3L1 * 2);
    s17.write(60 + i3L1 * 3);
    i3L1++;
  }
  if (i2L1 >= 30) {
    s16.write(100 - i4L1);
    i4L1++;
    l1status = HIGH;
  }
  if (i4L1 >= 30) {
    i1L1 = 0;
    i2L1 = 0;
    i3L1 = 0;
    i4L1 = 0;
    i5L1 = 0;
  }
}
void moveLeg2Right() {
  if (i1L2 <= 10) {
    s21.write(50 - i1L2 * 2);
    s20.write(80 - i1L2 * 3);
    i1L2++;
  }
  if (i2L2 <= 30) {
    s19.write(45 + i2L2);
    i2L2++;

  }
  if (i2L2 > 20 & i3L2 <= 10) {
    s21.write(30 + i3L2 * 2);
    s20.write(50 + i3L2 * 3);
    i3L2++;
  }
  if (i2L2 >= 30) {
    s19.write(75 - i4L2);
    i4L2++;
  }
  if (i4L2 >= 30) {
    i1L2 = 0;
    i2L2 = 0;
    i3L2 = 0;
    i4L2 = 0;
    i5L2 = 0;
  }
}

void moveLeg3Right() {
  if (i1L1 <= 10) {
    s24.write(50 - i1L1 * 2);
    s23.write(80 - i1L1 * 3);
  }
  if (i2L1 <= 30) {
    s22.write(50 + i2L1);

  }
  if (i2L1 > 20 & i3L1 <= 10) {
    s24.write(30 + i3L1 * 2);
    s23.write(50 + i3L1 * 3);
  }
  if (i2L1 >= 30) {
    s22.write(80 - i4L1);
  }
}

void moveLeg4Left() {
  if (i1L2 <= 10) {
    s10.write(65 + i1L2 * 2);
    s11.write(35 + i1L2 * 3);
  }
  if (i2L2 <= 30) {
    s12.write(60 - i2L2);

  }
  if (i2L2 > 20 & i3L2 <= 10) {
    s10.write(85 - i3L2 * 2);
    s11.write(65 - i3L2 * 3);
  }
  if (i2L2 >= 30) {
    s12.write(30 + i4L2);
  }
}

void moveLeg5Left() {
  if (i1L1 <= 10) {
    s7.write(80 + i1L1 * 2);
    s8.write(50 + i1L1 * 3);
  }
  if (i2L1 <= 30) {
    s9.write(60 - i2L1);

  }
  if (i2L1 > 20 & i3L1 <= 10) {
    s7.write(100 - i3L1 * 2);
    s8.write(80 - i3L1 * 3);
  }
  if (i2L1 >= 30) {
    s9.write(30 + i4L1);
  }
}

void moveLeg6Left() {
  if (i1L2 <= 10) {
    s1.write(90 + i1L2 * 2);
    s2.write(45 + i1L2 * 3);
  }
  if (i2L2 <= 30) {
    s3.write(90 - i2L2);
  }
  if (i2L2 > 20 & i3L2 <= 10) {
    s1.write(110 - i3L2 * 2);
    s2.write(75 - i3L2 * 3);
  }
  if (i2L2 >= 30) {
    s3.write(60 + i4L2);
  }
}
*/
