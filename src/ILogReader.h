//
// Created by null on 28.08.17.
//

#ifndef METAQUOTES_ILOGREADER_H
#define METAQUOTES_ILOGREADER_H

class ILogReader
{
public:

    virtual bool Open(const char*) = 0;         // открытие файла, false - ошибка
    virtual void Close() = 0;                   // закрытие файла
    virtual bool SetFilter(const char*) = 0;    // установка фильтра строк, false - ошибка
    virtual bool GetNextLine(char*,             // запрос очередной найденной строки,
                        const int) = 0;         // buf - буфер, bufsize - максимальная длина
                                                // false - конец файла или ошибка
};

#endif //METAQUOTES_ILOGREADER_H
