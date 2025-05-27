#ifndef SCREENKEYBOARD_CITYPRESENTER_HPP
#define SCREENKEYBOARD_CITYPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class ScreenKeyboard_CityView;

class ScreenKeyboard_CityPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    ScreenKeyboard_CityPresenter(ScreenKeyboard_CityView& v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();

    virtual ~ScreenKeyboard_CityPresenter() {}

private:
    ScreenKeyboard_CityPresenter();

    ScreenKeyboard_CityView& view;
};

#endif // SCREENKEYBOARD_CITYPRESENTER_HPP
