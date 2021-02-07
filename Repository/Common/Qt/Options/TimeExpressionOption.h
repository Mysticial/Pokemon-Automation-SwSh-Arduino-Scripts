/*  Time Option
 *
 *  From: https://github.com/Mysticial/Pokemon-Automation-SwSh-Arduino-Scripts
 *
 */

#ifndef PokemonAutomation_TimeExpressionOption_H
#define PokemonAutomation_TimeExpressionOption_H

#include <QJsonValue>
#include <QLineEdit>

template <typename Type>
class TimeExpressionOption{
public:
    TimeExpressionOption(
        QString label,
        Type min_value,
        Type max_value,
        QString default_value
    );
    void load_default(const QJsonValue& json);
    void load_current(const QJsonValue& json);
    QJsonValue write_default() const;
    QJsonValue write_current() const;

    operator Type() const{ return m_value; }
    Type value() const{ return m_value; }

    bool is_valid() const;
    void restore_defaults();
    bool update();

private:
    bool set_value(const QString& str);
    QString time_string() const;

protected:
    template <typename> friend class TimeExpressionOptionUI;
    const QString m_label;
    const Type m_min_value;
    const Type m_max_value;
    QString m_default;
    QString m_current;

    Type m_value;
    QString m_error;
};


template <typename Type>
class TimeExpressionOptionUI : public QWidget{
public:
    TimeExpressionOptionUI(QWidget& parent, TimeExpressionOption<Type>& value);
    void restore_defaults();

private:
    TimeExpressionOption<Type>& m_value;
    QLineEdit* m_box;
};

#endif

