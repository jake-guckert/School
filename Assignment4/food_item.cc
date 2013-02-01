#include "foodItem.h"
#include <string>

namespace assignment4
{
  food_item::food_item(std::string name, std::string upc, int shelf_life)
  {
    this->name = name;
    this->upc = upc;
    this->shelf_life = shelf_life;
    this->location = "";
    this->quantity = 0;

  }
  /*food_item::food_item(const food_item & other)
  {
    other.name = this->name;
    other.upc = this->upc;
    other.location = this->location;
    //other.shelf_life = this->shelf_life;
    //other.quantity = this->quantity;
    }*/

  food_item::~food_item()
  {
    //maybe need a clean() like in utah_set
  }

  food_item::food_item()
  {
  }
}
