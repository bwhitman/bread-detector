// Bread Detector for SparkFun Thing board
// From the "SendSMS" breadDetector 

#include <ESP8266WiFi.h>
// Include the SparkFun Phant library.
#include <Phant.h>
#include "OneWire.h"


const char WiFiSSID[] = "***REMOVED***";
const char WiFiPSK[] = "***REMOVED***";
const int LED_PIN = 5; // Thing's onboard, green LED
const int ANALOG_PIN = A0; // The only analog pin on the Thing
const int DIGITAL_PIN = 12; // Digital pin to be read
const char PhantHost[] = "data.sparkfun.com";
const char PublicKey[] = "***REMOVED***";
const char PrivateKey[] = "***REMOVED***";
// deleteKey ***REMOVED***

OneWire ds(DIGITAL_PIN);  //temperature sensor

unsigned long millis_start;
float inch_average = 0;
float temp_average = 0;
float sensor_average = 0;
int readings = 0;

char tempString[10];
char distanceString[10]; 
char sensorString[10];

#define MS_CYCLE 20000l

extern "C" {
#include "user_interface.h"
}



uint read_analog() {
  uint LDR_Value = 0; //Value of LDR (ADC)
  LDR_Value=system_adc_read();
  return LDR_Value;
}

void setup() 
{
  initHardware();
  connectWiFi();
  digitalWrite(LED_PIN, HIGH);
  millis_start = millis();
}


void loop() {
  uint sensorValue = read_analog();
  delay(10);
  if (sensorValue > 0) {
    float voltage = sensorValue / 1023.0;
    float temp = getTemp();
    if (temp < 1) temp = 0; // bad connection or something
    temp_average = temp_average + temp;
    sensor_average = sensor_average + voltage;
    readings = readings + 1;
    
    if (millis() > millis_start + MS_CYCLE ) {
      float temp_average_print = temp_average / readings;
      float sensor_average_print = sensor_average / readings;
      float inches = pow(sensor_average_print, -1.365) * 0.9652;
      dtostrf(inches,4,2,distanceString);
      dtostrf(temp_average_print,4,2,tempString);
      dtostrf(sensor_average_print, 4,2, sensorString);
      postToPhant();
      millis_start = millis();
      readings = 0;
      inch_average = 0;
      temp_average = 0;
      sensor_average = 0;
    }
  }
  delay(1000);

}


void connectWiFi()
{
  byte ledStatus = LOW;

  // Set WiFi mode to station (as opposed to AP or AP_STA)
  WiFi.mode(WIFI_STA);

  // WiFI.begin([ssid], [passkey]) initiates a WiFI connection
  // to the stated [ssid], using the [passkey] as a WPA, WPA2,
  // or WEP passphrase.
  WiFi.begin(WiFiSSID, WiFiPSK);

  // Use the WiFi.status() function to check if the ESP8266
  // is connected to a WiFi network.
  while (WiFi.status() != WL_CONNECTED)
  {
    // Blink the LED
    digitalWrite(LED_PIN, ledStatus); // Write LED high/low
    ledStatus = (ledStatus == HIGH) ? LOW : HIGH;

    // Delays allow the ESP8266 to perform critical tasks
    // defined outside of the sketch. These tasks include
    // setting up, and maintaining, a WiFi connection.
    delay(100);
    // Potentially infinite loops are generally dangerous.
    // Add delays -- allowing the processor to perform other
    // tasks -- wherever possible.
  }
}

void initHardware()
{
  Serial.begin(9600);
  pinMode(DIGITAL_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  // Don't need to set ANALOG_PIN as input, 
  // that's all it can be.
}

int postToPhant()
{
  // LED turns on when we enter, it'll go off when we 
  // successfully post.
  digitalWrite(LED_PIN, HIGH);

  // Declare an object from the Phant library - phant
  Phant phant(PhantHost, PublicKey, PrivateKey);

  // Add the four field/value pairs defined by our stream:
  
  phant.add("distance", distanceString);
  phant.add("temp", tempString);
  phant.add("raw_distance", sensorString);

  // Now connect to data.sparkfun.com, and post our data:
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(PhantHost, httpPort)) 
  {
    // If we fail to connect, return 0.
    return 0;
  }
  // If we successfully connected, print our Phant post:
  client.print(phant.post());

  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
    String line = client.readStringUntil('\r');
    //Serial.print(line); // Trying to avoid using serial
  }

  // Before we exit, turn the LED off.
  digitalWrite(LED_PIN, LOW);

  return 1; // Return success
}





float getTemp(){
 //returns the temperature from one DS18S20 in DEG Celsius

 byte data[12];
 byte addr[8];
 if ( !ds.search(addr)) {
   //no more sensors on chain, reset search
   ds.reset_search();
   return -1000;
 }

 if ( OneWire::crc8( addr, 7) != addr[7]) {
   Serial.println("CRC is not valid!");
   return -1000;
 }

 if ( addr[0] != 0x10 && addr[0] != 0x28) {
   Serial.print("Device is not recognized");
   return -1000;
 }

 ds.reset();
 ds.select(addr);
 ds.write(0x44,1); // start conversion, with parasite power on at the end

 byte present = ds.reset();
 ds.select(addr);  
 ds.write(0xBE); // Read Scratchpad

 
 for (int i = 0; i < 9; i++) { // we need 9 bytes
  data[i] = ds.read();
 }
 
 ds.reset_search();
 
 byte MSB = data[1];
 byte LSB = data[0];

 float tempRead = ((MSB << 8) | LSB); //using two's compliment
 float TemperatureSum = tempRead / 16;
 
 return TemperatureSum;
 
}


