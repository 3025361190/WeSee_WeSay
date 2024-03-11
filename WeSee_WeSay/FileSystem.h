#ifndef FILESYSTEM_H
#define FILESYSTEM_H
#include <QFile>
#include <QDebug>
#include <QDate>
#include <QDataStream>
#include "Data.h"

//链表节点结构体定义
typedef struct DataNode{
    qint64 id;
    qint64 dataPosition;
    //QString name;
    //QDate birthday;
    //QString describe;
    struct DataNode * next;
}DataNode, *IndexPtr;

class FileSystem
{
public:
    FileSystem();
    ~FileSystem();

    //索引文件及数据文件路径定义
    QString indexPath = "index.bin";
    QString dataPath = "data.bin";

    //两个文件的QFile对象
    QFile *index;
    QFile *data;

    //两个文件流对象
    QDataStream *indexStream;
    QDataStream *dataStream;

    //索引链表头指针(带空节点)
    IndexPtr indexLink;

    //增删改查函数声明
    void AddRecord(Data newData);
    void DeleteRecord(qint64 id);
    void ModifyRecord(qint64 id, Data newData);
    Data FindRecord(qint64 id);
};

#endif // FILESYSTEM_H
