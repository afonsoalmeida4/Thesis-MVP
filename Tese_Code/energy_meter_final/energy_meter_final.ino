//CURRENT CODE HAS APN FOR 1NCE

//power - 6uA sem RFM, 7uA com
// - 78uA
//NEW SCREEN DEFINES

//#include <reset.h>
#include <Arduino.h>
#include <Wire.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif

#include <Adafruit_SHT31.h>

#include <CayenneLPP.h>
CayenneLPP lpp(28);

Adafruit_SHT31 sht31 = Adafruit_SHT31();

#include <ModbusRtu.h>
#include "stdlib.h"
//#include <SoftwareSerial.h>


#define TRUE 1
#define FALSE 0

// END FLASH
//

#include <Sodaq_wdt.h>
#include <RTCZero.h> //timer thing
#include <FlashStorage.h> //to store the sequence number
#include <avr/dtostrf.h>


#define LUX_ANALOG A1
#define LED_R A0
#define LED_B A3

#define LUX_ENABLE 7

#define MEDIR_CAP 3 //PA09
#define CAP_V A2
#define PIR 11 //PA16


#define RFM_CS 9 //PA07
#define RFM_DIO0 13 //PA17
#define RFM_RST 5//PA15


//const byte voltage_interrupt = A3;
//
#define Serial Serial


//END DEFINITION

//END SCREEN DEFINE

//Flash Storage

FlashStorage(seq_0, byte);
FlashStorage(seq_1, byte);
FlashStorage(DST, int); //0 not written, 1 none, 2 DST

#define CONSOLE_STREAM   Serial
#define MODEM_STREAM     Serial1

#define HASH_SIZE 32
#define BLOCK_SIZE 64

//int count = 0;


//CONNECTION

#define CUSTOM
int DEBUG = 1;



//RTCZero rtc;

#define ADC_AREF 2.33f
#define BATVOLT_R1 100.0f
#define BATVOLT_R2 150.0f
#define BATVOLT_PIN CAP_V


/* Create an rtc object */
RTCZero rtc;

/* Change these values to set the current initial time */
const byte seconds = 0;
const byte minutes = 5;
const byte hours = 5;

const byte min_alarm = 2;
/* Change these values to set the current initial date */
const byte day = 4;
const byte month = 2;
const byte year = 20;

bool initmodem = false;
volatile bool isClock = false; //variables shared between main code and ISR must be declared volatile to tell the compiler that their variable can change at any time
volatile bool isButton = false;
int state = LOW;
int val = 0;

float getBatteryVoltage()
{
  digitalWrite(MEDIR_CAP, HIGH);

  sodaq_wdt_safe_delay(100);

  uint16_t voltage = (uint16_t)((ADC_AREF / 1.023) * (BATVOLT_R1 + BATVOLT_R2) / BATVOLT_R2 * (float)analogRead(CAP_V));

  /*
    Serial.println("Analog Read");
    Serial.println(analogRead(CAP_V));
  */
  digitalWrite(MEDIR_CAP, LOW);
  sodaq_wdt_safe_delay(100);

  return (float)voltage;
}

void alarmMatch()
{
  isClock = true;

}

int reset_cause = 0; //0 - normal power on ; 1 - Reset requested by System ; 2 - Reset by Watchdog ; 3 - External reset requested ; 4 - Reset Brown Out 3.3V; 5 - Reset Brown Out 1.2V
bool first_keepalive = true; //just send reset cause on first keepalive

//#define REG_PM_RCAUSE (0x40000438U)


//COMMUNICATION STUFF

#define SERIAL_DEBUG Serial  // serial USB debug - Arm M0
#define SERIAL_MODEM Serial1 // serial to Quectel BC66



int delay_var = 0;


#include "TinyLoRa.h"
#include <SPI.h>

TinyLoRa lora = TinyLoRa(RFM_DIO0, RFM_CS, RFM_RST);



// Network Session Key (MSB)
uint8_t NwkSkey[16] = {0x08, 0xe0, 0xd4, 0x06, 0x90, 0x1c, 0x0b, 0xe0, 0x8e, 0x08, 0xe0, 0x8f, 0x0a, 0x20, 0x4a, 0x09};

