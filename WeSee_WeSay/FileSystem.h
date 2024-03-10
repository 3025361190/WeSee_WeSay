#ifndef FILESYSTEM_H
#define FILESYSTEM_H
#include <QFile>
#include <QDebug>
#include <QDate>
#include <QTextStream>
#include "Data.h"

//链表节点结构体定义
typedef struct DataNode{
    int id;
    int dataPosition;
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
    QString indexPath = "index.txt";
    QString dataPath = "data.txt";

    //两个文件的QFile对象
    QFile *index;
    QFile *data;

    //两个文件流对象
    QTextStream *indexStream;
    QTextStream *dataStream;

    //索引链表头指针(带空节点)
    IndexPtr indexLink;

    //增删改查函数声明
    void AddRecord(Data newData);
    void DeleteRecord(int id);
    void ModifyRecord(int id, Data newData);
    Data FindRecord(int id);
};

#endif // FILESYSTEM_H
