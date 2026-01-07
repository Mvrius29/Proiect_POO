#pragma once
#include "Electrocasnice.h"

class Frigider : public Electrocasnice {
       protected:
       bool has_freezer;
       void set_has_freezer(const bool &);
        public:
        Frigider() = default;
        Frigider(const string &, const string &,const vector<pair<pair<string,float>,int>> &,const bool &);
        void display_info() const override;
        const bool get_has_freezer() const;
};