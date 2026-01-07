#pragma once 
#include "Electrocasnice.h"
#include "GetTime.h"
#include <vector>
#include <memory>
using namespace std;

class Request{
    static int index_tv;
    static int index_fr;
    static int index_ms;
    int complexity;
    string id_req;
    string type;
    string firm;
    string model;
    float price;
    int year;
    float load_capacity = 0;
    bool has_freezer = 0;
    float diagonal_size = 0;
    string unit = "";
    string timestamp;
    int complexity_level;
    void set_timestamp();
    void set_complexity_level(const int &);
    public:
    Request() = default;
    Request(const int &,const string &,const string &, const string &,const float &, const int &, const float &, const string &); // tv
    Request(const int &,const string &,const string &, const string &,const float &,const int &, const bool &); //frigider  
    Request(const int &,const string &,const string &, const string &,const float &, const int &, const float &); //masina de spalat
    const string& get_id_req() const;
    const string& get_timestamp() const;
    const int& get_complexity_level() const;
    const int get_vechime() const;
    const float get_reparation_time() const;
    const float get_reparation_price() const;
    ~Request() = default;
};