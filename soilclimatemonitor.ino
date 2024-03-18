// This #include statement was automatically added by the Particle IDE.
#include <SparkFun_Qwiic_Humidity_AHT20.h>

//Once your code is uploaded, open the serial monitor in the Arduino app to see the data come through

#include <Wire.h>
#define SOILPIN A0

AHT20 humiditySensor;
int fan = D4; 

void setup()
{
  pinMode(fan, OUTPUT);
  Serial.begin(9600);
  Serial.println("Qwiic Humidity AHT20 examples");

  Wire.begin(); //Join I2C bus

  //Check if the AHT20 will acknowledge
  if (humiditySensor.begin() == false)
  {
    Serial.println("AHT20 not detected. Please check wiring. Freezing.");
    while (1);
  }
  Serial.println("AHT20 acknowledged.");
}

void loop()
{
  //If a new measurement is available
  if (humiditySensor.available() == true)
  {
    //Get the new temperature and humidity value
    float temperature = humiditySensor.getTemperature();
    float degreesF = (temperature * 1.8 + 32);
    float humidity = humiditySensor.getHumidity();
    int analogValue = analogRead(SOILPIN);       // read  sensor
    int moist = map(analogValue, 3300, 1500, 0, 100);
    
    Particle.publish("sensorReading", (String)degreesF + ":" + (String)humidity + ":" + (String)moist);

    //Print the results
    Serial.print("Temperature: ");
    Serial.print(temperature, 2);
    Serial.print(" C\t");
    Serial.print("Temperature: ");
    Serial.print(degreesF, 2);
    Serial.print(" F\t");
    Serial.print("Humidity: ");
    Serial.print(humidity, 2);
    Serial.print("% RH");
    Serial.println();
    Serial.print("Analog Value: ");
    Serial.println(analogValue);
    Serial.print("Moisture Value: ");
    Serial.println(moist);
      
    if (degreesF > 80)
    {
        digitalWrite(fan, HIGH);
    }
    else {
        digitalWrite(fan, LOW);
    }
  }
 
        
  //The AHT20 can respond with a reading every ~50ms. However, increased read time can cause the IC to heat around 1.0C above ambient.
  //The datasheet recommends reading every 2 seconds.
  delay(2000);
}
