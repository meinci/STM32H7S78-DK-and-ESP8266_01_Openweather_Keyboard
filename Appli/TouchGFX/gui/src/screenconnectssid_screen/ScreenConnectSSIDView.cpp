#include <gui/screenconnectssid_screen/ScreenConnectSSIDView.hpp>
#include <cstring>

#include "wifi_credentials.h"

extern "C" void storeSSIDPassword(const char* ssid, const char* password);

Unicode::UnicodeChar keyboardBuffer[2][25];//add
uint8_t keyboardSelection = 0;

ScreenConnectSSIDView::ScreenConnectSSIDView()
{

}

void ScreenConnectSSIDView::setupScreen()
{
    ScreenConnectSSIDViewBase::setupScreen();
}

void ScreenConnectSSIDView::tearDownScreen()
{
    ScreenConnectSSIDViewBase::tearDownScreen();
}

void ScreenConnectSSIDView::keyboardSelected(uint8_t value)
{
	keyboardSelection = value;
}

void ScreenConnectSSIDView::updateScreen()
{
	if(Unicode::strlen(keyboardBuffer[0]) > 0)
		{
			memset(&textAreaSSIDBuffer, 0, TEXTAREASSID_SIZE * sizeof(Unicode::UnicodeChar));
			Unicode::strncpy(textAreaSSIDBuffer, keyboardBuffer[0], TEXTAREASSID_SIZE - 1);
			textAreaSSIDBuffer[TEXTAREASSID_SIZE-1] = '\0'; // make sure last index is null
			textAreaSSID.invalidate();
		}
	if(Unicode::strlen(keyboardBuffer[1]) > 0)
		{
			char temp[25] = {0};
			uint8_t n = Unicode::strlen(keyboardBuffer[1]);
			Unicode::UnicodeChar unicodeBuf[25] = {0};
			memset(temp, '*', n);
			Unicode::fromUTF8((uint8_t*)temp, unicodeBuf, Unicode::strlen(keyboardBuffer[1]));
			memset(&textAreaPaswordBuffer, 0, TEXTAREAPASWORD_SIZE * sizeof(Unicode::UnicodeChar));
			Unicode::strncpy(textAreaPaswordBuffer, unicodeBuf, TEXTAREAPASWORD_SIZE - 1);
			textAreaPaswordBuffer[TEXTAREAPASWORD_SIZE-1] = '\0'; // make sure last index is null
			textAreaPasword.invalidate();
		}
}


void ScreenConnectSSIDView::connect_SSID()
{
    // keyboardBuffer[0] enthält SSID, keyboardBuffer[1] enthält Passwort (UnicodeChar-Array)
    static const int MAX_SSID = 32+1;
    static const int MAX_PASS = 32+1;
    char ssidUTF8[MAX_SSID];
    char passUTF8[MAX_PASS];

    // UnicodeChar zu UTF-8 konvertieren; reinterpret_cast wegen signierte/unsignierte Bytes
    touchgfx::Unicode::toUTF8(keyboardBuffer[0], reinterpret_cast<uint8_t*>(ssidUTF8), MAX_SSID);
    touchgfx::Unicode::toUTF8(keyboardBuffer[1], reinterpret_cast<uint8_t*>(passUTF8), MAX_PASS);

    // SSID und Passwort an C-Funktion übergeben
    storeSSIDPassword(ssidUTF8, passUTF8);
}







