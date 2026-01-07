#include "Receptionist.h"

int Receptionist::index = 0;

Receptionist::Receptionist(const string &name1, const string &second_name1, const string &cnp, const string &employment_date1, const string &city1,
    const vector<string> &requests1): Service_Employes(name1, second_name1, cnp, employment_date1, city1), requests{requests1} {
       index++;
       id = "R" + to_string(index);
}

float Receptionist::get_salary()  {
   int salary = 4000;
   if(city != "Bucuresti") 
      salary += 400;
   salary += (get_time_with_company() / 3) * 0.05 * 4000;
    return salary;
}

void Receptionist::add_request(const string &request){
    requests.push_back(request);
}

void Receptionist::display_info()  {
    cout<< "Receptionist Information:\n";
    Service_Employes::display_info();
}