#include "Request.h"

int Request::index_tv = 0;
int Request::index_fr = 0;
int Request::index_ms = 0;

void Request::set_timestamp() {
    timestamp = GetTime::getfulltime();
}

void Request::set_complexity_level(const int &complexity_level1) {
    if (complexity_level1 < 0 || complexity_level1 > 5)
        throw std::invalid_argument("Complexity level must be between 0 and 5.");
    complexity_level = complexity_level1;
}

Request::Request(const int &complexity1, const string &type1, const string &firm1, const string &model1, const float &price1, const int &year1, const float &diagonal_size1, const string &unit1)
    : type{type1}, firm{firm1}, model{model1}, price{price1}, year{year1}, diagonal_size{diagonal_size1}, unit{unit1} {
    index_tv++;
    id_req = "C_TV_" + to_string(index_tv);
    set_timestamp();
    set_complexity_level(complexity1);
}

Request::Request(const int &complexity1, const string &type1, const string &firm1, const string &model1, const float &price1, const int &year1, const bool &has_freezer1)
    : type{type1}, firm{firm1}, model{model1}, price{price1}, year{year1}, has_freezer{has_freezer1} {
    index_fr++;
    id_req = "C_FR_" + to_string(index_fr);
    set_timestamp();
    set_complexity_level(complexity1);
}

Request::Request(const int &complexity1, const string &type1, const string &firm1, const string &model1, const float &price1, const int &year1, const float &load_capacity1)
    : type{type1}, firm{firm1}, model{model1}, price{price1}, year{year1}, load_capacity{load_capacity1} {
    index_ms++;
    id_req = "C_MS_" + to_string(index_ms);
    set_timestamp();
    set_complexity_level(complexity1);
}

const string &Request::get_id_req() const {
    return id_req;
}

const string &Request::get_timestamp() const {
    return timestamp;
}

const int &Request::get_complexity_level() const {
    return complexity_level;
}

const int Request::get_vechime() const {
    int curentYear = GetTime::getcurentYear();
    return curentYear - year;
}

const float Request::get_reparation_time() const {
    float reparation_time = 0;
    reparation_time = complexity_level * get_vechime() ;
    return reparation_time;
}


const float Request::get_reparation_price() const {
    float reparation_price = 0;
    reparation_price = price * get_reparation_time();
    return reparation_price;
}

const string& Request::get_firm() const {
    return firm;
}

const string& Request::get_type() const {
    return type;
}

const string& Request::get_model() const{
    return model;
}

const int& Request::get_year() const{
    return year;
}