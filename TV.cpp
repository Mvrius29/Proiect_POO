#include "TV.h"

void TV::set_diagonal_size(const float &diagonal_size1) {
    if(diagonal_size1 <= 0)
        throw std::invalid_argument("Diagonal size must be positive.");
    diagonal_size = diagonal_size1;
}

void TV::set_unit(const string &unit1) {
    if(unit1 != "cm" && unit1 != "inch")
        throw std::invalid_argument("Unit must be either 'cm' or 'inch'.");
    unit = unit1;
}

TV::TV(const string &firm1, const string &type1, const vector<pair<pair<string,float>,int>> &model_price_year1, const float &diagonal_size1, const string &unit1)
    : Electrocasnice{firm1, type1, model_price_year1} {
    set_unit(unit1);
    set_diagonal_size(diagonal_size1);
}

void TV::display_info() const {
    Electrocasnice::display_info();
    cout << "Diagonal Size: " << diagonal_size << " " << unit << "\n";
}

const float TV::get_diagonal_size() const {
    return diagonal_size;
}