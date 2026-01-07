#include "Tehnician.h"

int Tehnician::index = 0;

Tehnician::Tehnician(const string &name1, const string &second_name1, const string &cnp, const string &employment_date1, const string &city1, 
    const vector<pair<string,string>> &certifications1): Service_Employes(name1, second_name1, cnp, employment_date1, city1), certifications{certifications1} {
       index++;
       id = "T" + to_string(index);
}

float Tehnician::get_salary()  {
   int salary = 4000;
   if(city != "Bucuresti") 
      salary += 400;
   salary += (get_time_with_company() / 3) * 0.05 * 4000;
   salary += repartions_bonus * 0.2;
    return salary;
}

void Tehnician::add_cerification(const string &type, const string &firm){
    for(vector<pair<string,string>>::const_iterator it = certifications.begin(); it != certifications.end(); ++it) {
        if(it->first == type && it->second == firm)
            throw std::invalid_argument("Certification already exists.");
    }
    certifications.push_back(make_pair(type, firm));
}

void Tehnician::display_info()  {
    cout<< "Tehnician Information:\n";
    Service_Employes::display_info();
    cout << "Certifications:\n";
    for(vector<pair<string,string>>::const_iterator it = certifications.begin(); it != certifications.end(); ++it) {
        cout << "  Type: " << it->first << ", Firm: " << it->second << '\n';
    }
}
