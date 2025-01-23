#include <Arduino.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <RTClib.h>
#include <SPI.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);
RTC_DS3231 rtc;

int currentHour;
int currentMinute;

void setup()
{
	// initialize the LCD
	lcd.init();
  rtc.begin();
  if(rtc.lostPower()){
    rtc.adjust(DateTime((__DATE__), (__TIME__)));
  }
	lcd.backlight();
}

void zeroPadding(){
  lcd.print("0");  
}

void loop()
{
  DateTime timeNow = rtc.now();
  lcd.setCursor(0,0);
  if(timeNow.hour() != currentHour){
    if(timeNow.hour()<10){
      zeroPadding();
      lcd.print(timeNow.hour());  
    }else{
      lcd.print(timeNow.hour());
    }
    currentHour = timeNow.hour();
  }

  lcd.setCursor(2,0);
  lcd.print(":");

  if(timeNow.minute() != currentMinute){
    if(timeNow.minute()<10){
      zeroPadding();
      lcd.print(timeNow.minute());   
    }else{
      lcd.print(timeNow.minute());
    }
    currentMinute = timeNow.minute();
  }

  lcd.setCursor(5,0);
  lcd.print(":");

  if(timeNow.second()<10){
    zeroPadding();
    lcd.print(timeNow.second());  
  }else{
    lcd.print(timeNow.second());
  }

	// Do nothing here...
}