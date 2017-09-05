#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 13
#define SENSER_BIT   9 

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setup(void)
{
  // start serial port
  Serial.begin(115200);
  Serial.println("Dallas Temperature IC Control Library Demo");
  sensors.begin();
  sensors.setResolution(SENSER_BIT);
}

void loop(void)
{ 
  Serial.print("Requesting temperatures...");
  sensors.requestTemperatures();
  Serial.println("DONE");
  Serial.print("Temperature for the device 1 (index 0) is: ");
  Serial.println(sensors.getTempCByIndex(0));
  delay(500);
}
