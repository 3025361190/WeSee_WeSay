#ifndef DATA_H
#define DATA_H
#include <QString>
#include <QDate>
#include <QDebug>



class Data
{
public:
    Data();
    Data(int id, QString name, QDate birthday, QString describe);

    //数据域
    int id;
    QString name;
    QDate birthday;
    QString describe;


    QString ToString() const;
    static Data FromString(const QString& str);

};

#endif // DATA_H
