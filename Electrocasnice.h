#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "GetTime.h"
using namespace std;

class Electrocasnice {
   protected:
   string firm;
   string type;
   string model;
   float price;
   int year;
   void set_firm(const string &);
   void set_type(const string &);
   void set_model_price_year(const string&, const float& , const int&);
    public:
    Electrocasnice() = default;
    Electrocasnice(const string &, const string &, const string&, const float& , const int&);
    virtual void display_info() const;
    const string& get_firm() const ;
    const string& get_type() const ;
    const string& get_model() const;
};