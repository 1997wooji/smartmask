#include <SharpDust.h>
#include <SoftwareSerial.h>
#include <String.h>
#include <EEPROM.h>

#define DUST_LED_PIN    2
#define DUST_MEASURE_PIN  0
#define DUST_AVRG_MEASURE 5
#define EEPROM_ADDR 0
#define EEPROM_ADDR_HOUR 1

const int DELAY_FOR_LOOP_MS = 5000;

float dust_val = 0;
float dust_val_ug = 0;

char command;
int filter_time_sec;
//float get_avrg_dust_val(&SharpDust SharpDust,int avrg);
SoftwareSerial BT_serial(8,7);

void setup() {
  Serial.begin(9600);
  BT_serial.begin(9600);
  pinMode(A1, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  
  // for initial time setting
  // EEPROM.write(EEPROM_ADDR_HOUR, 10);
  // EEPROM.write(EEPROM_ADDR,42);

  SharpDust.begin(DUST_LED_PIN, DUST_MEASURE_PIN);
}

void loop() {
  
  // dust_val = SharpDust.measure();
  // dust_val_ug = 1000*dust_val;

  dust_val_ug = get_avrg_dust_val(5);

  turn_LED_by_dust(dust_val_ug);

    Serial.print(F("Dust :"));
    Serial.print(dust_val_ug);
    Serial.println(F(" ug/m^3"));

    String bt_str;
    bt_str = "Dust: ";
    bt_str += dust_val_ug;
    // bt_str += get_avrg_dust_val(5);
    bt_str += " ug/m^3";
    BT_serial.println(bt_str);
    // BT_serial.println(dust_val_ug);

      if(BT_serial.available()){
      command = BT_serial.read();
      BT_serial.flush();
    }

    // return fliter used time
    if(command == 'T'){

      int eeprom_filter_time_hour = EEPROM.read(EEPROM_ADDR_HOUR);
      BT_serial.print(eeprom_filter_time_hour); // hour
      BT_serial.print(":");
      int eeprom_filter_time = EEPROM.read(EEPROM_ADDR);
      BT_serial.print(eeprom_filter_time); // min
      BT_serial.println();
      // BT_serial.println("10:32");
      command = '\0';
    }
    // BT_serial.print(F("Dust :"));
    // BT_serial.print(dust_val_ug);
    // BT_serial.println(F(" ug/m^3"));

    // update eeprom filter use time with delay
    delay(DELAY_FOR_LOOP_MS);
    filter_time_sec += DELAY_FOR_LOOP_MS/1000;
    if(filter_time_sec >59){
      //add value in eeprom
      int eeprom_filter_time = EEPROM.read(EEPROM_ADDR);
      if(eeprom_filter_time >59){ // if min reach to 60min, update hour
        eeprom_filter_time = 0;
        int eeprom_filter_time_hour = EEPROM.read(EEPROM_ADDR_HOUR);
        EEPROM.write(EEPROM_ADDR_HOUR, eeprom_filter_time_hour+1);
      }
      EEPROM.write(EEPROM_ADDR, eeprom_filter_time+1);
      filter_time_sec = 0;
    }

  
}

void turn_LED_by_dust(float dust_val_ug){
  if(dust_val_ug < 0.0f)
    Serial.println("Error! Dust value is negative.");
  if(dust_val_ug < 30.0f){
   LED_control(false, false, true); // good
   Serial.println("good");
  } 
  else if(dust_val_ug < 80.0f){
    LED_control(false, true, false); // normal
    Serial.println("normal");
  }
  else if(dust_val_ug < 120.0f){
    LED_control(true, false, false); // bad
    Serial.println("bad");
  } 
  else{
    LED_control(true, false, false); //very bad (over 120)
    Serial.println("default");
  }
    
}

void LED_control(bool RED, bool GREEN, bool BLUE){
  const int led_pin_red = A1;
  const int led_pin_blue = 11;
  const int led_pin_green = 12;

  if(RED)
    digitalWrite(led_pin_red, HIGH);
  else
    digitalWrite(led_pin_red, LOW);

  if(BLUE)
    digitalWrite(led_pin_blue, HIGH);
  else
    digitalWrite(led_pin_blue, LOW);

  if(GREEN)
    digitalWrite(led_pin_green, HIGH);
  else
    digitalWrite(led_pin_green, LOW);
}

float get_avrg_dust_val(int avrg){
  float sum_val;
  for(int i=0; i< avrg; i++){
    sum_val += SharpDust.measure();
    delay(100);
  }
  return (sum_val / avrg)*1000;
}




