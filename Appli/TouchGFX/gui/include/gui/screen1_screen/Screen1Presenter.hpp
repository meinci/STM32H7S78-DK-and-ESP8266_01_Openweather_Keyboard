#ifndef SCREEN1PRESENTER_HPP
#define SCREEN1PRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class Screen1View;

class Screen1Presenter : public touchgfx::Presenter, public ModelListener
{
public:
    Screen1Presenter(Screen1View& v);

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

    // Methode, die aus der View beim Button-Klick gerufen wird
    void buttonClicked();

    virtual ~Screen1Presenter() {}
    void updateTemp(int request, float value);
    void updateHumi(int request,int value);
    void updatePres(int request,int value);
    void updateCity(int request,char* guiCity);
    void updateYear(int value);
    void updateMonth(int value);
    void updateDay(int value);
    void updateHour(int value);
    void updateMinute(int value);
    void updateIcon(int request,char* value);
    void updateDescription(int request,char* value);
    void updateSSID(char* value);
    void updateSSIDList(char* value);
    void hide_SSIDList();




private:
    Screen1Presenter();

    Screen1View& view;
};

#endif // SCREEN1PRESENTER_HPP
