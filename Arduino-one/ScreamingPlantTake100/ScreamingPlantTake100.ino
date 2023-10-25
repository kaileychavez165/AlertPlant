// Playing a digital WAV recording repeatadly using the XTronical DAC Audio library
// prints out to the serial monitor numbers counting up showing that the sound plays 
// independently of the main loop
// See www.xtronical.com for write ups on sound, the hardware required and how to make
// the wav files and include them in your code
//light
#define DHTTYPE DHT11
#include "DHTesp.h"
//Soil moisture sensor O/P pin
const int sensor_pin = 34;
//Speaker sensor pin
const int speaker_pin = 25;
//Variables for soil moisture
int _moisture,sensor_analog; 
//The pin you used for DHT11
const int DHT_PIN = 4;
//DHTesp object
DHTesp mySensor;
//SD object
//SdFat sd;
// Audio player
//TMRpcm audio;

#include "avatarWater.h";
#include "XT_DAC_Audio.h";

XT_DAC_Audio_Class DacAudio(speaker_pin,0);    // Create the main player class object. 
                                      // Use GPIO 25, one of the 2 DAC pins and timer 0
                                      
XT_Wav_Class PlantWater(AvatarWater_wav);   // create an object of type XT_Wav_Class that is used by 
                                      // the dac audio class (above), passing wav data as parameter.
                                      

uint32_t DemoCounter=0;               // Just a counter to use in the serial monitor
                                      // not essential to playing the sound

void setup() {
  Serial.begin(115200);               // Not needed for sound, just to demo printing to the serial
                                      // Monitor whilst the sound plays, ensure your serial monitor
                                     // speed is set to this speed also.
                                       //Setup for the DHT11 sensor
  mySensor.setup(DHT_PIN, DHTesp::DHT11);
  //Turning on soil moisture sensor
  pinMode(sensor_pin, INPUT);
  //Checking the SD card
  PlantWater.RepeatForever=true;        // Keep on playing sample forever!!!
  DacAudio.Play(&PlantWater);   
}


void loop() {
  DacAudio.FillBuffer();              // Fill the sound buffer with data
  Serial.println(DemoCounter++);      // Showing that the sound will play as well as your code running here.
  TempAndHumidity data = mySensor.getTempAndHumidity();
  //Reading from soil moisture sensor  
  sensor_analog = analogRead(sensor_pin);
  //Readable data for moisture
  //_moisture = ( 100 - ( (sensor_analog/4095.00) * 100 ) );
  //_moisture = map(sensor_analog,550,0,0,100);

  //Will print the temperature
  //Serial.println("Temp " + String(data.temperature, 2) + "°C");
  //Will print the humidity
  //Serial.println("Humidity " + String(data.humidity, 2) + "%");
  //Will print the moisture
  //Serial.print("Moisture: ");
  //Serial.println(_moisture);
  //Delay of 2 secs
  //delay(2000);

  //if temp conditions are met everything is good
  /*
  if((data.temperature < 70) && (data.temperature > 15))
  {
    Serial.println("Temp good");
    delay(2000);
  }
  //Doesn't meet conditions for temp
  else
  {
    delay(1000); //wait a second 
    Serial.println("Temp wrong!!");
              // Set to play
  }
  if ((data.humidity > 30) && (data.humidity < 90))
  {
    delay(2000); //wait a second 
    Serial.println("Humidity good");  
  }
  //Conditions for humidity are not met
  else
  {
    Serial.println("Humidity wrong!!");
    //DacAudio.Play(&PlantWater);           // Set to play
  }
  
  //If moisture conditions are met everything is good

  if ((_moisture > 0) && (_moisture < 57 ))
  {
    Serial.println("Moisture good");
    delay(2000);
  }
  //Conditions for moisture are not met
  else if (_moisture = 0)
  {
    Serial.println("Moisture wrong!!");
            // Set to play
  }
  */
 
  
}