// Application Session Key (MSB)
uint8_t AppSkey[16] = {0x0a, 0xa0, 0xe9, 0x0a, 0x40, 0xa2, 0x06, 0x20, 0xec, 0x08, 0x80, 0xb5, 0x0f, 0x20, 0x23, 0x0a};

// Device Address (MSB)
uint8_t DevAddr[4] =  {0x00, 0x10, 0xe9, 0x06 } ;



int msg_count = 0;

#define EN_SENSOR 4

int num_lux_read = 3;



//////////////////////////////////
uint16_t au16data[16];
uint8_t u8state;
unsigned long u32wait;
int incomingByte;
int count = 0;
int bytes_response = 0;
float resposta = 0 ;
String buf [4];
long result;
long result1;

modbus_t telegram;

//////////////////////////////////

float modbus_16bit_register_pair_to_float(uint16_t a, uint16_t b) {
  uint32_t combined = ((uint32_t)a << 16) | b;
  float f;
  memcpy(&f, &combined, sizeof f);
  return f;
}



unsigned int hexToDec(String hexString) {

  unsigned int decValue = 0;
  int nextInt;

  for (int i = 0; i < hexString.length(); i++) {

    nextInt = int(hexString.charAt(i));
    if (nextInt >= 48 && nextInt <= 57) nextInt = map(nextInt, 48, 57, 0, 9);
    if (nextInt >= 65 && nextInt <= 70) nextInt = map(nextInt, 65, 70, 10, 15);
    if (nextInt >= 97 && nextInt <= 102) nextInt = map(nextInt, 97, 102, 10, 15);
    nextInt = constrain(nextInt, 0, 15);

    decValue = (decValue * 16) + nextInt;
  }

  return decValue;
}




void getresponse ( )
{
  delay(1500);
  //Serial.print("hereeeeee");

  while (Serial1.available() > 0) {
    // read the incoming byte:
    //  Serial.print(Serial.read());
    incomingByte = Serial1.read();
    Serial1.print("0x");
    Serial1.print(incomingByte, HEX);
    Serial1.print( "  ");
    Serial.print("0x");
    Serial.print(incomingByte, HEX);
    Serial.print( "  ");


    count++;
    if (count == 3) {
      bytes_response = incomingByte;

    }
    if (count > 3 and count <= (3 + bytes_response)) {
      if (count == 4) {
        buf[0] = String(incomingByte, HEX);
        if (buf[0].length() < 2) {
          buf[0] = "0" + buf[0];

        }

      }
      if (count == 5) {
        buf[1] = String(incomingByte, HEX);
        if (buf[1].length() < 2) {
          buf[1] = "0" + buf[1];

        }
        buf[0].concat(buf[1]);


        result = hexToDec(buf[0]);



      }
      if (count == 6) {
        buf[2] = String(incomingByte, HEX);
        if (buf[2].length() < 2) {
          buf[2] = "0" + buf[2];

        }

      }
      if (count == 7) {
        buf[3] = String(incomingByte, HEX);
        if (buf[3].length() < 2) {
          buf[3] = "0" + buf[3];

        }
        buf[2].concat(buf[3]);
        result1 = hexToDec(buf[2]);

      }

      Serial.print("0x");
      Serial.print(incomingByte, HEX);
      Serial.print( "  ");
      resposta = modbus_16bit_register_pair_to_float(result, result1);

    }

  }
  //Serial.println("  ");
  Serial1.print("0x");

  delay(1500);
  Serial.begin(9600, SERIAL_8N1);

  /*while (Serial.available() > 0) {
          // read the incoming byte:
        //  Serial.print(Serial.read());
          incomingByte = Serial.read();
          Serial.print("0x");
          Serial.print(incomingByte, HEX);
          Serial.print( "  ");

    }
    //Serial.println("  ");
    Serial.print("0x");

    delay(1500);
    Serial.begin(9600,SERIAL_8N1);*/


}


