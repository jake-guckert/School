#ifndef WAREHOUSE_H
#define WAREHOUSE_H


#include <set>
#include <string>
#include "date.h"
#include "foodItem.h"

namespace assignment4
{
  class ware_house
  {
  public:
    ware_house(std::string name);
    ware_house(ware_house & other);
    ~ware_house();

    
    std::set<food_item> food_set; 
    std::string name;
    std::set<date> dates;
   

  private:
    
    
  };
}

#endif
