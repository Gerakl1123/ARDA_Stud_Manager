#include "dataschedule.h"


DataSchedule::DataMapLessonTime DataSchedule::intanceTimeLessonDefault()
{

    lessonsTime[1] = {QTime{8,30}, QTime{10,05}};
    lessonsTime[2] = {QTime{10,15},QTime{11,50}};
    lessonsTime[3] = {QTime{12,30},QTime{14,05}};
    lessonsTime[4] = {QTime{14,15},QTime{15,50}};
    lessonsTime[5] = {QTime{16,00},QTime{17,35}};
    lessonsTime[6] = {QTime{17,45},QTime{19,20}};
    lessonsTime[7] = {QTime{19,30},QTime{21,05}};
    lessonsTime[8] = {QTime{21,15},QTime{22,50}};

    return lessonsTime;
}
