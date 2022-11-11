// #include "Zigbee.h"
#include "Button.h"
#include <XBee.h>
#include "XBeeConfig.h"
#include <Printers.h>
#include <SoftwareSerial.h>
#include "support.h"

#define IO_XBEE_RX 2
#define IO_XBEE_TX 3
#define IO_PB 4
#define IO_LED 5

XBee xbee;
SoftwareSerial xbeeSerial(IO_XBEE_RX, IO_XBEE_TX);
Button pb(IO_PB);

void setup()
{
    while (!Serial);

    LOG("Serial ready");

    pinMode(IO_PB, INPUT);
    pinMode(IO_LED, OUTPUT);

    pinMode(IO_XBEE_RX, INPUT);
    pinMode(IO_XBEE_TX, OUTPUT);

    xbeeSerial.begin(9600);

    LOG("Running configuration");

    XBeeConfig xbeeConfig;
    xbeeConfig.setup(xbeeSerial);

    xbee.begin(xbeeSerial);
}

int lastMode = 0;
bool lastLed;

void loop()
{
    if (pb.clicked()) {
        lastLed = !lastLed;
        digitalWrite(IO_LED, lastLed);
    }
}