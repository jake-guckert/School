// make constructors

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include "wareHouse.h"
#include "date.h"
#include "foodItem.h"

using namespace std;

namespace assignment4
{

ware_house::ware_house(const std::string name)
{
  this->food_set = new set<food_item>;
  this->name = name;
  this->dates = new set<date>; // don't know if need to be new
}
ware_house::ware_house(const ware_house & rhs)
{
  this->food_set = NULL;
  this->name = NULL;
  this->dates = NULL; // don't know if need to be new

  *this = rhs;

}
ware_house::~ware_house()
{
  //maybe need a clean() like in utah_set
}


food_item::food_item(int quantity, const std::string name, const string upc, 
		     int shelf_life)
{
  this->quantity = quantity;
  this->name = name;
  this->upc = upc;
  this->shelf_life = shelf_life;

}
food_item::food_item(const food_item & rhs)
{
  this->quantity = 0;
  this->name = NULL;
  this->upc = NULL;
  this->shelf_life = 0;

  *this = rhs;
  
}
food_item::~food_item()
{
  //maybe need a clean() like in utah_set
}


date::date(int month, int day, int year)
{

}
date::date(const date & rhs)
{

}
date::~date()
{

}
  /*int get_month()
{
  return this->month;
}
int get_day()
{
  return this->day;
}
int get_year()
{
  return this->year;
}
}*/

int main(int argc, char** argv)
{
  fstream in(argv[1]);

  printf("Report by Jake Guckert, Josh Bell!!!!!!!\n\n");

  //Read in and sort data
   while(true)
  {
      std::string word;
      string line;
      
       getline(in, line);
       istringstream iss(line);

       if((iss>>word).compare("FoodItem")==0)
	{
	  iss>>word>>word>>word;
	  cout << word << endl; 
	}
      if(word.compare("Warehouse")==0)
  {}
	if(word.compare("Start")==0)
  {}
	  if(word.compare("Receive")==0)
  {}
	    if(word.compare("Request")==0)
  {}
	      if(word.compare("Next")==0)
  {}
if(word.compare("End")==0)
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
