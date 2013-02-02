#include "foodItem.h"
#include <map>
#include <iostream>

int main()
{
  std::map<std::string, assignment4::food_item> food_map;

  assignment4::food_item f("a", "b", 3);

  food_map["a"] = f;

}
