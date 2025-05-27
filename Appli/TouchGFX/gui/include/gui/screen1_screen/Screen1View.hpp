#ifndef SCREEN1VIEW_HPP
#define SCREEN1VIEW_HPP

#include <gui_generated/screen1_screen/Screen1ViewBase.hpp>
#include <gui/screen1_screen/Screen1Presenter.hpp>

class Screen1View : public Screen1ViewBase
{
public:
    Screen1View();
    virtual ~Screen1View() {}

    virtual void setupScreen();
    virtual void tearDownScreen();

    // Hier überschreibst du die Methode aus Screen1ViewBase:
    virtual void flexbuttonShow_SSIDs() override;
    //virtual void flexbuttonShow_SSIDs();

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
    void updateDescription(int request,char* guiDescription);
    void updateSSID(char* value);
    void updateSSIDList(char* value);
    void hide_SSIDList();


protected:
};

#endif // SCREEN1VIEW_HPP
