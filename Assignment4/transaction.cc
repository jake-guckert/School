// make constructors

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
#include <set>
#include <ctime>
#include "wareHouse.h"
#include "foodItem.h"

using namespace std;

namespace assignment4
{

  /* ware_house::ware_house(std::string name)
     {
     //this->food_set = set<assignment4::food_item>;
     this->name = name;
     //this->dates = set<assignment4::date>; // don't know if need to be new
     }
     ware_house::ware_house(ware_house & rhs)
     {
     //this->food_set = NULL;
     this->name = NULL;
     //this->dates = NULL; // don't know if need to be new

     *this = rhs;

     }
     ware_house::~ware_house()
     {
     //maybe need a clean() like in utah_set
     }*/

  /*******************************************************************************/
  food_item::food_item(std::string name, string upc, 
		       int shelf_life)
  {
    this->name = name;
    this->upc = upc;
    this->shelf_life = shelf_life;

  }
  food_item::food_item(food_item & rhs)
  {
    this->name = "";
    this->upc = "";
    this->shelf_life = 0;

    *this = rhs;
  
  }
  food_item::~food_item()
  {
    //maybe need a clean() like in utah_set
  }
}

tm tim; // used for dates
set<ware_house> set_wh; // set of warehouses
// create a dictionary of food items

  /********************************************************************************/

int main(int argc, char** argv)
{
  fstream in(argv[1]);

  printf("Report by Jake Guckert, Josh Bell!!!!!!!\n\n");

  //Read in and sort data
  while(true)
    {
      std::string word;
      string line;
      
      getline(in, line, ' ');

      if(line.compare("FoodItem") == 0)
	{
	  //UPC
	  getline(in, line, ':');
	  getline(in, line, ' ');
	  getline(in, line, ' ');
	  
	  std::string upc = line;

	  getline(in, line, ':');
	  getline(in, line, ' ');
	  getline(in, line, ' ');

	  int shelf_life = atoi(line.c_str());

	  getline(in, line, ':');
	  getline(in, line, ' ');
	  getline(in, line);

	  std::string name = line;

	  assignment4::food_item fi(name, upc, shelf_life);
	  // add dictionary of food_itme
	}
      
      else if(line.compare("Warehouse")==0)
	{
	  getline(in, line, '-');
	  getline(in, line, ' ');
	  getline(in, line);
	  
	  //Add line to warehouse?????????????????????
	  
	}
      else if(line.compare("Start")==0)
	{
	  getline(in, line, ':');
	  getline(in, line, ' ');
	  getline(in, line, '/');

	  tim.tm_mon = atoi(line.c_str());
	  getline(in, line, '/');
	  tim.tm_mday = atoi(line.c_str());
	  getline(in, line);
	  tim.tm_year = atoi(line.c_str());

	}
      else if(line.compare("Receive:")==0)
	{
	  // make a new food item looked up by the upc and add quantity and warehous etc

	  //UPC
	  getline(in, line, ' ');
	  // add item quantity to this upc
	  
	  //quantity
	  getline(in, line, ' ');

	  //warehouse
	  getline(in, line);

	}

      else if(line.compare("Request:")==0) // add item quantity to this upc at this 
	                             //warehouse
	{
	  //UPC
	  getline(in, line, ' ');
	  
	  //quantity
	  getline(in, line, ' ');

	  //warehouse
	  getline(in, line);

	  //look by warehouse, by upc and then minus quantity
	}

      else if(line.compare("Next")==0)
	{
	  // add one to whatever day it is
	  getline(in, line);
	  tim.tm_mday += 1; //adds one day
	  mktime(&tim); //refactor months and adjusts

	}

      if(line.compare("End")==0)// deal with extra spaces after END!!!!
	{
	  cout << "file complete" << endl;
	  break;
	}

      if(in.fail())
	{
	  cout << "Failed" << endl;
	  break;
	}
    }

}
