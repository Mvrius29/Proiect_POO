#pragma once 
#include "Service_Employes.h"
#include "GetTime.h"
#include <vector>

class Receptionist : public Service_Employes {
    static int index;
    vector<string> requests;

    public:
    Receptionist();
    Receptionist(const string &, const string &, const string &, const string &, const string &,const vector<string> &);
    float get_salary() override;
    void display_info() override;
    void add_request(const string &);
};