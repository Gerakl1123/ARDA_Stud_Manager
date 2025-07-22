 #ifndef ATTESTATCONTEST_H
 #define ATTESTATCONTEST_H
 #include"Contest.h"


 class Attestat : public ContestBase
 {
 public:
   explicit Attestat(const std::string& logFile)
         : ContestBase(logFile) {};

     Attestat() = delete;

 public:

   virtual qint16 findWinner(double score, const QString& file, const QString& saveFile, QString& faculty) override;


 };



 #endif // ATTESTATCONTEST_H
