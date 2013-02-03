#ifndef WAREHOUSE_H
#define WAREHOUSE_H


#include <set>
#include <string>
#include <map>
#include <vector>
#include "dates.h"
#include "foodItem.h"

namespace assignment4
{
  class ware_house
  {
  public:
    ware_house();
    ware_house(std::string name);
    //ware_house(const ware_house & other);
    ~ware_house();

    //string is upc key; vector<food_items>
    std::map<std::string, food_item> food_set;
    // what food is at this warehouse
    std::string name; // warehouse name
    date d;
    int current_activity;

    // not going to work. need to somehow associate it with a day.
    // so maybe we need a date class
   

  private:
    
    
  };
}

#endif
