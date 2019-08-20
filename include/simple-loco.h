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

    /// Заданный уровень тягового усилия
    double ref_traction_level;

    /// Максимальная реализуемая сила тяги, кН
    double F_max;

    /// Номинальная сила тяги (соотвествующая продолжительной мощности), кН
    double F_nom;

    /// Номинальная скорость (соотвествующая часовой мощности), км/ч
    double V_nom;

    /// Обработка нажатия клавиш
    void keyProcess();

    /// Шаг моделирования систем локомотива
    void step(double t, double dt);

    /// Расчет тяговой характеристики
    double trac_char(double v);

    /// Загрузка пользовательских параметров из конфига
    void loadConfig(QString cfg_path);
};

#endif // SIMPLE_LOCO_H
