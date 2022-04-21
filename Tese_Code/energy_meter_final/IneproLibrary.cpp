/*
 * IneproLibrary created by Goncalo Ramalho Freire de Andrade @ Jan/2018
 * PRO1-Mod
 */
#include "IneproLibrary.h"

IneproLib::IneproLib(bool displayMsg){
  //Lib activated when IneproLib(true)
}

// 00 03 20 00 00 02 CE 1A 
void IneproLib::getVolts(byte pmessage[]){
  byte msg[] = {0x00, 0x03, 0x20, 0x00, 0x00, 0x02, 0xCE, 0x1A};
  for (int i=0; i<8; i++){
    pmessage[i]=msg[i];
  }
}

//00 03 20 60 00 02 CE 04 
void IneproLib::getCurrent(byte pmessage[]){
  byte msg[] = {0x00, 0x03, 0x20, 0x60, 0x00, 0x02, 0xCE, 0x04};
  for (int i=0; i<8; i++){
    pmessage[i]=msg[i];
  }
}

//00 03 20 20 00 02 CF D0
void IneproLib::getFrequency(byte pmessage[]){
  byte msg[] = {0x00, 0x03, 0x20, 0x20, 0x00, 0x02, 0xCF, 0xD0};
  for (int i=0; i<8; i++){
    pmessage[i]=msg[i];
  }
}

//00 03 20 80 00 02 CF F2 
void IneproLib::getTotalActivePower(byte pmessage[]){
  byte msg[] = {0x00, 0x03, 0x20, 0x80, 0x00, 0x02, 0xCF, 0xF2};
  for (int i=0; i<8; i++){
    pmessage[i]=msg[i];
  }
}

//00 03 20 A0 00 02 CE 38 
void IneproLib::getTotalReactivePower(byte pmessage[]){
  byte msg[] = {0x00, 0x03, 0x20, 0xA0, 0x00, 0x02, 0xCE, 0x38 };
  for (int i=0; i<8; i++){
    pmessage[i]=msg[i];
  }
}

// 00 03 20 C0 00 02 CE 26
void IneproLib::getTotalApparentPower(byte pmessage[]){
  byte msg[] = {0x00, 0x03, 0x20, 0xC0, 0x00, 0x02, 0xCE, 0x26};
  for (int i=0; i<8; i++){
    pmessage[i]=msg[i];
  }
}

//00 03 20 E0 00 02 CF EC
void IneproLib::getPowerFactor(byte pmessage[]){
  byte msg[] = {0x00, 0x03, 0x20, 0xE0, 0x00, 0x02, 0xCF, 0xEC};
  for (int i=0; i<8; i++){
    pmessage[i]=msg[i];
  }
}

//00 03 30 00 00 02 CA DA 
void IneproLib::getTotalActiveEnergy(byte pmessage[]){
  byte msg[] = {0x00, 0x03, 0x30, 0x00, 0x00, 0x02, 0xCA, 0xDA};
  for (int i=0; i<8; i++){
    pmessage[i]=msg[i];
  }
}

//00 03 31 00 00 02 CB 26 
void IneproLib::getT1TotalActiveEnergy(byte pmessage[]){
  byte msg[] = {0x00, 0x03, 0x31, 0x00, 0x00, 0x02, 0xCB, 0x26};
  for (int i=0; i<8; i++){
    pmessage[i]=msg[i];
  }
}

//00 03 32 00 00 02 CB 62
void IneproLib::getT2TotalActiveEnergy(byte pmessage[]){
  byte msg[] = {0x00, 0x03, 0x32, 0x00, 0x00, 0x02, 0xCB, 0x62};
  for (int i=0; i<8; i++){
    pmessage[i]=msg[i];
  }
}

//00 03 30 20 00 02 CB 10
void IneproLib::getForwardActiveEnergy(byte pmessage[]){
  byte msg[] = {0x00, 0x03, 0x30, 0x20, 0x00, 0x02, 0xCB, 0x10};
  for (int i=0; i<8; i++){
    pmessage[i]=msg[i];
  }
}

//00 03 31 20 00 02 CA EC
void IneproLib::getT1ForwardActiveEnergy(byte pmessage[]){
  byte msg[] = {0x00, 0x03, 0x31, 0x20, 0x00, 0x02, 0xCA, 0xEC};
  for (int i=0; i<8; i++){
    pmessage[i]=msg[i];
  }
}

