//
// Created by chanming on 16/5/8.
//

#ifndef UNTITLED_KV_FILE_H
#define UNTITLED_KV_FILE_H


class KVFile {
private:
    int m_fileId;
    int InnerWrite(char* data, int size);
public:
    int GetFileId();
    KVFile(char* fileName);
    ~KVFile();
    char* Read();
    int Write(char* data, int size);
    /**
     * 从offset的位置开始,读取一个数据
     */
    struct KVDO* ReadOneData(int &offset);
};


#endif //UNTITLED_KV_FILE_H
