#include <Esplora.h>
#include <Wire.h>

char btn_status;

void setup()
{
  //Serial.begin(115200);       // initialize serial communication with your computer
  //Serial.println("Ready!");
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onRequest(requestEvent); // register event
}

void loop()
{
  int xValue = Esplora.readJoystickX();
  int yValue = Esplora.readJoystickY();
  int up = yValue < -256;
  int down = yValue > 256;
  int left = xValue > 256;
  int right = xValue < -256;
  int btnStart = !Esplora.readButton(SWITCH_1);
  int btnSelect = !Esplora.readButton(SWITCH_2);
  int btnB = !Esplora.readButton(SWITCH_3);
  int btnA = !Esplora.readButton(SWITCH_4);

  // translate 8 buttons into 8 bit of char variable
  btn_status = (
                 up
                 | (down << 1)
                 | (left << 2)
                 | (right << 3)
                 | (btnSelect << 4)
                 | (btnStart << 5)
                 | (btnA << 6)
                 | (btnB << 7)
               );

  //Serial.print("Joystick Up: "); Serial.print(up);
  //Serial.print(" Down: "); Serial.print(down);
  //Serial.print(" Left: "); Serial.print(left);
  //Serial.print(" Right: "); Serial.print(right);
  //Serial.print(" Select: "); Serial.print(btnSelect);
  //Serial.print(" Start: "); Serial.print(btnStart);
  //Serial.print(" A: "); Serial.print(btnA);
  //Serial.print(" B: "); Serial.print(btnB);
  //Serial.print(" btn_status: "); Serial.println(btn_status, HEX);

  delay(10);
}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent() {
  //Serial.print(" I2C send: "); Serial.println(btn_status, HEX);

  Wire.write(btn_status);
}
