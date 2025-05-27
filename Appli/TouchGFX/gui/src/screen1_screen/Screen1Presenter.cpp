#include <gui/screen1_screen/Screen1View.hpp>
#include <gui/screen1_screen/Screen1Presenter.hpp>

Screen1Presenter::Screen1Presenter(Screen1View& v)
    : view(v)
{

}

void Screen1Presenter::activate()
{

}

void Screen1Presenter::deactivate()
{

}

void Screen1Presenter::updateTemp(int request, float value){
	view.updateTemp(request, value);

}

void Screen1Presenter::updateHumi(int request,int value){
	view.updateHumi(request,value);
}
void Screen1Presenter::updatePres(int request,int value){
	view.updatePres(request,value);
}

void Screen1Presenter::updateCity(int request,char* guiCity){
	view.updateCity(request,guiCity);
}

void Screen1Presenter::updateYear(int value){
	view.updateYear(value);
}

void Screen1Presenter::updateMonth(int value){
	view.updateMonth(value);
}

void Screen1Presenter::updateDay(int value){
	view.updateDay(value);
}

void Screen1Presenter::updateHour(int value){
	view.updateHour(value);
}

void Screen1Presenter::updateMinute(int value){
	view.updateMinute(value);
}

void Screen1Presenter::updateIcon(int request,char* value){
	view.updateIcon(request,value);
}

void Screen1Presenter::updateDescription(int request,char* value){
	view.updateDescription(request,value);
}

void Screen1Presenter::updateSSID(char* value){
	view.updateSSID(value);
}
void Screen1Presenter::updateSSIDList(char* value){
	view.updateSSIDList(value);
}

void Screen1Presenter::buttonClicked()
{
    // Hier rufen wir unsere Model-Methode auf, z. B. scanSSIDs()
    model->scanSSIDs();
}

void Screen1Presenter::hide_SSIDList()
{
	view.hide_SSIDList();
}




