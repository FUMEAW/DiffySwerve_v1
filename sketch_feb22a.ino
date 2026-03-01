//
//    FILE: AS5600_position.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/AS5600
//
//  Examples may use AS5600 or AS5600L devices.
//  Check if your sensor matches the one used in the example.
//  Optionally adjust the code.


#include "AS5600.h"

//  Uncomment the line according to your sensor type
//AS5600L as5600;   //  use default Wire
AS5600 as5600;   //  use default Wire
//1172 is the approximate zero position

void setup()
{
  while(!Serial);
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("AS5600_LIB_VERSION: ");
  Serial.println(AS5600_LIB_VERSION);
  Serial.println();

  Wire.begin();

  as5600.begin(4);  //  set direction pin.
  as5600.setDirection(AS5600_CLOCK_WISE);  //  default, just be explicit.

  Serial.println(as5600.getAddress());

  //  as5600.setAddress(0x40);  //  AS5600L only

  int b = as5600.isConnected();
  Serial.print("Connect: ");
  Serial.println(b);

  as5600.resetPosition();
  as5600.resetCumulativePosition();
  delay(1000);
}


void loop()
{
  static uint32_t lastTime = 0;

  //  set initial position

  //  update every 100 ms
  //  should be enough up to ~200 RPM
  if (millis() - lastTime >= 100)
  {
    int position = as5600.getCumulativePosition();
    lastTime = millis();
    Serial.print(position / 4096);
    Serial.print("\t");
    Serial.println(as5600.getRevolutions());
  }

  //  just to show how reset can be used
}


//  -- END OF FILE --
//Basically, we need to write PID to work by using the difference between 2 rpms
// r1 = rpm1, r2 = rpm2
// diff = r2 - r1
// r1 = 300
// input = analog encoder 