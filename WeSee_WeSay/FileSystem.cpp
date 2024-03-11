#include "FileSystem.h"

FileSystem::FileSystem()
{
    //文件对象初始化
    index = new QFile(indexPath);
    data = new QFile(dataPath);

    //用读写方式打开文件
    index->open(QIODevice::ReadWrite);
    data->open(QIODevice::ReadWrite);

    //初始化文件流对象
    indexStream = new QDataStream(index);
    dataStream = new QDataStream(data);
    //设置数据流版本
    indexStream->setVersion(QDataStream::Qt_5_14);
    dataStream->setVersion(QDataStream::Qt_5_14);


    //创建链表
    indexLink = new DataNode();
    indexLink->next = nullptr;
    indexLink->id = -1;

    //初始化链表
    while (!indexStream->atEnd()) {

        DataNode * newNode = new DataNode();
        newNode->next = indexLink->next;
        indexLink->next = newNode;

        //读取id
        //qDebug() << line;
        //indexLink->next->id = line.toInt();

        *indexStream >> indexLink->next->id;

        //读取下一行
        //line = indexStream->readLine();

        //读取dataPosition
        //qDebug() << line;
        //indexLink->next->dataPosition = line.toInt();

        *indexStream >> indexLink->next->dataPosition;

//        //读取name
//        qDebug() << line;
//        line = indexStream->readLine();
//        line.resize(line.size() - 1);
//        tempptr->name = line;

//        //读取birthday
//        qDebug() << line;
//        line = indexStream->readLine();
//        tempptr->birthday = QDate::fromString(line, Qt::ISODate);

//        //读取describe
//        qDebug() << line;
//        line = indexStream->readLine();
//        line.resize(line.size() - 1);
//        tempptr->describe = line;

        //读取下一行
        //line = indexStream->readLine();
    }
}

FileSystem::~FileSystem()
{
    index->close();
    data->close();

    index->open(QIODevice::WriteOnly | QIODevice::Truncate);

    DataNode * tempptr = indexLink;
    while(tempptr->next != nullptr)
    {
        *indexStream << tempptr->next->id << tempptr->next->dataPosition;

        tempptr = tempptr->next;
    }

    index->close();
}

//增
void FileSystem::AddRecord(Data newData)
{
    //记录当前记录存放在数据文件中的位置
    int currentPosition = data->size();
    //将newData写入数据文件
    data->seek(currentPosition);
    QString targetString = newData.ToString();
    *dataStream << targetString.toUtf8();
    qDebug() << "二进制：" <<targetString.toUtf8();
    if(!data->flush())
    {
        qDebug() << "数据插入失败";
        return;
    }
    qDebug() << "文件：" << data->size();
    //将newdata的id和currentPosition写入索引文件
    index->seek(index->size());
    *indexStream << newData.id << currentPosition;
    if(!index->flush())
    {
        qDebug() << "索引插入失败";
        data->resize(currentPosition);
        return;
    }


    //新建链表节点
    DataNode * newNode = new DataNode();
    newNode->next = indexLink->next;
    indexLink->next = newNode;

    //将newdata的id和currentPosition存入链表
    indexLink->next->id = newData.id;
    indexLink->next->dataPosition = currentPosition;
}
//删
void FileSystem::DeleteRecord(qint64 id)
{
    DataNode * tempptr = indexLink;
    while(tempptr->next != nullptr)
    {
        if(tempptr->next->id == id)
        {
            DataNode * targetNode = tempptr->next;
            tempptr->next = tempptr->next->next;
            delete targetNode;
            return;
        }

        tempptr = tempptr->next;
    }

    qDebug() << "没有找到对应记录";
    return;
}
//改
void FileSystem::ModifyRecord(qint64 id, Data newData)
{
    DeleteRecord(id);
    AddRecord(newData);
}
//查
Data FileSystem::FindRecord(qint64 id)
{
    int targetPosition = -1;
    DataNode * tempptr = indexLink;
    while(tempptr->next != nullptr)
    {
        if(tempptr->next->id == id)
        {
            targetPosition = tempptr->next->dataPosition;
            break;
        }

        tempptr = tempptr->next;
    }
    if(targetPosition == -1)
    {
        qDebug() << "未找到该记录";
        return Data();
    }
    data->seek(targetPosition);
    QByteArray targetData;
    *dataStream >> targetData;
    QString targetString = QString::fromUtf8(targetData);
    return Data::FromString(targetString);
}
