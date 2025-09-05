#ifndef PASSPORT_H
#define PASSPORT_H
#include"Data.h"

class PassPort : public Data
{
private:
    QString adress;
    QString DateVidachi;
    QString CodePodrazdelenia;
    QString KemVidan;
    QString seria;
    QString nomer;


public:
    PassPort();

    ~PassPort() override = default;
};

#endif // PASSPORT_H
