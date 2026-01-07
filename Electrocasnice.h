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
   vector<pair<pair<string,float>,int>> model_price_year;
   void set_firm(const string &);
   void set_type(const string &);
   void set_model_price_year(const vector<pair<pair<string,float>,int>> &);
   void set_catalogue_price(const float &);
    public:
    Electrocasnice() = default;
    Electrocasnice(const string &, const string &, const vector<pair<pair<string,float>,int>> &);
    virtual void display_info() const;
    void add_model(const string &, const float &, const int &);
    void delete_model(const string &);
    const string& get_firm() const ;
    const string& get_type() const ;
};