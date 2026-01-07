#pragma once
#include "Electrocasnice.h"

class Washer : public Electrocasnice {
    protected:
    float load_capacity; // in kg
    void set_load_capacity(const float &);
    public:
    Washer() = default;
    Washer(const string &, const string &,const vector<pair<pair<string,float>,int>> &,const float &);
    void display_info() const override;
    const float get_load_capacity() const;
};