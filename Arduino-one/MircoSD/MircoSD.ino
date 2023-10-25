#include <MusicDefinitions.h>
#include <XT_DAC_Audio.h>
#include "FS.h"
#include "SdFat.h"

#define SPI_SPEED SD_SCK_MHZ(5)
#define CS_PIN 5


SdFat sd;
String myFile;

XT_DAC_Audio_Class DacAudio(25,0);    // Create the main player class object. 
                                      // Use GPIO 25, one of the 2 DAC pins and timer 0
                            

void setup() {
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
  //Serial.print(file.name());

  sd.ls(LS_R | LS_SIZE);
  //myFile = "plantS.h"
  
  //XT_Wav_Class plantScream(myFile.c_str()); // Create an object of type XT_Wav_Class

  //audio.play("plantS.wav");    plays a file

  
}

void loop() {
  // put your main code here, to run repeatedly:
 // DacAudio.Play(&StarWars);           // Set to play
}
