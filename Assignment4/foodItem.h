#include <string>

#ifndef FOOD_H
#define FOOD_H

namespace assignment4
{

  class food_item
  {
  public:
    //constructor
    food_item(int quantity, const std::string name, const int upc, int shelf_life);
    food_item(const food_item & other);// copy
    ~food_item(); //destructor

    int quantity;
    const std::string name;
    const int upc;
    int shelf_life;

  private:
    
  };
}

#endif
