#include "SdFat.h"
#include "FS.h"

// Define pins for microSD card reader
#define SD_CS 5
#define SD_SCK 18
#define SD_MISO 19
#define SD_MOSI 23

// Define pins for DAC (Digital-to-Analog Converter) output
// DAC1 on ESP32
#define DAC_PIN 25

// Create an instance of the SdFat library
SdFat SD;

// Create an instance of the SdFile class
SdFile audioFile;

void setup() {
  // Serial Monitor
  Serial.begin(115200);

  // Checking microSD card
  if (!SD.begin(SD_CS, SD_SCK, SD_MISO, SD_MOSI)) {
    Serial.println("Card Mount Failed");
    return;
  }

  // Opens the audio file
  audioFile.open("plantS.wav", FILE_READ);
  if (!audioFile.isOpen()) {
    Serial.println("Failed to open file");
  }

  // Enabling DAC1 on ESP32
  dacWrite(DAC_PIN, 0);
}

void loop() {
  if (audioFile) {
    // Reads audio data and sends it to the DAC
    uint16_t sample;
    
    // It reads 2 bytes (16 bits) at a time
    // and then it sends each sample to the DAC
    while (audioFile.read(&sample, 2) == 2) {
      dacWrite(DAC_PIN, sample);
    }

    // Closes the file when finished
    audioFile.close();
  }
}
