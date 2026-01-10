#pragma once 
#include "Service_Employes.h"
#include <vector>
#include "Request.h"
#include <fstream>
using namespace std;

class Tehnician : public Service_Employes {
     static int index;
     vector<pair<string,string>> certifications; 
     vector<Request*> requestst_in_process;
     int curent_task_time_left;
     float repartions_bonus ;
     int total_hours_worked ;
     void add_certification(const string &, const string &);

    public:
     Tehnician();
     Tehnician(const string &, const string &, const string &, const string &, const string &, const vector<pair<string,string>> &);
     float get_salary()  override;
     void display_info()  override;
     void add_cerification(const string &, const string &);
     int get_number_of_jobs() const;
     int get_total_hours_worked() const;
     bool verify_certification(const string &, const string &);
     bool free_tehnician();
     void add_to_local_queue(Request *);
     void work();
     void display_status() const;

};