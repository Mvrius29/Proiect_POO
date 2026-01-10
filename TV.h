#pragma once 
#include "Electrocasnice.h"

class TV : public Electrocasnice {
   protected:
   float diagonal_size; 
   string unit;
   void set_diagonal_size(const float &);
   void set_unit(const string &);
    public:
    TV() = default;
    TV(const string &, const string &,const string&, const float& , const int&,const float &,const string &);
    void display_info() const override;
    const float get_diagonal_size() const;
};