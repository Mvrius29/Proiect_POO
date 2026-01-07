#pragma once 
#include "Service_Employes.h"
#include <vector>

class Tehnician : public Service_Employes {
     static int index;
     vector<pair<string,string>> certifications; 
     float repartions_bonus ;
     int curent_jobs;
     int total_hours_worked ;
     void add_certification(const string &, const string &);

    public:
     Tehnician();
     Tehnician(const string &, const string &, const string &, const string &, const string &, const vector<pair<string,string>> &);
     float get_salary()  override;
     void display_info()  override;
     void add_cerification(const string &, const string &);
     //de completet dupa ce fac class de electrocasnice si de cereri
};