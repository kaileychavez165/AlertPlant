#include "FS.h"
#include <SdFat.h>
#include <FreeStack.h>

//object of SdFat
SdFat SD;

void setup() {
  // Start Serial communication
  Serial.begin(115200);

  // Checking SD card
  if (!SD.begin(5)) 
  { // Pin 5 is used for CS
    Serial.println("Failed to initialize SD card!");
    while (true);
  }
  //worked
  Serial.println("SD card initialized.");

  // Initialize audio
  Audio.begin(88200, 100); // Sample rate and buffer size

}

void loop() {
  int count = 0;

  // Open wave file from SD card
  File myFile = SD.open("plantS.wav");

  if (!myFile) {
    Serial.println("Error opening plantS.wav");
    while (true);
  }
  // Number of samples to read in a block
  const int S = 1024;
  short buffer[S];

  Serial.print("Playing");

  while (myFile.available()) {
    myFile.read((uint8_t*)buffer, sizeof(buffer));

    int volume = 1024;
    Audio.prepare(buffer, S, volume);
    Audio.write(buffer, S);

    count++;
    if (count == 100) {
      Serial.print(".");
      count = 0;
    }
  }

  myFile.close();
  Audio.end();
  Serial.println("End of file. Thank you for listening!");
  while (true);
}
