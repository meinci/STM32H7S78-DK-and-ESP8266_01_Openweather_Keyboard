#include <gui/screenkeyboard_screen/ScreenKeyboardView.hpp>

extern Unicode::UnicodeChar keyboardBuffer[2][25];//add
extern uint8_t keyboardSelection;//add

ScreenKeyboardView::ScreenKeyboardView()
{
	keyboard.setPosition(5, 5, 640, 480);//add
	add(keyboard);//add
}

void ScreenKeyboardView::setupScreen()
{
    ScreenKeyboardViewBase::setupScreen();
}

void ScreenKeyboardView::tearDownScreen()
{
    ScreenKeyboardViewBase::tearDownScreen();
}

void ScreenKeyboardView::getBuffer(){//add
	Unicode::UnicodeChar* buff = keyboard.getBuffer();
	Unicode::strncpy(keyboardBuffer[keyboardSelection], buff, Unicode::strlen(buff)+1);
}
