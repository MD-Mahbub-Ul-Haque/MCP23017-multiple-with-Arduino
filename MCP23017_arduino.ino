#include <Wire.h>
#include <Adafruit_MCP23X17.h>

Adafruit_MCP23X17 mcp;

void setup() {
  Serial.begin(9600);
  Serial.println("MCP23017 Serial Control Test!");

  if (!mcp.begin_I2C(0x20)) {
    Serial.println("Error initializing MCP23017 at address 0x20.");
    while (1);
  }

  for (uint8_t pin = 0; pin < 8; pin++) {
    mcp.pinMode(pin, OUTPUT);
    mcp.digitalWrite(pin, HIGH);
  }

  Serial.println("Enter commands in the format Nx or Fx where x is the relay number (0-7).");
}

void loop() {
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    command.trim();

    if (command.length() > 1) {
      char action = command.charAt(0);
      int relay = command.substring(1).toInt();

      if (relay >= 0 && relay < 8) {
        if (action == 'N') {
          mcp.digitalWrite(relay, LOW);
          Serial.print("Relay ");
          Serial.print(relay);
          Serial.println(" turned ON.");
        } else if (action == 'F') {
          mcp.digitalWrite(relay, HIGH);
          Serial.print("Relay ");
          Serial.print(relay);
          Serial.println(" turned OFF.");
        } else {
          Serial.println("Invalid command. Use Nx or Fx where x is the relay number (0-7).");
        }
      } else {
        Serial.println("Invalid relay number. Use 0-7.");
      }
    } else {
      Serial.println("Invalid command format. Use Nx or Fx where x is the relay number (0-7).");
    }
  }
}
