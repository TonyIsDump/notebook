#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10  // Slave Select pin
#define RST_PIN 9  // Reset pin

MFRC522 rfid(SS_PIN, RST_PIN);  // Create MFRC522 instance

bool isCardPresent() {
  byte atqa_answer[2];
  byte atqa_size = 2;
  MFRC522::StatusCode result = rfid.PICC_WakeupA(atqa_answer, &atqa_size);
  return (result == MFRC522::STATUS_OK || result == MFRC522::STATUS_COLLISION);
}

void setup() {
  Serial.begin(9600);  // Initialize serial communication
  SPI.begin();         // Initialize SPI bus
  rfid.PCD_Init();     // Initialize MFRC522 RFID reader
  Serial.println("Scan an RFID card...");
}

void loop() {
  if (!isCardPresent()) {
    return;
  }

  if (!rfid.PICC_ReadCardSerial()) {
    return;
  }

  bool isFirst = (rfid.uid.size == 4 &&
                  rfid.uid.uidByte[0] == 227 &&
                  rfid.uid.uidByte[1] == 79 &&
                  rfid.uid.uidByte[2] == 192 &&
                  rfid.uid.uidByte[3] == 41);

  bool isSecond = (rfid.uid.size == 4 &&
                   rfid.uid.uidByte[0] == 163 &&
                   rfid.uid.uidByte[1] == 66 &&
                   rfid.uid.uidByte[2] == 225 &&
                   rfid.uid.uidByte[3] == 14);

  if (isFirst) {
    while (true) {
      Serial.println("1");
      delay(500);  // Adjust this delay to change how frequently "1" is printed

      rfid.PICC_HaltA();

      if (!isCardPresent()) {
        break;
      }

      if (!rfid.PICC_ReadCardSerial()) {
        break;
      }

      // Recheck if it's still the same card
      if (!(rfid.uid.size == 4 &&
            rfid.uid.uidByte[0] == 227 &&
            rfid.uid.uidByte[1] == 79 &&
            rfid.uid.uidByte[2] == 192 &&
            rfid.uid.uidByte[3] == 41)) {
        rfid.PICC_HaltA();  // Halt the new (different) card
        break;
      }
    }
  } else if (isSecond) {
    Serial.println("2");
    rfid.PICC_HaltA();
    // Wait for the card to be removed to prevent repeated printing
    while (isCardPresent()) {
      delay(100);
    }
  } else {
    Serial.println("denied");
    rfid.PICC_HaltA();
    // Wait for the card to be removed to prevent repeated printing
    while (isCardPresent()) {
      delay(100);
    }
  }
}