#include "dates.h"
#include <string>

namespace assignment4
{

  date::date()
  {
  }

  date::date(std::string d)
  {
    this->d = d;
    this->activity = 0;
    
  }
}
