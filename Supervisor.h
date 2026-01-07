#pragma once
#include "Service_Employes.h"
#include "GetTime.h"
#include <vector>
#include <memory>
#include <algorithm>


class Supervisor : public Service_Employes{
    static int index;

    public:
    Supervisor();
    Supervisor(const string &, const string &, const string &, const string &, const string &);
    float get_salary() override;
    void display_info() override;
    void top3_performers(const vector<unique_ptr<Service_Employes>>& );
    //void raportVenituri(const vector<CerereReparatie>& toateCererile);
};