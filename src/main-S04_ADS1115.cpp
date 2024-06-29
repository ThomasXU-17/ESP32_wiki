#include <Arduino.h>
#include <Adafruit_ADS1X15.h>

Adafruit_ADS1115 ads0;  /* ADS1115 for the 16-bit version */
Adafruit_ADS1115 ads1;  

float voltage2pressure(float voltage, float v_min=500, float v_max=4500, float p_min=-40000, float p_max=40000)
{
  return (voltage - v_min) * (p_max - p_min) / (v_max - v_min) + p_min;
}

void setup()
{
  pinMode(1, INPUT);
  Serial.begin(115200);
  Serial.println("Hello!");

  Serial.println("Getting single-ended readings from AIN0..3");
  Serial.println("ADC Range: +/- 6.144V (1 bit = 3mV/ADS1015, 0.1875mV/ADS1115)");

  // The ADC input range (or gain) can be changed via the following
  // functions, but be careful never to exceed VDD +0.3V max, or to
  // exceed the upper and lower limits if you adjust the input range!
  // Setting these values incorrectly may destroy your ADC!
  //                                                                ADS1015  ADS1115
  //                                                                -------  -------
  // ads.setGain(GAIN_TWOTHIRDS);  // 2/3x gain +/- 6.144V  1 bit = 3mV      0.1875mV (default)
  ads0.setGain(GAIN_ONE);        // 1x gain   +/- 4.096V  1 bit = 2mV      0.125mV
  // ads.setGain(GAIN_TWO);        // 2x gain   +/- 2.048V  1 bit = 1mV      0.0625mV
  // ads.setGain(GAIN_FOUR);       // 4x gain   +/- 1.024V  1 bit = 0.5mV    0.03125mV
  // ads.setGain(GAIN_EIGHT);      // 8x gain   +/- 0.512V  1 bit = 0.25mV   0.015625mV
  // ads.setGain(GAIN_SIXTEEN);    // 16x gain  +/- 0.256V  1 bit = 0.125mV  0.0078125mV

  if (!ads0.begin(0x48, &Wire)) {
    Serial.println("Failed to initialize ADS0.");
    while (1);
  }

  if (!ads1.begin(0x49, &Wire)) {
    Serial.println("Failed to initialize ADS1.");
    while (1);
  }
}

void loop()
{
  int16_t adc0_0, adc0_1, adc0_2, adc0_3, adc1_0, adc1_1, adc1_2, adc1_3;
  float volts0_0, volts0_1, volts0_2, volts0_3, volts1_0, volts1_1, volts1_2, volts1_3;

  adc0_0 = ads0.readADC_SingleEnded(0);
  adc0_1 = ads0.readADC_SingleEnded(1);
  adc0_2 = ads0.readADC_SingleEnded(2);
  adc0_3 = ads0.readADC_SingleEnded(3);
  adc1_0 = ads1.readADC_SingleEnded(0);
  adc1_1 = ads1.readADC_SingleEnded(1);
  adc1_2 = ads1.readADC_SingleEnded(2);
  adc1_3 = ads1.readADC_SingleEnded(3);

  volts0_0 = ads0.computeVolts(adc0_0);
  volts0_1 = ads0.computeVolts(adc0_1);
  volts0_2 = ads0.computeVolts(adc0_2);
  volts0_3 = ads0.computeVolts(adc0_3);
  volts1_0 = ads1.computeVolts(adc1_0);
  volts1_1 = ads1.computeVolts(adc1_1);
  volts1_2 = ads1.computeVolts(adc1_2);
  volts1_3 = ads1.computeVolts(adc1_3);

  Serial.println("-----------------------------------------------------------");
  // Serial.print(">AIN0_0: "); Serial.println(adc0_0, 5);
  // Serial.print(">AIN0_1: "); Serial.println(adc0_1, 5); 
  // Serial.print(">AIN0_2: "); Serial.println(adc0_2, 5); 
  // Serial.print(">AIN0_3: "); Serial.println(adc0_3, 5); 
  Serial.print(">V0_0: "); Serial.println(volts0_0, 5);
  // Serial.print(">V0_1: "); Serial.println(volts0_1, 5); 
  // Serial.print(">V0_2: "); Serial.println(volts0_2, 5); 
  // Serial.print(">V0_3: "); Serial.println(volts0_3, 5); 
  // Serial.println("-----------------------------------------------------------");
  // Serial.print(">AIN1_0: "); Serial.println(adc1_0, 5);
  // Serial.print(">AIN1_1: "); Serial.println(adc1_1, 5);
  // Serial.print(">AIN1_2: "); Serial.println(adc1_2, 5);
  // Serial.print(">AIN1_3: "); Serial.println(adc1_3, 5);
  Serial.print(">V1_0: "); Serial.println(volts1_0, 5);
  // Serial.print(">V1_1: "); Serial.println(volts1_1, 5);
  // Serial.print(">V1_2: "); Serial.println(volts1_2, 5);
  // Serial.print(">V1_3: "); Serial.println(volts1_3, 5);
  // Serial.println("-----------------------------------------------------------");
  float p0 = voltage2pressure(volts0_0*1000.0);
  float p1 = voltage2pressure(volts1_0*1000.0);
  Serial.print(">P_ADS1115_0: "); Serial.println(p0, 5);
  Serial.print(">P_ADS1115_1: "); Serial.println(p1, 5);
  Serial.print(">P_DIFF: "); Serial.println(p0-p1, 5);

  uint32_t esp32adc = analogReadMilliVolts(1);
  Serial.print(">ESP32 ADC: "); Serial.println(esp32adc/1000.0, 5);
  Serial.print(">P_ESP32: "); Serial.println(voltage2pressure(esp32adc), 5);
  delay(20);
}