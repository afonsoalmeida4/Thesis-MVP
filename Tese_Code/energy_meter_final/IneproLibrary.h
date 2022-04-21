/*
 * IneproLibrary created by Goncalo Ramalho Freire de Andrade @ Jan/2018
 * PRO1-Mod
 */
#ifndef IneproLib_h
#define IneproLib_h

#include "Arduino.h"

class IneproLib {
  public:
    //constructor
    IneproLib(bool displayMsg=false);

    // Methods

    void getVolts(byte pmessage[]);
    void getCurrent(byte pmessage[]);
    void getFrequency(byte pmessage[]);
    
    void getTotalActivePower(byte pmessage[]);
    void getTotalReactivePower(byte pmessage[]);
    void getTotalApparentPower(byte pmessage[]);
    void getPowerFactor(byte pmessage[]);

    void getTotalActiveEnergy(byte pmessage[]);
    void getT1TotalActiveEnergy(byte pmessage[]);
    void getT2TotalActiveEnergy(byte pmessage[]);

    void getForwardActiveEnergy(byte pmessage[]);
    void getT1ForwardActiveEnergy(byte pmessage[]);
    void getT2ForwardActiveEnergy(byte pmessage[]);

    void getReverseActiveEnergy(byte pmessage[]);
    void getT1ReverseActiveEnergy(byte pmessage[]);
    void getT2ReverseActiveEnergy(byte pmessage[]);

    void getTotalReactiveEnergy(byte pmessage[]);
    void getT1TotalReactiveEnergy(byte pmessage[]);
    void getT2TotalReactiveEnergy(byte pmessage[]);

    void getForwardReactiveEnergy(byte pmessage[]);
    void getT1ForwardReactiveEnergy(byte pmessage[]);
    void getT2ForwardReactiveEnergy(byte pmessage[]);

    void getReverseReactiveEnergy(byte pmessage[]);
    void getT1ReverseReactiveEnergy(byte pmessage[]);
    void getT2ReverseReactiveEnergy(byte pmessage[]);
    
  private:
  
};

#endif
