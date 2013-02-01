#include "foodItem.h"
#include <map>

int main()
{
  std::map<std::string, assignment4::food_item> food_map;

  assignment4::food_item f("a", "b", 3);

  food_map["a"] = f;


}
