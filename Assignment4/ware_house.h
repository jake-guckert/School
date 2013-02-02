#ifndef WAREHOUSE_H
#define WAREHOUSE_H


#include <set>
#include <string>
#include "dates.h"
#include "foodItem.h"

namespace assignment4
{
  class ware_house
  {
  public:
    ware_house(std::string name);
    //ware_house(const ware_house & other);
    ~ware_house();

    
    std::set<food_item> food_set; // what food is at this warehouse
    std::string name; // warehouse name

    // not going to work. need to somehow associate it with a day.
    // so maybe we need a date class
    int activity; // to count the number of requests and recieves
   

  private:
    
    
  };
}

#endif
