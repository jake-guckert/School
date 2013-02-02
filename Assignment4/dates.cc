#include "dates.h"
#include <ctime>
#include <string>

namespace assignment4
{

  date::date(&int month, &int day, &int year,  int activity)
  {
    this->month = month;
    this->day = day; 
    this->year = year;
    this->activity = activity;
  }


  date::date()
  {

  }
}