void SendEBRequest(uint8_t u8id, uint8_t u8fct, uint16_t u16RegAdd, uint16_t u16CoilsNo/*, uint16_t  *au16reg*/)
{
  /*
    u8id : slave address, in this case =1
    u8fct : function code (check documentation)
    u16RegAdd : start address in slave (check documentation)
    u16CoilsNo : number of elements (coils or registers) to read
    au16reg : pointer to a memory array in the Arduino
    Exemplo  byte message_intant_P[] = {0x01, 0x04, 0x00, 0x79, 0x00, 0x01, 0xe0, 0x13};
  */
  uint8_t telegram[8]; //
  uint8_t tel[6]; //
  uint16_t crc;
  Serial1.begin(9600, SERIAL_8N1);
  //Serial.begin(9600,SERIAL_8N1);

  tel[0] = u8id;
  tel[1] = u8fct;
  tel[2] = ((u16RegAdd >> 8) & 0xFF);
  tel[3] = (u16RegAdd & 0xFF);
  tel[4] = ((u16CoilsNo >> 8) & 0xFF);
  tel[5] = (u16CoilsNo & 0xFF);

  crc = ModRTU_CRC(tel, sizeof(tel));  //Calcula o CRC da menssagem

  Serial1.println(crc, HEX);
  //Serial.println(crc,HEX);

  telegram[0] = u8id;
  telegram[1] = u8fct;
  telegram[2] = ((u16RegAdd >> 8) & 0xFF);
  telegram[3] = (u16RegAdd & 0xFF);
  telegram[4] = ((u16CoilsNo >> 8) & 0xFF);
  telegram[5] = (u16CoilsNo & 0xFF);
  telegram[6] = (crc & 0xFF);
  telegram[7] = ((crc >> 8) & 0xFF);


  Serial.println("\n");
  Serial.println( telegram[0], HEX);
  Serial.println( telegram[1], HEX);
  Serial.println( telegram[2], HEX);
  Serial.println( telegram[3], HEX);
  Serial.println( telegram[4], HEX);
  Serial.println( telegram[5], HEX);
  delay(200);

  digitalWrite(1, HIGH);  //Colcar transceiver rs485 em modo escrita
  delay(500);
  //Serial.println(telegram[0],HEX);
  //Serial.print(sizeof(telegram));

  Serial1.write(telegram, sizeof(telegram));
  //Serial.write(telegram, sizeof(telegram));

  delay(10);
  digitalWrite(1, LOW);  //Colcar transceiver rs485 em modo leitura
}

uint16_t ModRTU_CRC(uint8_t * buf, int len)
{
  uint16_t crc = 0xFFFF;

  for (int pos = 0; pos < len; pos++) {
    crc ^= (uint16_t)buf[pos];          // XOR byte into least sig. byte of crc

    for (int i = 8; i != 0; i--) {    // Loop over each bit
      if ((crc & 0x0001) != 0) {      // If the LSB is set
        crc >>= 1;                    // Shift right and XOR 0xA001
        crc ^= 0xA001;
      }
      else                            // Else LSB is not set
        crc >>= 1;                    // Just shift right
    }
  }
  // Note, this number has low and high bytes swapped, so use it accordingly (or swap bytes)
  return crc;
}


