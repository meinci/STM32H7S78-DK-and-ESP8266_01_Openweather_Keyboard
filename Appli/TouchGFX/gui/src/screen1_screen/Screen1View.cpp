#include <gui/screen1_screen/Screen1View.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <BitmapDatabase.hpp>  // Enthält die generierten Bitmap-IDs
#include <stdio.h>
#include <string.h>
#include <cstring>
#include "globals.h"

Unicode::UnicodeChar keyboardBuffer_City[25];//add



enum WeatherType
{
    ICON_UNKNOWN,
    ICON_01D,
    ICON_01N,
    ICON_02D,
    ICON_02N
    // ggf. weitere ...
};

const char* enumToString(WeatherType icon)
{
    switch (icon)
    {
    case ICON_01D:    return "01d";
    case ICON_01N:    return "01n";
    case ICON_02D:    return "02d";
    case ICON_02N:    return "02n";
    default:          return "unknown";
    }
}

Screen1View::Screen1View()
{

}

void Screen1View::setupScreen()
{
    Screen1ViewBase::setupScreen();
}

void Screen1View::tearDownScreen()
{
    Screen1ViewBase::tearDownScreen();
}


void Screen1View::flexbuttonShow_SSIDs()
{
    // Hier machst du, was du willst, z. B. Presenter-Funktion aufrufen
	tA_SSIDList.setVisible(true);
    presenter->buttonClicked(); // oder presenter->updateSSIDList(...);
}



void Screen1View::updateHumi(int request,int value){
	if(request == 0){
		 Unicode::snprintf(tA_Outdoor_HumiBuffer,TA_OUTDOOR_HUMI_SIZE,"%.2d%",value);
		 tA_Outdoor_Humi.invalidate();
	}
}


void Screen1View::updatePres(int request,int value){
	if(request == 0){
		Unicode::snprintf(tA_Outdoor_PresBuffer,TA_OUTDOOR_PRES_SIZE,"%dmpH",value);
		tA_Outdoor_Pres.invalidate();
	}
}

void Screen1View::updateYear(int value){
	Unicode::snprintf(tA_YearBuffer,TA_YEAR_SIZE,"%.4d",value);
    tA_Year.invalidate();
}
void Screen1View::updateMonth(int value){
	Unicode::snprintf(tA_MonthBuffer,TA_MONTH_SIZE,"%.2d",value);
    tA_Month.invalidate();
}
void Screen1View::updateDay(int value){
	Unicode::snprintf(tA_DayBuffer,TA_DAY_SIZE,"%.2d",value);
    tA_Day.invalidate();
}
void Screen1View::updateHour(int value){
	Unicode::snprintf(tA_HourBuffer,TA_HOUR_SIZE,"%.2d",value);
    tA_Hour.invalidate();
}

void Screen1View::updateIcon( int request,char* value){
	if(request == 0){
		if (strcmp(value, "01d") == 0) {
			image2.setBitmap(touchgfx::Bitmap(BITMAP__01D_2X_ID));
		}
		if (strcmp(value, "01n") == 0) {
			image2.setBitmap(touchgfx::Bitmap(BITMAP__01D_2X_ID));
		}
		if (strcmp(value, "02d") == 0) {
			image2.setBitmap(touchgfx::Bitmap(BITMAP__02D_2X_ID));
		}
		if (strcmp(value, "02n") == 0) {
			image2.setBitmap(touchgfx::Bitmap(BITMAP__02D_2X_ID));
		}
		if (strcmp(value, "03d") == 0) {
			image2.setBitmap(touchgfx::Bitmap(BITMAP__03D_2X_ID));
		}
		if (strcmp(value, "03n") == 0) {
			image2.setBitmap(touchgfx::Bitmap(BITMAP__03D_2X_ID));
		}
		if (strcmp(value, "04d") == 0) {
			image2.setBitmap(touchgfx::Bitmap(BITMAP__04D_2X_ID));
		}
		if (strcmp(value, "04n") == 0) {
			image2.setBitmap(touchgfx::Bitmap(BITMAP__04D_2X_ID));
		}
		if (strcmp(value, "09d") == 0) {
			image2.setBitmap(touchgfx::Bitmap(BITMAP__09D_2X_ID));
		}
		if (strcmp(value, "09n") == 0) {
			image2.setBitmap(touchgfx::Bitmap(BITMAP__09N_2X_ID));
		}
		if (strcmp(value, "10d") == 0) {
			image2.setBitmap(touchgfx::Bitmap(BITMAP__10D_2X_ID));
		}
		if (strcmp(value, "10n") == 0) {
			image2.setBitmap(touchgfx::Bitmap(BITMAP__10N_2X__ID));
		}
		if (strcmp(value, "11d") == 0) {
			image2.setBitmap(touchgfx::Bitmap(BITMAP__11D_2X_ID));
		}
		if (strcmp(value, "11n") == 0) {
			image2.setBitmap(touchgfx::Bitmap(BITMAP__11N_2X_ID));
		}
		if (strcmp(value, "13d") == 0) {
			image2.setBitmap(touchgfx::Bitmap(BITMAP__13D_2X_ID));
		}
		if (strcmp(value, "13n") == 0) {
			image2.setBitmap(touchgfx::Bitmap(BITMAP__13N_2X_ID));
		}
		if (strcmp(value, "50d") == 0) {
			image2.setBitmap(touchgfx::Bitmap(BITMAP__50D_2X_ID));
		}
		if (strcmp(value, "50n") == 0) {
			image2.setBitmap(touchgfx::Bitmap(BITMAP__50N_2X_ID));
		}
		image2.invalidate();
	}
}
void Screen1View::updateMinute(int value){
	Unicode::snprintf(tA_MinuteBuffer,TA_DAY_SIZE,"%.2d",value);
    tA_Minute.invalidate();
}

