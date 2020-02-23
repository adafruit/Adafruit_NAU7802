/**************************************************************************/
/**
  @file     Adafruit_NAU7802.h

  Author: Limor Fried (Adafruit Industries)
  License: BSD (see license.txt)

  This is a library for the Adafruit NAU7802 I2C ADC breakout board
  ----> http://www.adafruit.com/products/4538

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

*/
/**************************************************************************/
#include <Adafruit_I2CDevice.h>
#include <Adafruit_I2CRegister.h>
#include <Arduino.h>
#include <Wire.h>

/** Default NAU7802 I2C address. */
#define NAU7802_I2CADDR_DEFAULT 0x2A ///< I2C address
#define NAU7802_PU_CTRL 0x00         ///< Power control register
#define NAU7802_CTRL1 0x01           ///< Control/config register #1
#define NAU7802_CTRL2 0x02           ///< Control/config register #2
#define NAU7802_ADCO_B2 0x12         ///< ADC ouput LSB
#define NAU7802_ADC 0x15             ///< ADC / chopper control
#define NAU7802_PGA 0x1B             ///< PGA control
#define NAU7802_POWER 0x1C           ///< power control
#define NAU7802_REVISION_ID 0x1F     ///< Chip revision ID

/*! The possible LDO voltages */
typedef enum _ldovoltages {
  NAU7802_4V5,
  NAU7802_4V2,
  NAU7802_3V9,
  NAU7802_3V6,
  NAU7802_3V3,
  NAU7802_3V0,
  NAU7802_2V7,
  NAU7802_2V4,
  NAU7802_EXTERNAL,
} NAU7802_LDOVoltage;

/*! The possible gains */
typedef enum _gains {
  NAU7802_GAIN_1,
  NAU7802_GAIN_2,
  NAU7802_GAIN_4,
  NAU7802_GAIN_8,
  NAU7802_GAIN_16,
  NAU7802_GAIN_32,
  NAU7802_GAIN_64,
  NAU7802_GAIN_128,
} NAU7802_Gain;

/*! The possible sample rates */
typedef enum _sample_rates {
  NAU7802_RATE_10SPS = 0,
  NAU7802_RATE_20SPS = 1,
  NAU7802_RATE_40SPS = 2,
  NAU7802_RATE_80SPS = 3,
  NAU7802_RATE_320SPS = 7,
} NAU7802_SampleRate;

/*! The possible calibration modes */
typedef enum _calib_mode {
  NAU7802_CALMOD_INTERNAL = 0,
  NAU7802_CALMOD_OFFSET = 2,
  NAU7802_CALMOD_GAIN = 3,
} NAU7802_Calibration;

/**************************************************************************/
/*!
    @brief  NAU7802 driver.
*/
/**************************************************************************/
class Adafruit_NAU7802 {
public:
  Adafruit_NAU7802();
  bool begin(TwoWire *theWire = &Wire);
  bool reset(void);
  bool enable(bool flag);
  bool available(void);
  int32_t read(void);

  bool setLDO(NAU7802_LDOVoltage voltage);
  NAU7802_LDOVoltage getLDO(void);
  bool setGain(NAU7802_Gain gain);
  NAU7802_Gain getGain(void);
  bool setRate(NAU7802_SampleRate gain);
  NAU7802_SampleRate getRate(void);
  bool calibrate(NAU7802_Calibration mode);

private:
  Adafruit_I2CRegister *_pu_ctrl_reg = NULL;
  Adafruit_I2CDevice *i2c_dev = NULL;
};
