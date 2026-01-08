#include "TV.h"

void TV::set_diagonal_size(const float &diagonal_size1) {
    if(diagonal_size1 <= 0)
        throw std::invalid_argument("Diagonal size must be positive.");
    diagonal_size = diagonal_size1;
}

void TV::set_unit(const string &unit1) {
    if((unit1 != "cm" && unit1 != "inch") && (unit1 != "CM" && unit1 != "INCH"))
        throw std::invalid_argument("Unit must be either 'cm/CM' or 'inch/INCH'.");
    unit = unit1;
}

TV::TV(const string &firm1, const string &type1, const string& model1, const float&price1 , const int&year1, const float &diagonal_size1, const string &unit1)
    : Electrocasnice{firm1, type1, model1,price1,year1} {
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