// Funktion, um UTF-8 in UTF-16 zu konvertieren
void convertUtf8ToUtf16(const char* utf8, Unicode::UnicodeChar* utf16, uint16_t maxLength) {
    uint16_t i = 0;
    while (*utf8 && i < maxLength - 1) {
        uint8_t c = *utf8++;
        if (c < 0x80) {
            utf16[i++] = c; // ASCII-Zeichen
        } else if ((c & 0xE0) == 0xC0) {
            // 2-Byte-Sequenz
            uint8_t c2 = *utf8++;
            utf16[i++] = ((c & 0x1F) << 6) | (c2 & 0x3F);
        } else if ((c & 0xF0) == 0xE0) {
            // 3-Byte-Sequenz
            uint8_t c2 = *utf8++;
            uint8_t c3 = *utf8++;
            utf16[i++] = ((c & 0x0F) << 12) | ((c2 & 0x3F) << 6) | (c3 & 0x3F);
        }
    }
    utf16[i] = 0; // Null-Terminator hinzufügen
}

void Screen1View::updateCity(int request,char* guiCity){
	if(request == 0){
		convertUtf8ToUtf16(guiCity, tA_Outdoor_CityBuffer, 32);
		tA_Outdoor_City.setWildcard(tA_Outdoor_CityBuffer);
		tA_Outdoor_City.invalidate();
	}
}

/*void Screen1View::updateTemp(int request, float value){

	if(request == 0){
		Unicode::UnicodeChar tempBuffer[32];

		//Unicode::snprintfFloat(value, tA_Outdoor_TempBuffer,TA_OUTDOOR_TEMP_SIZE,"%.2f°C",value);
		Unicode::snprintfFloat(tempBuffer, 32, "%2.1f", value);
		convertUtf8ToUtf16(tempBuffer, tA_Outdoor_TempBuffer, 32);

		tA_Outdoor_Temp.setWildcard(tA_Outdoor_TempBuffer);
		tA_Outdoor_Temp.invalidate();
	}
}*/

void Screen1View::updateTemp(int request, float value)
{
    // 1) Puffer definieren
    static Unicode::UnicodeChar tempBuffer[32];

    // 2) Float in Unicode-String konvertieren

      Unicode::snprintfFloat(tempBuffer, 10, "%.1f°C", value);

    // 3) Den String als Wildcard setzen
    tA_Outdoor_Temp.setWildcard(tempBuffer);

    // 4) Text neu zeichnen
    tA_Outdoor_Temp.invalidate();
}

void Screen1View::updateDescription(int request,char* guiDescription){
	if(request == 0){
		// Konvertiere die UTF-8-Daten in UTF-16
		convertUtf8ToUtf16(guiDescription, tA_DescriptionBuffer, 32);
		tA_Description.setWildcard(tA_DescriptionBuffer);
		tA_Description.invalidate();
	}
  }

void Screen1View::updateSSID(char* guiSSID){
	//tA_SSID.setWildcard1(tA_SSIDBuffer);
	Unicode::snprintf(tA_SSIDBuffer, TA_SSID_SIZE, guiSSID);
	tA_SSID.invalidate();
}

void Screen1View::updateSSIDList(char* value)
{
	Unicode::snprintf(tA_SSIDListBuffer, TA_SSIDLIST_SIZE, value);

	tA_SSIDList.invalidate();
}

void Screen1View::hide_SSIDList(){
	tA_SSIDList.setVisible(false);
	tA_SSIDList.invalidate();
}
