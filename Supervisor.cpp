#include "Supervisor.h"

int Supervisor::index = 0;

Supervisor::Supervisor() : Service_Employes() {}

Supervisor::Supervisor(const string &name1, const string &second_name1, const string &cnp, const string &employment_date1, const string &city1)
    : Service_Employes(name1, second_name1, cnp, employment_date1, city1) {
       index++;
       id = "S" + to_string(index);
       type="S";
}   

float Supervisor::get_salary()  {
   int salary = 4000;
   if(city != "Bucuresti") 
      salary += 400;
   salary += (get_time_with_company() / 3) * 0.05 * 4000;
   salary += 4000 * 0.2;
   return salary;
}

void Supervisor::display_info()  {
    cout<< "Supervisor Information:\n";
    Service_Employes::display_info();
}

void Supervisor::top3_performers(const vector<unique_ptr<Service_Employes>>& employees){
    if(employees.size() < 3)
      throw std::invalid_argument("Not enough employees to determine top 3 performers.");

    vector<Service_Employes*> emp_ptrs ;
    for(vector<unique_ptr<Service_Employes>>::const_iterator it = employees.begin(); it != employees.end(); ++it) {
        emp_ptrs.push_back(it->get());
    }

    sort(emp_ptrs.begin(), emp_ptrs.end(), [](Service_Employes* a, Service_Employes* b) {
        return a->get_salary() > b->get_salary();
    }); 
    
    sort(emp_ptrs.begin(), emp_ptrs.begin() + 3, [](Service_Employes* a, Service_Employes* b) {
        if(a -> get_name() != b -> get_name())
            return a -> get_name() < b -> get_name();
        else
            return a -> get_second_name() < b -> get_second_name();
    }); 

    cout << "Top 3 Performers:\n";
    for(int i = 0; i < 3; ++i) {
        cout << i + 1 << ". " << emp_ptrs[i]->get_CNP() << " - Time with Company: " << emp_ptrs[i]->get_time_with_company() << " years\n";
    }
}