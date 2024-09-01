#include <NTPClient.h>
// change next line to use with another board/shield
#include <ESP8266WiFi.h>
// #include <WiFi.h> // for WiFi shield
// #include <WiFi101.h> // for WiFi 101 shield or MKR1000
#include <WiFiUdp.h>
#include "../secret.h"

// const char *ssid     = "<SSID>";
// const char *password = "<PASSWORD>";

WiFiUDP ntpUDP;

// You can specify the time server pool and the offset (in seconds, can be
// changed later with setTimeOffset() ). Additionally you can specify the
// update interval (in milliseconds, can be changed using setUpdateInterval() ).
NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", 10800, 300000);

void setup()
{
  Serial.begin(115200);

  WiFi.begin(SSID, PASS);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  timeClient.begin();
}

void loop()
{
  timeClient.update();
  unsigned long epoch = timeClient.getEpochTime() - millis() / 1000;
  Serial.println();
  Serial.print(timeClient.getFormattedDate(epoch));
  Serial.print("\t");
  Serial.print(timeClient.getFormattedTime(epoch));
  Serial.print("\t");
  Serial.println(timeClient.getDurationOfWork(1725153560 - 600 - 15));

  delay(1000);
}
