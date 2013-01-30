// make constructors

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <regex>
#include "wareHouse.h"
#include "date.h"
#include "foodItem.h"

using namespace std;

namespace assignment4
{

ware_house::ware_house(std::set<food_item> food_set, const std::string name, 
		       std::set<date> dates)
{
  
}
ware_house::ware_house(const ware_house & rhs)
{

}
ware_house::~ware_house()
{

}


food_item::food_item(int quantity, const std::string name, const int upc, 
		     int shelf_life)
{

}
food_item::food_item(const food_item & rhs)
{

}
food_item::~food_item()
{

}


date::date(int quantity, const std::string name, const int upc, 
		     int shelf_life)
{

}
date::date(const date & rhs)
{

}
date::~date()
{

}
int get_month()
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
}

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
