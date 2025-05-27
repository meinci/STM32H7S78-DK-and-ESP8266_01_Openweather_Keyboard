
#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>
#include "stm32h7rsxx_hal.h"
extern __IO float guiTemp;
extern __IO int guiHumi;
extern __IO int guiPres;
extern __IO int guiYear;
extern __IO int guiMonth;
extern __IO int guiDay;
extern __IO int guiHour;
extern __IO int guiMinute;
extern __IO int request;
extern char guiIcon[6];
extern char guiDescription[25];
extern char guiCity[30];
extern char guiSSID[32];
extern char guissidList[20][33];
extern char SSIDs_Buffer[512];


#include <iostream>
#include <string>
#include "cJSON.h"
#include <string.h>
#include "globals.h"
#include <touchgfx/Unicode.hpp>

// Deklariere hier die externe Funktion aus C
extern "C" {
    void myScanFunctionInC(void);
}

Model::Model() : modelListener(0)
{

}

void Model::tick()
{

  modelListener->updateTemp(request,guiTemp);
  modelListener->updateHumi(request,guiHumi);
  modelListener->updateCity(request,guiCity);
  modelListener->updatePres(request,guiPres);
  modelListener->updateYear(guiYear);
  modelListener->updateMonth(guiMonth);
  modelListener->updateDay(guiDay);
  modelListener->updateHour(guiHour);
  modelListener->updateMinute(guiMinute);
  modelListener->updateIcon(request,guiIcon);
  modelListener->updateDescription(request,guiDescription);
  modelListener->updateSSID(guiSSID);
  modelListener->updateSSIDList(SSIDs_Buffer);

}

void Model::scanSSIDs()
{
    // Aufruf der C-Funktion
    myScanFunctionInC();
}







