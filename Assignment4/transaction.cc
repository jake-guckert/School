// make constructors

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
#include <set>
#include <map>
#include <ctime>
#include <time.h>
#include "ware_house.h"
#include "foodItem.h"
#include "dates.h"

using namespace std;

/*******************************************************************************/
tm tim; // used for dates

//key is the warehouse name
map<string, assignment4::ware_house> wh_map; // set of warehouses

// create a dictionary of available  food items. not tied to any warehouse
// key is the upc. zero quantity.
// Just a list of available food items to choose from.
map<string, assignment4::food_item> food_map;

// A set of dates where the key is the date in as a string.
map<string, assignment4::date> date_map;

/********************************************************************************/

int main(int argc, char** argv)
{
  fstream in(argv[1]);

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
	  	  
	  // food item to dictionary by upc key
	  food_map[upc] = fi;
	}

      //Make a new warehouse with the name provided
      // Add warehouse to map of warehouses
      else if(line.compare("Warehouse")==0)
	{
	  getline(in, line, '-');
	  getline(in, line, ' ');
	  getline(in, line);
	  
	  // create new warehouse
	  assignment4::ware_house wh(line);
	  
	  //Add warehouse to set of warehouses
	  //wh_map[line] = wh;
	  
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

	  int activity = 0;

	  string month;
	  ostringstream monthconvert;
	  monthconvert << tim.tm_mon;
	  month = monthconvert.str();

	  string day;
	  ostringstream dayconvert;
	  dayconvert << tim.tm_mday;
	  day = dayconvert.str();

	  string year;
	  ostringstream yearconvert;
	  yearconvert << tim.tm_year;
	  year = yearconvert.str();

	  string d = year+month+day;
	  assignment4::date day1(d);
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
	  map<string, assignment4::food_item>::iterator it;
	 
	  //find upc in food_map
	  it = food_map.find(upc);
	  
	  //Check if item already exists in the warehouse


	  //it - should be a food_item??????????
	  // make a new food_item with quantity, location and upc
	  // and shelf-life, and name from upc
	  assignment4::food_item f(it->second.name, it->second.upc, it->second.shelf_life);
	  f.location = warehouse;
	  f.quantity = quantity;

	  //Add this food item to the warehouse
	  //????


	  //add one to activity of warehouse

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
	  std::map<string, assignment4::ware_house>::iterator it;

	  //look by warehouse, by upc and then minus quantity
	  //find warehouse
	  //it = wh_map.find(warehouse by its name);
	  //it - is the warehouse
	  //find food_item by upc
	  //subtract quantity from food_item.quantity += -1
	  
	  // HEAD

	  //add one to activity of warehouse
	  //warehouse.date.activity += 1 //add one to activity of warehouse
	  // Timing objects?!??!?!
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
	  cout << "\n" << endl;
	  cout << "Report by Jake Guckert & Josh Bell\n" << endl;
	  cout << "Unstocked Products:\n" << endl;
	  // cout << Unstocked(map of warehouses) << "\n" <<  endl; returns a list of UPCs and name
	  cout << "Fully-Stocked Products:\n" << endl;
	  // cout << FullyStocked(map of warehouses) << "\n" << endl; returns a list of UPCs and name
	  cout << "Busiest Days:\n" << endl;
	  // cout BusiestDays(map of warehouses) << "\n" << endl;
	  break;
	}

      if(in.fail())
	{
	  cout << "Failed" << endl;
	  break;
	}
    }

}
