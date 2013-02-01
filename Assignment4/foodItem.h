#ifndef FOOD_H
#define FOOD_H

#include <string>



namespace assignment4
{

  class food_item
  {
  public:
    //constructor
    food_item(std::string name, std::string upc, int shelf_life);
    food_item(food_item & other);// copy
    ~food_item(); //destructor

    std::string location;
    std::string name;
    std::string upc;
    int shelf_life;
    int quantity;
    

  private:
    
  };
}

#endif
