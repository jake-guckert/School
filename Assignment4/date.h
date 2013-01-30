
#ifndef DATE_H
#define DATE_H

namespace assignment4
{

  class date
  {
  public:
    date(int month, int day, int year);
    date(const date & other);
    ~date();
    
    int get_month();
    int get_day();
    int get_year();

    

  private:
    int month;
    int day;
    int year; 
  };
}

#endif
