#ifndef DATE_H
#define DATE_H

#include <QString>
#include <ctime>

class Date
{
public:
    static QString getCurrentDate()
    {
        time_t rawtime;
        struct tm *timeinfo;
        char buffer[11];

        time(&rawtime);
        timeinfo = localtime(&rawtime);

        strftime(buffer, 11, "%Y-%m-%d", timeinfo);
        return QString(buffer);
    }
};

#endif // DATE_H
