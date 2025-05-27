#ifndef SCREENCONNECTSSIDVIEW_HPP
#define SCREENCONNECTSSIDVIEW_HPP

#include <gui_generated/screenconnectssid_screen/ScreenConnectSSIDViewBase.hpp>
#include <gui/screenconnectssid_screen/ScreenConnectSSIDPresenter.hpp>
#include <touchgfx/Unicode.hpp>
typedef uint16_t UnicodeChar;

class ScreenConnectSSIDView : public ScreenConnectSSIDViewBase
{
public:
    ScreenConnectSSIDView();
    void onUserConfirmedInput();

    virtual ~ScreenConnectSSIDView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void keyboardSelected(uint8_t value);
    virtual void updateScreen();
    virtual void connect_SSID();

protected:
};

#endif // SCREENCONNECTSSIDVIEW_HPP
