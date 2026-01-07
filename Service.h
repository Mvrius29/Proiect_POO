#pragma once
//Employees
#include "Service_Employes.h"
#include "Supervisor.h"
#include "Tehnician.h"
#include "Receptionist.h"

//Electrocasnice
#include "Electrocasnice.h"
#include "Washer.h"
#include "Frigider.h"
#include "TV.h"

//Requests
#include "Request.h"

#include <vector>
#include <memory>
#include <fstream>
#include <sstream>
#include <string.h>
#include <map>

class Service {
    vector<unique_ptr<Service_Employes>> Employees_list;
    vector<unique_ptr<Electrocasnice>> Electrocasnice_list;
    vector<unique_ptr<Request>> Requests_list;
    map<pair<string,string>,int> Electrocasnice_irreparable;
    
public:
    /// Employees Management
    void read_employees(const string &); 
    void add_employee_sup(const string&, const string& , const string& , const string&, const string&, const string&);
    void add_employee_teh(const string&, const string& , const string& , const string&, const string&, const string&, const vector<pair<string, string>>& );
    void add_employee_rec(const string&, const string& , const string& , const string&, const string&, const string&, const vector<string>& );
    void delete_employee(const string &);
    void find_employee(const string &);
    void show_all_employees() const;
    void run_top3_performers() const;


    //Electrocasnice Management
    void read_electrocasnice(const string &);  
    void add_electrocasnic_and_firm(const string &, const string &,const vector<pair<pair<string,float>,int>> &,const float &,const string &);
    void add_electrocasnic_and_firm(const string &, const string &,const vector<pair<pair<string,float>,int>> &,const bool &);
    void add_electrocasnic_and_firm(const string &, const string &,const vector<pair<pair<string,float>,int>> &,const float &);
    void delete_firm(const string &firm, const string &type);
    void show_all_electrocasnice() const;

    //Request Management
    bool verify_electrocasnic_existence(const string &, const string &) const;
    void read_requests(const string &);
    void add_request_tv(const int &,const string &,const string &, const string &,const float &, const int &, const float &, const string &);
    void add_request_frigider(const int &,const string &,const string &, const string &,const float &,const int &, const bool &);
    void add_request_washer(const int &,const string &,const string &, const string &,const float &, const int &, const float &);
    void show_all_requests() const;
    
    //Reports Management
    void irreparable_report() const;
     
    bool verify_posibilyty_of_runing() const;

    ~Service() = default;
};