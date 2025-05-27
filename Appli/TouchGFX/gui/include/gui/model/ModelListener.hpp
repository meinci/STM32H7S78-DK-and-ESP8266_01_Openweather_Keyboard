#ifndef MODELLISTENER_HPP
#define MODELLISTENER_HPP

#include <gui/model/Model.hpp>
#include <touchgfx/hal/Types.hpp>

class ModelListener
{
public:
    ModelListener() : model(0) {}
    
    virtual ~ModelListener() {}

    void bind(Model* m)
    {
        model = m;
    }
    virtual void updateTemp(int request, float value){}
    virtual void updateHumi(int request,int value){}
    virtual void updateCity(int request,char* guiCity){}
    virtual void updatePres(int request,int value){}
    virtual void updateYear(int value){}
    virtual void updateMonth(int value){}
    virtual void updateDay(int value){}
    virtual void updateHour(int value){}
    virtual void updateMinute(int value){}
    virtual void updateIcon(int request,char* value){}
    virtual void updateDescription(int request,char* value){}
    virtual void updateSSID(char* value){}
    virtual void updateSSIDList(char* value){}

protected:
    Model* model;
};

#endif // MODELLISTENER_HPP
