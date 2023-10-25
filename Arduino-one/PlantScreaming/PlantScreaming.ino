#include "DHTesp.h"
#include "SdFat.h"
#include "XT_DAC_Audio.h";
//#include "TMRpcm.h"
//Clock speed
#define SPI_SPEED SD_SCK_MHZ(4)
//Your pin used for the SD card
#define CS_PIN 5
//light
#define DHTTYPE DHT11
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
SdFat sd;
// Audio player
//TMRpcm audio;

void setup()
{
  //Serial Monitor
  Serial.begin(115200);
  //Setup for the DHT11 sensor
  mySensor.setup(DHT_PIN, DHTesp::DHT11);

  //Turning on soil moisture sensor
  pinMode(sensor_pin, INPUT);
  //Checking the SD card
  
  // put your setup code here, to run once:
  Serial.begin(115200);
  if (!sd.begin(CS_PIN, SPI_SPEED)) {
    if (sd.card()->errorCode()) {
      Serial.println("SD initialization failed.");
    } else if (sd.vol()->fatType() == 0) {
      Serial.println("Can't find a valid FAT16/FAT32 partition.");
    } else {
      Serial.println("Can't determine error type");
    }
    return;
  }
  Serial.println("Files on card:");
  Serial.println("   Size    Name");

  sd.ls(LS_R | LS_SIZE);
  }
  // Initialize the speaker
  //audio.speakerPin = speaker_pin;



void loop()
{
  // put your main code here, to run repeatedly:

  //Will get the reading from DHT11
  TempAndHumidity data = mySensor.getTempAndHumidity();
  //Reading from soil moisture sensor  
  sensor_analog = analogRead(sensor_pin);
  //Readable data for moisture
  _moisture = ( 100 - ( (sensor_analog/4095.00) * 100 ) );
  //_moisture = map(sensor_analog,550,0,0,100);

  //Will print the temperature
  Serial.println("Temp " + String(data.temperature, 2) + "°C");
  //Will print the humidity
  Serial.println("Humidity " + String(data.humidity, 2) + "%");
  //Will print the moisture
  Serial.print("Moisture: ");
  Serial.println(_moisture);
  //Delay of 2 secs
  delay(2000);

  //if temp conditions are met everything is good
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
  }
    //audio.play("ScreamingPlant.m4a");


      // Soil is dry, take appropriate action (e.g., water the plant)
      //To open the file and play
      //audio = sd.open("ScreamingPlant.m4a"); //Put actual file name
      //opening the file
      //if(audio) 
      //{
      //while there is that file
        //while(audio.available()) 
        
        //Play the audio
        //Serial.println(audio.read());
        //Delay of 5 seconds
        //delay(500);
        //}
      //} 
      

  //if temp conditions for humidity are met everything is good
  if ((data.humidity > 30) && (data.humidity < 90))
  {
    delay(2000); //wait a second 
    Serial.println("Humidity good");  
  }
  //Conditions for humidity are not met
  else
  {
    Serial.println("Humidity wrong!!");
  }
  //If moisture conditions are met everything is good
  if ((_moisture > 0) && (_moisture < 57 ))
  {
    Serial.println("Moisture good");
    delay(2000);
  }
  //Conditions for moisture are not met
  else
  {
    Serial.println("Moisture wrong!!");
  }
   
}

  

