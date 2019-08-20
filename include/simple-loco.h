#ifndef     SIMPLE_LOCO_H
#define     SIMPLE_LOCO_H

#include    "vehicle-api.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class SimpleLoco : public Vehicle
{
public:

    /// Конструктор класса
    SimpleLoco(QObject *parent = Q_NULLPTR);

    /// Деструктор класса
    ~SimpleLoco();

private:

    /// Обработка нажатия клавиш
    void keyProcess();
};

#endif // SIMPLE_LOCO_H
