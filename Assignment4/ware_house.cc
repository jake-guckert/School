#include "ware_house.h"


namespace assignment4
{
  ware_house::ware_house()
  {
  }

  ware_house::ware_house(std::string name)
     {
       this->name = name;
       this->current_activity = 0;
     }

  /*ware_house::ware_house(const ware_house & rhs)
     {
       this->name = "";
       this->activity = 0;

       //*this = rhs;// fix this???????????????????
       }*/
     ware_house::~ware_house()
     {
     //maybe need a clean() like in utah_set
     }
}
