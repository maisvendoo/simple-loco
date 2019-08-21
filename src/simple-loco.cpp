#include    "simple-loco.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
SimpleLoco::SimpleLoco(QObject *parent) : Vehicle (parent)
  , ref_traction_level(0.0)
  , F_max(450.0)
  , F_nom(350.0)
  , V_nom(80.0)
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
SimpleLoco::~SimpleLoco()
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void SimpleLoco::keyProcess()
{
    if (getKeyState(KEY_A))
    {
        ref_traction_level += 0.01;
    }

    if (getKeyState(KEY_D))
    {
        ref_traction_level -= 0.01;
    }

    ref_traction_level = cut(ref_traction_level, 0.0, 1.0);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void SimpleLoco::step(double t, double dt)
{
    // Вычисляем силу тяги, которую реализует локомотив в данный момент
    double trac_force = ref_traction_level * trac_char(velocity);

    // Вычисляем момент, приходящийся на одну колесную пару
    double torque = trac_force * wheel_diameter / 2.0 / num_axis;

    // Задаем момент каждой колесной паре
    for (size_t i = 1; i < Q_a.size(); ++i)
    {
        Q_a[i] = torque;
    }

    analogSignal[194] = static_cast<float>(wheel_rotation_angle[0] / 2.0 / Physics::PI);
    analogSignal[195] = static_cast<float>(wheel_rotation_angle[1] / 2.0 / Physics::PI);
    analogSignal[196] = static_cast<float>(wheel_rotation_angle[2] / 2.0 / Physics::PI);
    analogSignal[197] = static_cast<float>(wheel_rotation_angle[3] / 2.0 / Physics::PI);
    analogSignal[198] = static_cast<float>(wheel_rotation_angle[4] / 2.0 / Physics::PI);
    analogSignal[199] = static_cast<float>(wheel_rotation_angle[5] / 2.0 / Physics::PI);

    DebugMsg = QString("Время: %1 с Зад. тяга: %2 Скорость: %3 км/ч Сила тяги: %4 кН")
            .arg(t, 10, 'f', 1)
            .arg(ref_traction_level, 4, 'f', 2)
            .arg(velocity * Physics::kmh, 6, 'f', 2)
            .arg(trac_force / 1000.0, 6, 'f', 1);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
double SimpleLoco::trac_char(double v)
{
    // Переводим номинальную скорость в м/с
    double v_nom = V_nom / Physics::kmh;
    double traction_force = 0;

    // Вычисляем силу тяги, в зависимости от величины
    // текущей скорости по отношению к номинальной.
    // Учитываем, что параметры заданной характеристики мы брали в кН,
    // а движку требуются величины в системе СИ, поэтому домножаем на 1000
    // переводя килоньютоны в ньютоны
    if (abs(v) < v_nom)
    {
        traction_force = (F_max + (F_nom - F_max) * abs(v) / v_nom) * 1000.0;
    }
    else
    {
        traction_force = F_nom * v_nom * 1000.0 / v;
    }

    return traction_force;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void SimpleLoco::loadConfig(QString cfg_path)
{
    // Создаем экземпляр "читателя" XML-конфигов
    CfgReader cfg;

    // Открываем конфигурационный файл по переданному движком пути
    if (cfg.load(cfg_path))
    {
        // Задаем имя секции конфига, из которой будем читать параметры
        QString sectionName = "Vehicle";

        // Читаем интересующие нас параметы в соотвествующие переменные
        cfg.getDouble(sectionName, "F_max", F_max);
        cfg.getDouble(sectionName, "F_nom", F_nom);
        cfg.getDouble(sectionName, "V_nom", V_nom);
    }
}

GET_VEHICLE(SimpleLoco)