void send_lora_consume(float consume)
{
  /*enable sensors */
  digitalWrite(EN_SENSOR, HIGH);
  digitalWrite(LUX_ENABLE, HIGH);

  sodaq_wdt_safe_delay(50);
  lpp.reset();

  Serial.println("Before SHT INIT");

  //float lux = get_lux();


  if (! sht31.begin(0x44)) {   // Set to 0x45 for alternate i2c addr
    Serial.println("Couldn't find SHT31");
    float t = 0.0;
    float h = 0.0;
    float b_volt = 0;

    b_volt = getBatteryVoltage();

    lpp.addTemperature(0, t);


    lpp.addRelativeHumidity(1, h);

    b_volt = b_volt / (100.0);

    lpp.addAnalogInput(2, b_volt);
    lpp.addAnalogInput(3, consume);


    //lpp.addLuminosity(3, lux);

    lora.frameCounter = msg_count;
    //lora.sendData(loraData, sizeof(loraData), lora.frameCounter);


    //lora.sendData((unsigned char*)send_buf, sizeof(send_buf), lora.frameCounter);

    lora.sendData(lpp.getBuffer(), lpp.getSize(), lora.frameCounter);

    Serial.print("Frame Counter: "); Serial.println(lora.frameCounter);
    lora.frameCounter++;
    msg_count++;
  }
  else {
    Serial.println("Sending LoRa Data...");


    float t = sht31.readTemperature();
    float h = sht31.readHumidity();

    if (! isnan(t)) {  // check if 'is not a number'
      Serial.print("Temp *C = "); Serial.print(t); Serial.print("\t\t");
    } else {
      Serial.println("Failed to read temperature");
    }

    if (! isnan(h)) {  // check if 'is not a number'
      Serial.print("Hum. % = "); Serial.println(h);
    } else {
      Serial.println("Failed to read humidity");
    }
    if (! isnan(consume)) {  // check if 'is not a number'
      Serial.print("Count consume = "); Serial.println(consume);
    } else {
      Serial.println("Failed to read motion");
    }
    /*
      char send_buf[17] = "";
      float b_volt = 0;
      b_volt = getBatteryVoltage();
      sprintf(send_buf,"%.02f,%.02f,%.00f",t,h,b_volt);

      Serial.print(send_buf);
    */

    float b_volt = 0;

    b_volt = getBatteryVoltage();

    lpp.addTemperature(0, t);


    lpp.addRelativeHumidity(1, h);

    b_volt = b_volt / (100.0);

    lpp.addAnalogInput(2, b_volt);
    lpp.addAnalogInput(3, consume);


    //lpp.addLuminosity(3, lux);

    lora.frameCounter = msg_count;
    //lora.sendData(loraData, sizeof(loraData), lora.frameCounter);


    //lora.sendData((unsigned char*)send_buf, sizeof(send_buf), lora.frameCounter);

    lora.sendData(lpp.getBuffer(), lpp.getSize(), lora.frameCounter);

    Serial.print("Frame Counter: "); Serial.println(lora.frameCounter);
    lora.frameCounter++;
    msg_count++;
  }
  /* Turn off Sensors */
  digitalWrite(EN_SENSOR, LOW);
  digitalWrite(LUX_ENABLE, LOW);

}


void setup_BOD33()
{
  Serial.println(F("Fuse settings before:"));
  Serial.println((*(uint32_t*)NVMCTRL_USER), HEX);         // Display the current user word 0 fuse settings
  Serial.println((*(uint32_t*)(NVMCTRL_USER + 4)), HEX);   // Display the current user word 1 fuse settings
  uint32_t userWord0 = *((uint32_t*)NVMCTRL_USER);            // Read fuses for user word 0
  uint32_t userWord1 = *((uint32_t*)(NVMCTRL_USER + 4));      // Read fuses for user word 1
  NVMCTRL->CTRLB.bit.CACHEDIS = 1;                            // Disable the cache
  NVMCTRL->ADDR.reg = NVMCTRL_AUX0_ADDRESS / 2;               // Set the address
  NVMCTRL->CTRLA.reg = NVMCTRL_CTRLA_CMD_EAR |                // Erase the auxiliary user page row
                       NVMCTRL_CTRLA_CMDEX_KEY;
  while (!NVMCTRL->INTFLAG.bit.READY)                         // Wait for the NVM command to complete
    NVMCTRL->STATUS.reg |= NVMCTRL_STATUS_MASK;                 // Clear the error flags
  NVMCTRL->ADDR.reg = NVMCTRL_AUX0_ADDRESS / 2;               // Set the address
  NVMCTRL->CTRLA.reg = NVMCTRL_CTRLA_CMD_PBC |                // Clear the page buffer
                       NVMCTRL_CTRLA_CMDEX_KEY;
  while (!NVMCTRL->INTFLAG.bit.READY)                         // Wait for the NVM command to complete
    NVMCTRL->STATUS.reg |= NVMCTRL_STATUS_MASK;                 // Clear the error flags
  *((uint32_t*)NVMCTRL_USER) = userWord0 & ~FUSES_BOD33_EN_Msk;  // Disable the BOD33 enable fuse in user word 0
  *((uint32_t*)(NVMCTRL_USER + 4)) = userWord1;               // Copy back user word 1 unchanged
  NVMCTRL->CTRLA.reg = NVMCTRL_CTRLA_CMD_WAP  |               // Write to the user page
                       NVMCTRL_CTRLA_CMDEX_KEY;
  while (!NVMCTRL->INTFLAG.bit.READY)                         // Wait for the NVM command to complete
    NVMCTRL->STATUS.reg |= NVMCTRL_STATUS_MASK;                 // Clear the error flags
  NVMCTRL->CTRLB.bit.CACHEDIS = 0;                            // Enable the cache
  Serial.println(F("Fuse settings after:"));
  Serial.println((*(uint32_t*)NVMCTRL_USER), HEX);         // Display the current user word 0 fuse settings
  Serial.println((*(uint32_t*)(NVMCTRL_USER + 4)), HEX);   // Display the current user word 1 fuse settings

}

