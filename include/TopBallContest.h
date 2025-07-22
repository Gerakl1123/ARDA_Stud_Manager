#ifndef TOPBALLCONTEST_H
#define TOPBALLCONTEST_H
#include"Contest.h"

class TopContest : public ContestBase
{
public:
  explicit TopContest(const std::string& logFile)
        : ContestBase(logFile) {};


public:

    Student TopBall(const QString &ifile, const QString &saveFile);

    qint16 findWinner(double score, const QString& file, const QString& saveFile, QString& faculty) override;

};

#endif // TOPBALLCONTEST_H
