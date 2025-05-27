#include <gui/screenkeyboard_city_screen/ScreenKeyboard_CityView.hpp>

extern Unicode::UnicodeChar keyboardBuffer_City[25];//add

extern "C" void storeBuffer_City(const char*cityUTF8);

ScreenKeyboard_CityView::ScreenKeyboard_CityView()
{
    keyboard.setPosition(5, 5, 640, 480);//add
	add(keyboard);//add
}

void ScreenKeyboard_CityView::setupScreen()
{
    ScreenKeyboard_CityViewBase::setupScreen();
}

void ScreenKeyboard_CityView::tearDownScreen()
{
    ScreenKeyboard_CityViewBase::tearDownScreen();
}

void ScreenKeyboard_CityView::getBuffer_City()
{
	static const int MAX_CITY = 25;
	char cityUTF8[MAX_CITY];

	Unicode::UnicodeChar* buff = keyboard.getBuffer();
	Unicode::strncpy(keyboardBuffer_City, buff, Unicode::strlen(buff)+1);

	touchgfx::Unicode::toUTF8(keyboardBuffer_City, reinterpret_cast<uint8_t*>(cityUTF8), MAX_CITY);

	storeBuffer_City(cityUTF8);

}

