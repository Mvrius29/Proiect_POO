#include "Electrocasnice.h"

void Electrocasnice::set_firm(const string &firm1) {
    if(firm1.size() < 2)
      throw std::invalid_argument("Firm name must be at least 2 characters long.");
    firm = firm1;
}

void Electrocasnice::set_type(const string &type1) {
    if(type1 != "TV" && type1 != "FR" && type1 != "MS")
      throw std::invalid_argument("Type name must be one of: TV, FR, MS.");
    type = type1;
}

void Electrocasnice::set_model_price_year(const string &model1, const float &price1 , const int &year1) {
        if(model1.size() == 0)
           throw std::invalid_argument("Model cannot be null.");
        if(price1 < 0)
            throw std::invalid_argument("Price cannot be negative.");
        if(year1 < 1900 || year1 > GetTime::getcurentYear())
            throw std::invalid_argument("Year is not valid.");
     year = year1;
     price = price1;
     model = model1;
}



Electrocasnice::Electrocasnice(const string &firm1, const string &type1, const string &model1, const float &price1 , const int &year1){
    set_firm(firm1);
    set_type(type1);
    set_model_price_year(model1,price1,year1);
}

void Electrocasnice::display_info() const {
    cout << "Firm: " << firm << '\n';
    cout << "Type: " << type << '\n';
    cout << "Model: " << model << '\n';
    cout << "Price:" << price << '\n';
    cout << "Year" << year << '\n'; 
    
}

const string& Electrocasnice::get_firm() const {
    return firm;
}

const string& Electrocasnice::get_type() const {
    return type;
}

const string& Electrocasnice::get_model() const{
    return model;
}