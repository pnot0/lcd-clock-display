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
int currentDay;
int currentMonth;
int currentYear;
int currentDOW;

byte sDay[] = {
  0x0F,
  0x10,
  0x10,
  0x0E,
  0x01,
  0x01,
  0x1E,
  0x15
};

byte mDay[] = {
  0x11,
  0x1B,
  0x15,
  0x15,
  0x11,
  0x11,
  0x11,
  0x15
};

byte tDay[] = {
  0x1F,
  0x04,
  0x04,
  0x04,
  0x04,
  0x04,
  0x04,
  0x15
};

byte wDay[] = {
  0x11,
  0x11,
  0x11,
  0x11,
  0x15,
  0x15,
  0x0A,
  0x15
};

byte fDay[] = {
  0x1F,
  0x10,
  0x10,
  0x1E,
  0x10,
  0x10,
  0x10,
  0x15
};

byte celsiusChar[] = {
  0x0E,
  0x15,
  0x12,
  0x10,
  0x10,
  0x11,
  0x0E,
  0x00
};

byte humidityChar[] = {
  0x18,
  0x19,
  0x02,
  0x04,
  0x08,
  0x12,
  0x07,
  0x02
};

void setup()
{
	// initialize the LCD
	lcd.init();
  rtc.begin();
  if(rtc.lostPower()){
    rtc.adjust(DateTime((__DATE__), (__TIME__)));
  }
	lcd.backlight();

  lcd.createChar(0, sDay);
  lcd.createChar(1, mDay);
  lcd.createChar(2, tDay);
  lcd.createChar(3, wDay);
  lcd.createChar(4, fDay);
}

void zeroPadding(int time){
  if(time == 0){
    lcd.print("00");  
  }else{
    lcd.print("0");
    lcd.print(time);
  }
}

bool checkChange(int curTime, int prevTime){
  if(curTime != prevTime){
    return 1;
  }else{
    return 0;
  }
}

void loop()
{
  DateTime timeNow = rtc.now();
  lcd.setCursor(0,0);
  if(checkChange(timeNow.hour(), currentHour)){
    if(timeNow.hour()<10){
      zeroPadding(timeNow.hour());
    }else{
      lcd.print(timeNow.hour());
    }
    currentHour = timeNow.hour();
  }

  lcd.setCursor(2,0);
  lcd.print(":");

  if(checkChange(timeNow.minute(), currentMinute)){
    if(timeNow.minute()<10){
      zeroPadding(timeNow.minute());
    }else{
      lcd.print(timeNow.minute());
    }
    currentMinute = timeNow.minute();
  }

  lcd.setCursor(5,0);
  lcd.print(":");

  if(timeNow.second()<10){
    zeroPadding(timeNow.second());
  }else{
    lcd.print(timeNow.second());
  }

  lcd.setCursor(9,0);

  if(checkChange(timeNow.dayOfTheWeek(), currentDOW)){
    lcd.print("SMTWTFS");
    lcd.setCursor(9+timeNow.dayOfTheWeek(),0);
    switch(timeNow.dayOfTheWeek()){
      case 0:
        lcd.write(0);
        break;
      case 1:
        lcd.write(1);
        break;
      case 2:
        lcd.write(2);
        break;
      case 3:
        lcd.write(3);
        break;
      case 4:
        lcd.write(2);
        break;
      case 5:
        lcd.write(4);
        break;
      case 6:
        lcd.write(0);
        break;
    }
    currentDOW = timeNow.dayOfTheWeek();
  }

  lcd.setCursor(0,1);

  if(checkChange(timeNow.day(), currentDay)){
    if(timeNow.day()<10){
      zeroPadding(timeNow.day());
    }else{
      lcd.print(timeNow.day());
    }
  }

  lcd.setCursor(2,1);
  lcd.print("/");

  if(checkChange(timeNow.month(), currentMonth)){
    if(timeNow.month()<10){
      zeroPadding(timeNow.month());
    }else{
      lcd.print(timeNow.month());
    }
  }

  lcd.setCursor(5,1);
  lcd.print("/");

  if(checkChange(timeNow.year(), currentYear)){
    lcd.print(timeNow.year());
  }
  
	// Do nothing here...
}