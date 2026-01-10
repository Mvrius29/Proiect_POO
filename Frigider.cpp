#include "Frigider.h"

void Frigider::set_has_freezer(const bool &has_freezer1) {
    if((has_freezer1 != true && has_freezer1 != false) )
        throw std::invalid_argument("Has freezer must be true or false.");
    has_freezer = has_freezer1;
}
Frigider::Frigider(const string &firm1, const string &type1, const string& model1, const float&price1 , const int&year1, const bool &has_freezer1)
    : Electrocasnice{firm1, type1, model1,price1,year1}  {
    set_has_freezer(has_freezer1);
    }

void Frigider::display_info() const {
    Electrocasnice::display_info();
    cout << "Has Freezer: " << (has_freezer ? "Yes" : "No") << '\n';
}

const bool Frigider::get_has_freezer() const {
    return has_freezer;
}