void nvm_wait_states() //maybe not necessary
{
  NVMCTRL->CTRLB.bit.RWS = 3;
}


void setup_rtc_debug()
{
  byte h, mm, s = 0;

  rtc.begin(); // initialize RTC

  rtc.setTime(h, mm, s);

  rtc.setAlarmTime(h, (mm + 5), s);

  rtc.enableAlarm(rtc.MATCH_MMSS);

  rtc.attachInterrupt(alarmMatch);
}


void i2c_scan()
{
  byte error, address;
  int nDevices;

  Serial.println("Scanning...");

  nDevices = 0;
  for (address = 1; address < 127; address++ )
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Serial.println("Scanning before begin ...");
    Wire.beginTransmission(address);
    Serial.println("Scanning after begin ...");

    error = Wire.endTransmission();
    Serial.println("Scanning after end trans ...");
    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address < 16)
        Serial.print("0");
      Serial.print(address, HEX);
      Serial.println("  !");

      nDevices++;
    }
    else if (error == 4)
    {
      Serial.print("Unknown error at address 0x");
      if (address < 16)
        Serial.print("0");
      Serial.println(address, HEX);
    }
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("done\n");

  delay(5000);           // wait 5 seconds for next scan
}


//
//enable sensor - PA8


void setup()
{
  asm(".global _printf_float"); //very impotant for sprintf with float

  Serial1.begin(9600, SERIAL_8N1);
  Serial.begin(9600, SERIAL_8N1); //use the hardware serial if you want to connect to your computer via usb cable, etc.
  //master.start(); // start the ModBus object.
  //master.setTimeOut( 2000 ); // if there is no answer in 2000 ms, roll over
  u32wait = millis() + 1000;
  u8state = 0;
  // Bootup sodaq_wdt_safe_delay to programm the board.

  setup_BOD33();

  nvm_wait_states();

  //Find Reset Cause
  if (REG_PM_RCAUSE == PM_RCAUSE_SYST) {
    Serial.println("Reset requested by system");
    reset_cause = 1;
  }
  if (REG_PM_RCAUSE == PM_RCAUSE_WDT) {
    Serial.println("Reset requested by Watchdog");
    reset_cause = 2;
  }
  if (REG_PM_RCAUSE == PM_RCAUSE_EXT) {
    Serial.println("External reset requested");
    reset_cause = 3;
  }
  if (REG_PM_RCAUSE == PM_RCAUSE_BOD33) {
    Serial.println("Reset brown out 3.3V");
    reset_cause = 4;
  }
  if (REG_PM_RCAUSE == PM_RCAUSE_BOD12) {
    Serial.println("Reset brown out 1.2v");
    reset_cause = 5;
  }
  if (REG_PM_RCAUSE == PM_RCAUSE_POR) {
    Serial.println("Normal power on reset");
    reset_cause = 0;
  }
  //End find reset cause

  Wire.begin();


  sodaq_wdt_safe_delay(5000);

  sodaq_wdt_enable(WDT_PERIOD_8X); //ENABLE WDT

  setup_rtc_debug();


  pinMode(MEDIR_CAP, OUTPUT);
  digitalWrite(MEDIR_CAP, LOW);
  pinMode(CAP_V, INPUT);
  analogReference(AR_DEFAULT);

  //PIR THINGS

  /*pinMode(LUX_ENABLE,OUTPUT);
    digitalWrite(LUX_ENABLE,LOW);

    pinMode(LUX_ANALOG,INPUT); //965,966 in a lit room*/

  pinMode(EN_SENSOR, OUTPUT);
  digitalWrite(EN_SENSOR, LOW);



  lora.setChannel(MULTI);
  // set datarate
  //lora.setDatarate(SF7BW125);
  lora.setDatarate(SF9BW125);
  //lora.setDatarate(SF10BW125);
  //lora.setDatarate(SF11BW125);
  if (!lora.begin())
  {
    Serial.println("Failed");
    Serial.println("Check your radio");
    while (true)
    {
      delay(1000);
      Serial.println("Failed");
      Serial.println("Check your radio");
      delay(1000);
    }
  }
  else {
    Serial.println("INIT LORA SUCCESS");
  }

  //send_lora_consume();

  sodaq_wdt_reset();

  //stuff to allow falling interrupt
  // Set the XOSC32K to run in standby
  SYSCTRL->XOSC32K.bit.RUNSTDBY = 1;

  // Configure EIC to use GCLK1 which uses XOSC32K
  // This has to be done after the first call to attachInterrupt()
  GCLK->CLKCTRL.reg = GCLK_CLKCTRL_ID(GCM_EIC) |
                      GCLK_CLKCTRL_GEN_GCLK1 |
                      GCLK_CLKCTRL_CLKEN;




  //lora.sleep();
  //systemSleep();



}

