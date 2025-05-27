#ifndef SCREENKEYBOARD_CITYVIEW_HPP
#define SCREENKEYBOARD_CITYVIEW_HPP

#include <gui_generated/screenkeyboard_city_screen/ScreenKeyboard_CityViewBase.hpp>
#include <gui/screenkeyboard_city_screen/ScreenKeyboard_CityPresenter.hpp>
#include <gui/common/CustomKeyboard.hpp>//add
#include <touchgfx/Unicode.hpp>

class ScreenKeyboard_CityView : public ScreenKeyboard_CityViewBase
{
public:
    ScreenKeyboard_CityView();
    virtual ~ScreenKeyboard_CityView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void getBuffer_City();//add

protected:
    CustomKeyboard keyboard;//add
};

#endif // SCREENKEYBOARD_CITYVIEW_HPP
