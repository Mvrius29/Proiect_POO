#include "Washer.h"

void Washer::set_load_capacity(const float &load_capacity1) {
    if(load_capacity1 <= 0)
        throw std::invalid_argument("Load capacity must be positive.");
    load_capacity = load_capacity1;
}

Washer::Washer(const string &firm1, const string &type1, const string& model1, const float&price1 , const int&year1, const float &load_capacity1)
    : Electrocasnice{firm1, type1, model1,price1,year1} {
    set_load_capacity(load_capacity1);
}

void Washer::display_info() const {
    Electrocasnice::display_info();
    cout << "Load Capacity: " << load_capacity << " kg\n";
}

const float Washer::get_load_capacity() const {
    return load_capacity;
}