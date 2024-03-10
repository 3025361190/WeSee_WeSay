#include "FileSystem.h"

FileSystem::FileSystem()
{
    //文件对象初始化
    index = new QFile(indexPath);
    data = new QFile(dataPath);

    //用读写方式打开文件
    index->open(QIODevice::ReadWrite | QIODevice::Text);
    data->open(QIODevice::ReadWrite | QIODevice::Text);

    //初始化文件流对象
    indexStream = new QTextStream(index);
    dataStream = new QTextStream(data);
    //设定编码格式为“UTF-8”
    indexStream->setCodec("UTF-8");
    indexStream->setCodec("UTF-8");

    //创建链表
    indexLink = new DataNode();
    indexLink->next = nullptr;
    indexLink->id = -1;

    //初始化链表
    QString line = indexStream->readLine();
    while (!line.isNull()) {

        //创建新节点
//        tempptr->next = new DataNode();
//        tempptr = tempptr->next;
//        tempptr->next = nullptr;

        DataNode * newNode = new DataNode();
        newNode->next = indexLink->next;
        indexLink->next = newNode;


        //读取id
        //qDebug() << line;
        indexLink->next->id = line.toInt();

        //读取下一行
        line = indexStream->readLine();

        //读取dataPosition
        //qDebug() << line;
        indexLink->next->dataPosition = line.toInt();


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
        line = indexStream->readLine();
    }
}

FileSystem::~FileSystem()
{
    index->close();
    data->close();

    index->open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text);

    DataNode * tempptr = indexLink;
    while(tempptr->next != nullptr)
    {
        *indexStream << tempptr->next->id << "\n" << tempptr->next->dataPosition << "\n";

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
    dataStream->seek(data->size());
    *dataStream << newData.ToString() << "\n";
    //将newdata的id和currentPosition写入索引文件
    indexStream->seek(index->size());
    *indexStream << newData.id << "\n" << currentPosition << "\n";

    //新建链表节点
    DataNode * newNode = new DataNode();
    newNode->next = indexLink->next;
    indexLink->next = newNode;

    //将newdata的id和currentPosition存入链表
    indexLink->next->id = newData.id;
    indexLink->next->dataPosition = currentPosition;
}
//删
void FileSystem::DeleteRecord(int id)
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
void FileSystem::ModifyRecord(int id, Data newData)
{
    DeleteRecord(id);
    AddRecord(newData);
}
//查
Data FileSystem::FindRecord(int id)
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
    dataStream->seek(targetPosition);
    QString targetData = dataStream->readLine();
    targetData.resize(targetData.size() - 1);
    return Data::FromString(targetData);
}
