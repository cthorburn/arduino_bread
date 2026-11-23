#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DS3231.h>
#include <time.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_RESET     -1
#define OLED_ADDRESS 0x3c // See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
DS3231 myRTC;

uint16_t presses = 0;
uint8_t state_B1 = LOW;
uint8_t state_B2 = LOW;
uint8_t state_B3 = LOW;
uint8_t state_B4 = LOW;

#define FAN_PIN 11
#define HEATER_PIN 12
#define B1_PIN 9
#define B2_PIN 8
#define B3_PIN 7
#define B4_PIN 6
#define BUZZ_PIN 10

#define ON HIGH
#define OFF LOW

#define TC74_ADDR 0b1001101

// #define FOR_EACH_BUTTON(i) for(int (i) = 4; (i) < 8 ; (i)++)


// uint8_t lastState[4] = {LOW, LOW, LOW, LOW};
// void setupscan();

// void loopscan();

// void heaterOn();
// void heaterOff();
// void fan(uint8_t onoff);
int getTemp();

void buzz();
void setup() {
  Serial.begin(115200);

  unsigned int theDate = myRTC.getDate();

  pinMode(BUZZ_PIN, OUTPUT);

  tone(BUZZ_PIN, 85); //Set the voltage to high and makes a noise
  delay(1000);//Waits for 1000 milliseconds
  noTone(BUZZ_PIN);//Sets the voltage to low and makes no noise
  delay(1000);//Waits for 1000 milliseconds

  // setupscan();
  // return;

  // pinMode(FAN_PIN, OUTPUT);
  // pinMode(HEATER_PIN, OUTPUT);

  // pinMode(B1_PIN, INPUT);
  // pinMode(B2_PIN, INPUT);
  // pinMode(B3_PIN, INPUT);
  // pinMode(B4_PIN, INPUT);



  if(!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  delay(2000);
  
  display.clearDisplay();
  delay(2000);

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(2, 2);
  display.println("Welcome " + myRTC.getYear() ); 
  display.display();
  delay(2000);
  
  display.setCursor(2, 10);
  display.println("Temp: " + getTemp() ); 
  display.display();






  Serial.begin(9600);
}



void loop() {
  // for(;;) {
  //   delay(3000);
  //   heaterOn();
  //   delay(10000);
  //   heaterOff();
  // }
}

int getTemp() {
    Wire.beginTransmission(TC74_ADDR);
//start the transmission

  int temperature;
  Wire.write(0);

  Wire.requestFrom(TC74_ADDR, 1);
  if (Wire.available()) {
    temperature = Wire.read();
    Serial.println(temperature);
  }

  return temperature;

}

// void fan(uint8_t onoff) {
//   digitalWrite(FAN_PIN, onoff);
// }

// void heaterOn() {
//   fan(ON);
//   delay(2000);
//   digitalWrite(HEATER_PIN, HIGH);
// }

// void heaterOff() {
//   digitalWrite(HEATER_PIN, LOW);
//   delay(5000);
//   fan(OFF);
// }



// void loopx() {

//   FOR_EACH_BUTTON(i) {
//     uint8_t btnIdx = i - 2;
//     if(lastState[btnIdx] != digitalRead(i)) {
//       lastState[btnIdx] = lastState[btnIdx] == LOW ? HIGH : LOW; 
//       Serial.print("Button : ");
//       Serial.print(btnIdx);
//       Serial.print(" new state: ");
//       Serial.println( lastState[btnIdx] == LOW ? "OFF" : "ON");
//     }
//   }
// }

// void testdrawline() {
//   int16_t i;

//   display.clearDisplay(); // Clear display buffer

//   for(i=0; i<display.width(); i+=4) {
//     display.drawLine(0, 0, i, display.height()-1, SSD1306_WHITE);
//     display.display(); // Update screen with each newly-drawn line
//     delay(1);
//   }
//   for(i=0; i<display.height(); i+=4) {
//     display.drawLine(0, 0, display.width()-1, i, SSD1306_WHITE);
//     display.display();
//     delay(1);
//   }
//   delay(250);

//   display.clearDisplay();

//   for(i=0; i<display.width(); i+=4) {
//     display.drawLine(0, display.height()-1, i, 0, SSD1306_WHITE);
//     display.display();
//     delay(1);
//   }
//   for(i=display.height()-1; i>=0; i-=4) {
//     display.drawLine(0, display.height()-1, display.width()-1, i, SSD1306_WHITE);
//     display.display();
//     delay(1);
//   }
//   delay(250);

//   display.clearDisplay();

//   for(i=display.width()-1; i>=0; i-=4) {
//     display.drawLine(display.width()-1, display.height()-1, i, 0, SSD1306_WHITE);
//     display.display();
//     delay(1);
//   }
//   for(i=display.height()-1; i>=0; i-=4) {
//     display.drawLine(display.width()-1, display.height()-1, 0, i, SSD1306_WHITE);
//     display.display();
//     delay(1);
//   }
//   delay(250);

//   display.clearDisplay();

//   for(i=0; i<display.height(); i+=4) {
//     display.drawLine(display.width()-1, 0, 0, i, SSD1306_WHITE);
//     display.display();
//     delay(1);
//   }
//   for(i=0; i<display.width(); i+=4) {
//     display.drawLine(display.width()-1, 0, i, display.height()-1, SSD1306_WHITE);
//     display.display();
//     delay(1);
//   }

//   delay(2000); // Pause for 2 seconds
// }

// void testdrawrect(void) {
//   display.clearDisplay();

//   for(int16_t i=0; i<display.height()/2; i+=2) {
//     display.drawRect(i, i, display.width()-2*i, display.height()-2*i, SSD1306_WHITE);
//     display.display(); // Update screen with each newly-drawn rectangle
//     delay(1);
//   }

//   delay(2000);
// }




// void setupscan()
// {
//   Wire.begin();
 
//   Serial.begin(9600);
//   while (!Serial);             // Leonardo: wait for serial monitor
//   Serial.println("\nI2C Scanner");
// }
 
 
// void loopscan()
// {
//   byte error, address;
//   int nDevices;
 
//   Serial.println("Scanning....");
 
//   nDevices = 0;
//   for(address = 1; address < 127; address++ )
//   {
//     // The i2c_scanner uses the return value of
//     // the Write.endTransmisstion to see if
//     // a device did acknowledge to the address.
//     Wire.beginTransmission(address);
//     error = Wire.endTransmission();
    
//     if (address<16)
//       Serial.print("0");
    
//     Serial.print(address,HEX);

//     if (error == 0) {
//       Serial.println(": I2C device found");
//       nDevices++;
//     }  
//     else
//       Serial.println(": Unknown error");
    
//   }

//   if (nDevices == 0) 
//     Serial.println("No I2C devices found\n");
//   else
//     Serial.println("done\n");
 
//   delay(5000);           // wait 5 seconds for next scan
// }