//00 03 32 20 00 02 CA A8 
void IneproLib::getT2ForwardActiveEnergy(byte pmessage[]){
  byte msg[] = {0x00, 0x03, 0x32, 0x20, 0x00, 0x02, 0xCA, 0xA8};
  for (int i=0; i<8; i++){
    pmessage[i]=msg[i];
  }
}

//00 03 30 40 00 02 CB 0E 
void IneproLib::getReverseActiveEnergy(byte pmessage[]){
  byte msg[] = {0x00, 0x03, 0x30, 0x40, 0x00, 0x02, 0xCB, 0x0E};
  for (int i=0; i<8; i++){
    pmessage[i]=msg[i];
  }
}

//00 03 31 40 00 02 CA F2 
void IneproLib::getT1ReverseActiveEnergy(byte pmessage[]){
  byte msg[] = {0x00, 0x03, 0x31, 0x40, 0x00, 0x02, 0xCA, 0xF2};
  for (int i=0; i<8; i++){
    pmessage[i]=msg[i];
  }
}

//00 03 32 40 00 02 CA B6
void IneproLib::getT2ReverseActiveEnergy(byte pmessage[]){
  byte msg[] = {0x00, 0x03, 0x32, 0x40, 0x00, 0x02, 0xCA, 0xB6};
  for (int i=0; i<8; i++){
    pmessage[i]=msg[i];
  }
}


//00 03 30 60 00 02 CA C4 
void IneproLib::getTotalReactiveEnergy(byte pmessage[]){
  byte msg[] = {0x00, 0x03, 0x30, 0x60, 0x00, 0x02, 0xCA, 0xC4};
  for (int i=0; i<8; i++){
    pmessage[i]=msg[i];
  }
}


//00 03 31 60 00 02 CB 38 
void IneproLib::getT1TotalReactiveEnergy(byte pmessage[]){
  byte msg[] = {0x00, 0x03, 0x31, 0x60, 0x00, 0x02, 0xCB, 0x38};
  for (int i=0; i<8; i++){
    pmessage[i]=msg[i];
  }
}


//00 03 32 60 00 02 CB 7C 
void IneproLib::getT2TotalReactiveEnergy(byte pmessage[]){
  byte msg[] = {0x00, 0x03, 0x32, 0x60, 0x00, 0x02, 0xCB, 0x7C};
  for (int i=0; i<8; i++){
    pmessage[i]=msg[i];
  }
}


//00 03 30 80 00 02 CB 32 
void IneproLib::getForwardReactiveEnergy(byte pmessage[]){
  byte msg[] = {0x00, 0x03, 0x30, 0x80, 0x00, 0x02, 0xCB, 0x32};
  for (int i=0; i<8; i++){
    pmessage[i]=msg[i];
  }
}

//00 03 31 80 00 02 CA CE 
void IneproLib::getT1ForwardReactiveEnergy(byte pmessage[]){
  byte msg[] = {0x00, 0x03, 0x31, 0x80, 0x00, 0x02, 0xCA, 0xCE};
  for (int i=0; i<8; i++){
    pmessage[i]=msg[i];
  }
}

//00 03 32 80 00 02 CA 8A 
void IneproLib::getT2ForwardReactiveEnergy(byte pmessage[]){
  byte msg[] = {0x00, 0x03, 0x32, 0x80, 0x00, 0x02, 0xCA, 0x8A};
  for (int i=0; i<8; i++){
    pmessage[i]=msg[i];
  }
}

//00 03 30 A0 00 02 CA F8 
void IneproLib::getReverseReactiveEnergy(byte pmessage[]){
  byte msg[] = {0x00, 0x03, 0x30, 0xA0, 0x00, 0x02, 0xCA, 0xF8};
  for (int i=0; i<8; i++){
    pmessage[i]=msg[i];
  }
}


//00 03 31 A0 00 02 CB 04
void IneproLib::getT1ReverseReactiveEnergy(byte pmessage[]){
  byte msg[] = {0x00, 0x03, 0x31, 0xA0, 0x00, 0x02, 0xCB, 0x04};
  for (int i=0; i<8; i++){
    pmessage[i]=msg[i];
  }
}


//00 03 32 A0 00 02 CB 40
void IneproLib::getT2ReverseReactiveEnergy(byte pmessage[]){
  byte msg[] = {0x00, 0x03, 0x32, 0xA0, 0x00, 0x02, 0xCB, 0x40};
  for (int i=0; i<8; i++){
    pmessage[i]=msg[i];
  }
}

