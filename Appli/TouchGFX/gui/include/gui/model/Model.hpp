#ifndef MODEL_HPP
#define MODEL_HPP

#include <stdint.h>
#include <touchgfx/Unicode.hpp>


class ModelListener;

class Model
{
public:
    Model();

    void bind(ModelListener* listener)
    {
        modelListener = listener;
    }
    // Diese Methode wird später vom Presenter aufgerufen
    void show_SSIDs();

    void tick();
    void scanSSIDs();  // Neue Methode, die später myScanFunctionInC() aufruft

protected:
    ModelListener* modelListener;
};

#endif // MODEL_HPP