//char buf;




/**
  Powers down all devices and puts the system to deep sleep.
*/
void systemSleep()
{

  //digitalWrite(EN_SENSOR,LOW);


  SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;

  lora.sleep();

  // Disable USB
  //USBDevice.detach();

  Serial.flush();
  Serial.end();
  USBDevice.detach();
  USB->DEVICE.CTRLA.reg &= ~USB_CTRLA_ENABLE; // Disable USB
  //rtc.standbyMode();

  // Disable systick interrupt

  SysTick->CTRL &= ~SysTick_CTRL_TICKINT_Msk;

  sodaq_wdt_disable();

  //BARRIER INSTRUCTION - WASNT HERE BEFORE
  __DSB();


  // SAMD sleep
  __WFI();


  // Enable systick interrupt
  SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;

  sodaq_wdt_enable(WDT_PERIOD_8X); //ENABLE WDT

  //ENABLE 3.3V PWR_SUP


}

int num_of_keep_alives = 0;

int timer = 0;
float final_response;
void loop()
{
  switch ( u8state ) {
    /*case 0:
      if (millis() > u32wait) u8state++; // wait state
      break;*/
    case 0:

      SendEBRequest(0x1, 0x3, 0x500A, 0x0002);
      u8state++;
      break;
    case 1:
      getresponse();
      Serial.print("bytes: ");
      Serial.print (bytes_response);
      Serial.println("\n");
      final_response = resposta * (-1);
      Serial.print("Resposta: ");
      Serial.print(final_response);
      count = 0;
      u8state = 0;
      //send_lora_consume(final_response);

      break;
  }
  if (sodaq_wdt_flag) {
    // Reset watchdog
    sodaq_wdt_reset();
    sodaq_wdt_flag = false;
    if ((~isButton) && (~isClock) && (~sodaq_wdt_flag)) {
      systemSleep();
    }
    //systemSleep();

  }
  if (isClock)
  {

    isClock = false;
    sodaq_wdt_reset();
    rtc.setAlarmMinutes((rtc.getAlarmMinutes() + 5) % 60); //reschedule the alarm for the next 12h
    if (!lora.begin())
    {
      Serial.println("Failed");
      Serial.println("Check your radio");

    }
    else {
      switch ( u8state ) {
        /*case 0:
          if (millis() > u32wait) u8state++; // wait state
          break;*/
        case 0:

          SendEBRequest(0x1, 0x3, 0x500A, 0x0002/*,&dataCheck*/);
          u8state++;
          break;
        case 1:
          getresponse();
          Serial.print("bytes: ");
          Serial.print (bytes_response);
          Serial.println("\n");
          if (resposta < 0){
            final_response = resposta * (-1);
           }else{
            final_response = resposta;
           }
          
          Serial.print("Resposta: ");
          Serial.print(final_response);
          count = 0;
          u8state = 0;
          //send_lora_consume(final_response);

          break;
      }
      send_lora_consume(final_response);

    }
    if ((~isButton) && (~isClock) && (~sodaq_wdt_flag)) {
      //systemSleep();

    }
    //systemSleep();
  }



}
