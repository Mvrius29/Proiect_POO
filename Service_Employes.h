#pragma once
#include <iostream>
#include <string>
#include <ctime>
#include "GetTime.h"
using namespace std;

class Service_Employes {
  protected:
  string type;
  string id;
  string name;
  string second_name;
  string CNP;
  string employment_date;
  string city;
  void age_verification(const string &);
  void set_name(const string &); 
  void set_second_name(const string &);

  public:
  Service_Employes() = default;
  Service_Employes(const string &, const string &, const string &, const string &, const string &);
  virtual float get_salary() = 0;
  virtual void display_info() ; 
  virtual void modify_name(const string &);
  int get_time_with_company();
  virtual ~Service_Employes() ;
  const string& get_CNP() const;
  const string& get_name() const;
  const string& get_second_name() const;
  const string& get_type() const;
  
}; 
