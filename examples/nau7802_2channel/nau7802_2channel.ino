#include <Adafruit_NAU7802.h>

Adafruit_NAU7802 nau;

bool channel1 = true;

void setup() {
  Serial.begin(115200);
  delay(1000); //wait for monitor to be opened
  Serial.println("NAU7802");
  while (! nau.begin()) {
    Serial.println("Failed to find NAU7802");
    delay(1000);
  }
  Serial.println("Found NAU7802, disabling PGA cap for 2 channel operation");
  nau.setPGACap(NAU7802_CAP_OFF);
  
  nau.setLDO(NAU7802_2V7);
  Serial.print("LDO voltage set to ");
  switch (nau.getLDO()) {
    case NAU7802_4V5:  Serial.println("4.5V"); break;
    case NAU7802_4V2:  Serial.println("4.2V"); break;
    case NAU7802_3V9:  Serial.println("3.9V"); break;
    case NAU7802_3V6:  Serial.println("3.6V"); break;
    case NAU7802_3V3:  Serial.println("3.3V"); break;
    case NAU7802_3V0:  Serial.println("3.0V"); break;
    case NAU7802_2V7:  Serial.println("2.7V"); break;
    case NAU7802_2V4:  Serial.println("2.4V"); break;
    case NAU7802_EXTERNAL:  Serial.println("External"); break;
  }

  nau.setGain(NAU7802_GAIN_128);
  Serial.print("Gain set to ");
  switch (nau.getGain()) {
    case NAU7802_GAIN_1:  Serial.println("1x"); break;
    case NAU7802_GAIN_2:  Serial.println("2x"); break;
    case NAU7802_GAIN_4:  Serial.println("4x"); break;
    case NAU7802_GAIN_8:  Serial.println("8x"); break;
    case NAU7802_GAIN_16:  Serial.println("16x"); break;
    case NAU7802_GAIN_32:  Serial.println("32x"); break;
    case NAU7802_GAIN_64:  Serial.println("64x"); break;
    case NAU7802_GAIN_128:  Serial.println("128x"); break;
  }

  nau.setRate(NAU7802_RATE_320SPS);
  Serial.print("Conversion rate set to ");
  switch (nau.getRate()) {
    case NAU7802_RATE_10SPS:  Serial.println("10 SPS"); break;
    case NAU7802_RATE_20SPS:  Serial.println("20 SPS"); break;
    case NAU7802_RATE_40SPS:  Serial.println("40 SPS"); break;
    case NAU7802_RATE_80SPS:  Serial.println("80 SPS"); break;
    case NAU7802_RATE_320SPS:  Serial.println("320 SPS"); break;
  }

  // Take 10 readings to flush out readings
  for (uint8_t i=0; i<10; i++) {
    while (! nau.available()) delay(1);
    nau.read();
  }

  while (! nau.calibrate(NAU7802_CALMOD_INTERNAL)) {
    Serial.println("Failed to calibrate internal offset, retrying!");
    delay(1000);
  }
  Serial.println("Calibrated internal offset");

  while (! nau.calibrate(NAU7802_CALMOD_OFFSET)) {
    Serial.println("Failed to calibrate system offset, retrying!");
    delay(1000);
  }
  Serial.println("Calibrated system offset");
}

void loop() {
  static int32_t val1 = 0;
  static int32_t val2 = 0;
  //interleave between channel 1 & 2
  if(channel1) {
    //wait for available data on channel 1 & read
    while (!nau.available()) delayMicroseconds(500);
    val1 = nau.read();
    //switch to channel 2
    nau.setChannel(NAU7802_CHANNEL2);
    channel1 = false;
  } else {
    //wait for available data on channel 2 & read
    while (!nau.available()) delayMicroseconds(500);
    val2 = nau.read();
  
    //switch back to channel 1
    nau.setChannel(NAU7802_CHANNEL1);
    channel1 = true;
  }
  Serial.print("Read: "); Serial.print(val1); Serial.print(","); Serial.println(val2);
}
