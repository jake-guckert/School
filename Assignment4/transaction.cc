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
#include <vector>
#include "ware_house.h"
#include "foodItem.h"
#include "dates.h"

using namespace std;

/*******************************************************************************/
tm tim; // used for dates

//key is the warehouse name
map<string, assignment4::ware_house> wh_map; // map of warehouses by name

// create a dictionary of available  food items. not tied to any warehouse
// key is the upc. zero quantity.
// Just a list of available food items to choose from.
map<string, assignment4::food_item> food_map;

// A set of dates where the key is the date in as a string.
string current_day = "";

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

	  assignment4::food_item fi(name, upc);
	  fi.shelf_life = shelf_life;
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
	  
	  string name = line;
	  // create new warehouse
	  assignment4::ware_house wh(name);
	  
	  //Add warehouse to set of warehouses
	  wh_map[name] = wh;
	  
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

	  current_day = month+"/"+day+"/"+year;
	}

      //items being shipped in by warehouse
      if(line.compare("Receive:")==0)
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
	  map<string, assignment4::ware_house>::iterator it_wh;
	  map<string, assignment4::food_item>::iterator fs;
	  map<string, assignment4::food_item>::iterator fm;
	   string::iterator fm2;
	  
	  
	 
	  
	  
	  //Check if item already exists in the warehouse
	  it_wh = wh_map.find(warehouse); // the key and value of the warehouse from map
       
	  fs = it_wh->second.food_set.find(upc);
	  fm = food_map.find(upc);

	  //if item is not  already in the warehouse
	  if(fs != it_wh->second.food_set.end())
	    {
	      //traverse through vector of food_items
	      
		  //find lowest shelf life and subtract
		  // change quantity
		  fs->second.quantity += quantity;
		  fm->second.quantity +=quantity;
		  
	    }
	  // the item is not in the warehouse
	  else
	    {
	      //find upc in food_map
	      it = food_map.find(upc);
	      
	      //it - should be a food_item??????????
	      // make a new food_item with quantity, location and upc
	      // and shelf-life, and name from upc
	      assignment4::food_item f(it->second.name, it->second.upc);
	      f.location = warehouse;
	      f.quantity = quantity;
	      f.shelf_life = it->second.shelf_life;
	    
	      //Add this food item to the food_set within the warehouse
	      it_wh->second.food_set[upc] = f;
	      fm->second.quantity += quantity;

	    }
	 
	  it_wh->second.current_activity += quantity;
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

	  //iterator for map
	  map<string, assignment4::food_item>::iterator it;
	  map<string, assignment4::ware_house>::iterator it_wh;
	  map<string, assignment4::food_item>::iterator fs;
	  map<string, int>::iterator dm;
	 
	  	  
	  //Check if item already exists in the warehouse
	  it_wh = wh_map.find(warehouse); // the key and value of the warehouse from map
	  fs = it_wh->second.food_set.find(upc);
	  //if item already exists in warehouse
	  if(fs == it_wh->second.food_set.end())
	    {
	      // change quantity
	      fs->second.quantity -= quantity;
	      if(fs->second.quantity < 0)
		fs->second.quantity = 0;
		
	    }
	 
	  it_wh->second.current_activity += quantity;
	}

      else if(line.compare("Next")==0)
	{
	  // compare current_activity to activity date and swap if need be
	  // change all the food_items shelf-life - 1
	  // iterate through food_item and minus one from food_item.shelf-life
	  map<string, assignment4::ware_house>::iterator it_wh;
	  map<string, assignment4::food_item>::iterator it_f;

	  for(it_wh = wh_map.begin(); it_wh != wh_map.end(); it_wh++) // goes through each warehouse
	    {
	      if(it_wh->second.current_activity > it_wh->second.d.activity)
		{
		  it_wh->second.d.activity = it_wh->second.current_activity;
		  it_wh->second.current_activity = 0;
		  it_wh->second.d.d = current_day;
		}
	      for(it_f = it_wh->second.food_set.begin(); it_f != it_wh->second.food_set.end(); it_f++) // goes through food_set within a warehouse
		{
		  it_f->second.shelf_life --; // minus a day off of the shelf-life
		  if(it_f->second.shelf_life == 0)
		    {
		      it_f->second.quantity = 0;
		    }
		}

	    }

	   // add one to whatever day it is
	  getline(in, line);
	  tim.tm_mday += 1; //adds one day
	  mktime(&tim); //refactor months and adjusts
	  
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

	  current_day = month+"/"+day+"/"+year;
	}

      if(line.compare("End")==0)// deal with extra spaces after END!!!!
	{
	  cout << "Report by Jake Guckert & Josh Bell\n" << endl;
	  cout << "Unstocked Products:\n" << endl;
	  
	  map<string, assignment4::ware_house>::iterator it_wh;
	  map<string, assignment4::food_item>::iterator it_f;

	      for(it_f = food_map.begin(); it_f != food_map.end(); it_f++) // goes through food_set within a warehouse
		{		  
		  
		  if(it_f->second.quantity == 0)
		    {
		      cout<< it_f->second.upc << " " << it_f->second.name << endl;
		    }
		}
	    

	  cout << "Fully-Stocked Products:\n" << endl;
	  
	  cout << "Busiest Days:\n" << endl;
	  
	  for(it_wh = wh_map.begin(); it_wh != wh_map.end(); it_wh++) // goes through each warehouse
	    {
	      cout << it_wh->first << endl;
	      cout << it_wh->second.d.d << endl;
	      cout << it_wh->second.d.activity << endl;
	    }
	  return 0;
	}

      if(in.fail())
	{
	  cout << "Failed" << endl;
	  return 0;
	}
    }

}
