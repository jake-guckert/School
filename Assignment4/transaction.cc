// make constructors

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
#include <set>
#include <map>
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
    this->location = "";
    this->quantity = 0;

  }
  food_item::food_item(food_item & rhs)
  {
    this->name = "";
    this->upc = "";
    this->shelf_life = 0;
    this->location = "";
    this->quantity = 0;

    *this = rhs;
  
  }
  food_item::~food_item()
  {
    //maybe need a clean() like in utah_set
  }

  food_item::food_item()
  {
  }
}

tm tim; // used for dates
//map<assignment4::ware_house> wh_map; // set of warehouses
// create a dictionary of food items
map<string, assignment4::food_item> food_map;

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

      //Create a new food_item and add to the map of foods
      if(line.compare("FoodItem") == 0)
	{
	  //UPC
	  getline(in, line, ':');
	  getline(in, line, ' ');
	  getline(in, line, ' ');
	  
	  std::string upc = line;

	  //Shelf-life
	  getline(in, line, ':');
	  getline(in, line, ' ');
	  getline(in, line, ' ');

	  int shelf_life = atoi(line.c_str());

	  //Food name
	  getline(in, line, ':');
	  getline(in, line, ' ');
	  getline(in, line);

	  std::string name = line;

	  assignment4::food_item fi(name, upc, shelf_life);
	  	  
	  // add dictionary of food_item
	  //food_map.insert(pair<string, assignment4::food_item>(upc,fi));
	}

      //Make a new warehouse with the name provided
      // Add warehouse to map of warehouses
      else if(line.compare("Warehouse")==0)
	{
	  getline(in, line, '-');
	  getline(in, line, ' ');
	  getline(in, line);
	  
	  // create new warehouse
	  //assignment4::ware_house wh(line);
	  
	  //Add warehouse to set of warehouses
	  //wh_map.insert(line);
	  
	}

      //initailize the timer for the particular date
      else if(line.compare("Start")==0)
	{
	  getline(in, line, ':');
	  getline(in, line, ' ');
	  getline(in, line, '/');

	  //month
	  tim.tm_mon = atoi(line.c_str());
	  getline(in, line, '/');
	  //day
	  tim.tm_mday = atoi(line.c_str());
	  //year
	  getline(in, line);
	  tim.tm_year = atoi(line.c_str());

	}
      
      //items being shipped in by warehouse
      else if(line.compare("Receive:")==0)
	{
	  // make a new food item looked up by the upc and add quantity
	  // and warehouse etc

	  //UPC
	  getline(in, line, ' ');
	  // add item quantity to this upc
	  string upc = line;
	  
	  //quantity
	  getline(in, line, ' ');
	  int quantity = atoi(line.c_str());

	  //warehouse
	  getline(in, line);
	  string warehouse = line;

	  //iterator for map
	  //map<string, food_item>::iterator it;
	 
	  //find upc in food_map
	  //it = food_map.find(upc);
	  
	  //it - should be a food_item
	  // make a new food_item with quantity, location and upc
	  // and shelf-life, and name from upc
	  //Add this food item to the list of food items
	  //food_item f = (it.name, it.upc, it.shelf-life);
	  //f.location = warehouse;
	  //f.quantity = quantity;

	}
      
      // items being shipped out of a warehouse
      else if(line.compare("Request:")==0) // add item quantity to this upc at this 
	                             //warehouse
	{
	  //UPC
	  getline(in, line, ' ');
	  string upc = line;
	  
	  //quantity
	  getline(in, line, ' ');
	  int quantity = atoi(line.c_str());
	  
	  //warehouse
	  getline(in, line);
	  string warehouse = line;

	  // iterator for set
	  //std::map<assignmet4::ware_house>::iterator it;
	  //look by warehouse, by upc and then minus quantity
	  //find warehouse
	  //it = wh_map.find(warehouse by its name);
	  //it - is the warehouse
	  //find food_item by upc
	  //subtract quantity from food_item.quantity
	  
	}

      else if(line.compare("Next")==0)
	{
	  // add one to whatever day it is
	  getline(in, line);
	  tim.tm_mday += 1; //adds one day
	  mktime(&tim); //refactor months and adjusts

	  // change all the food_items shelf-life - 1
	  //iterate through food_item and minus one from food_item.shelf-life
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
