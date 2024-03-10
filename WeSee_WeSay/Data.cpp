#include "Data.h"

Data::Data()
{
    id = -1;
}

Data::Data(int id, QString name, QDate birthday, QString describe)
{
    this->id = id;
    this->name = name;
    this->birthday = birthday;
    this->describe = describe;
}

QString Data::ToString() const {
    //连接字符串
    QString result = QString::number(id) + "/" + name + "/" + birthday.toString(Qt::ISODate) + "/" + describe;
    return result;
}

Data Data::FromString(const QString& str) {
    //分割字符串
    QStringList parts = str.split('/');
    if (parts.size() != 4) {
        qDebug() << "Invalid input format";
        return Data();
    }

    Data newData;
    newData.id = parts[0].toInt();
    newData.name = parts[1];
    newData.birthday = QDate::fromString(parts[2], Qt::ISODate);
    newData.describe = parts[3];
    return newData;
}

