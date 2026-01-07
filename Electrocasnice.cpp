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

void Electrocasnice::set_model_price_year(const vector<pair<pair<string,float>,int>> &model_price_year1) {
    for(vector<pair<pair<string,float>,int>>::const_iterator it = model_price_year1.begin(); it != model_price_year1.end(); ++it) {
        if(it->first.second < 0)
            throw std::invalid_argument("Price cannot be negative.");
        if(it->second < 1900 || it->second > GetTime::getcurentYear())
            throw std::invalid_argument("Year is not valid.");
    }
    model_price_year = model_price_year1;
}



Electrocasnice::Electrocasnice(const string &firm1, const string &type1, const vector<pair<pair<string,float>,int>> &model_price_year1){
    set_firm(firm1);
    set_type(type1);
    set_model_price_year(model_price_year1);
}

void Electrocasnice::display_info() const {
    cout << "Firm: " << firm << '\n';
    cout << "Type: " << type << '\n';
    cout << "Models: " << '\n';
    for(vector<pair<pair<string,float>,int>>::const_iterator it = model_price_year.begin(); it != model_price_year.end(); ++it) {
        cout << "  Model: " << it->first.first << ", Price: " << it->first.second << ", Year: " << it->second << '\n';
    }
}

void Electrocasnice::add_model(const string &model, const float &price, const int &year){
    if(price < 0)
        throw std::invalid_argument("Price cannot be negative.");
    if(year < 1900 || year > GetTime::getcurentYear())
        throw std::invalid_argument("Year is not valid.");
    for(vector<pair<pair<string,float>,int>>::const_iterator it = model_price_year.begin(); it != model_price_year.end(); ++it) {
        if(it->first.first == model)
            throw std::invalid_argument("Model already exists.");
    }
    model_price_year.push_back(make_pair(make_pair(model, price), year));
}

void Electrocasnice::delete_model(const string &model){
    for(vector<pair<pair<string,float>,int>>::const_iterator it = model_price_year.begin(); it != model_price_year.end(); ++it) {
        if(it->first.first == model) {
            model_price_year.erase(it);
            return;
        }
    }
    throw std::invalid_argument("Model not found.");
}

const string& Electrocasnice::get_firm() const {
    return firm;
}

const string& Electrocasnice::get_type() const {
    return type;
}