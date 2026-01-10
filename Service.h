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
#include <queue>
using namespace std;

class Service {
    vector<unique_ptr<Service_Employes>> Employees_list;
    vector<unique_ptr<Electrocasnice>> Electrocasnice_list;
    vector<unique_ptr<Request>> Requests_list;
    
    map<pair<string,string>,int> Electrocasnice_irreparable;
    static int nr_rec;
    
public:
    Service();

    /// Employees Management
    void read_employees(const string &); 
    bool verify_employees_existence(const string &);
    void add_employee_sup(const string&, const string& , const string& , const string&, const string&, const string&);
    void add_employee_teh(const string&, const string& , const string& , const string&, const string&, const string&, const vector<pair<string, string>>& );
    void add_employee_rec(const string&, const string& , const string& , const string&, const string&, const string&, const vector<string>& );
    void delete_employee(const string &);
    void find_employee(const string &);
    void show_all_employees() const;
    void run_top3_performers() const;

    //Electrocasnice Management
    void read_electrocasnice(const string &);    
    bool verify_electrocasnic_existence(const string &, const string &) const;
    void add_electrocasnic_and_firm(const string &, const string &,const string &,const float &, const int &,const float &,const string &);
    void add_electrocasnic_and_firm(const string &, const string &,const string &,const float &, const int &,const bool &);
    void add_electrocasnic_and_firm(const string &, const string &,const string &,const float &, const int &,const float &);
    void delete_firm(const string &, const string &);
    void delete_model(const string &, const string &);
    Electrocasnice* find_type_from_firm(const string &, const string &);
    void show_all_electrocasnice() const;

    //Request Management
 
    void read_requests(const string &);
    void add_request_tv(const int &,const string &,const string &, const string &,const float &, const int &, const float &, const string &);
    void add_request_frigider(const int &,const string &,const string &, const string &,const float &,const int &, const bool &);
    void add_request_washer(const int &,const string &,const string &, const string &,const float &, const int &, const float &);
    void show_all_requests() const;
    bool search_electronic_in_requests(const string &, const string &, const string &,const int &);
    void delete_request(const string &, const string &, const string &,const int &);
    void clear_requests_lists();
    void share_requests_to_rec();
    void add_request_to_an_rec(const string &);
    void delete_request_from_an_rec(const string &);
    int get_request_list_dim() const;
    Request* get_last_request();
    const string& get_request_id(const string &,const string &, const string &, const int& );
    //Reports Management
    void irreparable_report() const;
     
    //Simulation Management
    bool verify_posibilyty_of_runing() const;
    Tehnician* get_correct_tehnician(const string& , const string &);
    bool teh_working() const;
    void simulate();
    ~Service() = default;
};