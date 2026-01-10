#include "Receptionist.h"

int Receptionist::index = 0;

Receptionist::Receptionist(const string &name1, const string &second_name1, const string &cnp, const string &employment_date1, const string &city1,
                           const vector<string> &requests1) : Service_Employes(name1, second_name1, cnp, employment_date1, city1), requests{requests1}
{
    index++;
    id = "R" + to_string(index);
    type = "R";
}

float Receptionist::get_salary()
{
    int salary = 4000;
    if (city != "Bucuresti")
        salary += 400;
    salary += (get_time_with_company() / 3) * 0.05 * 4000;
    return salary;
}

void Receptionist::add_request(const string &request)
{
    requests.push_back(request);
}

void Receptionist::display_info()
{
    cout << "Receptionist Information:\n";
    Service_Employes::display_info();
    for (vector<string>::const_iterator it = requests.begin(); it != requests.end(); ++it)
        cout << " Request: " << (*it) << "\n";
}

void Receptionist::clear_request()
{
    requests.clear();
}

int Receptionist::requests_list_size() const
{
    int dim = requests.size();
    return dim;
}

bool Receptionist::verify_request(const string &id)
{
    for (vector<string>::const_iterator it = requests.begin(); it != requests.end(); ++it)
    {
        if ((*it) == id)
            return true;
    }
    return false;
}

void Receptionist::delete_request(const string &id)
{
    for (vector<string>::const_iterator it = requests.begin(); it != requests.end(); ++it)
        if ((*it) == id)
        {
            requests.erase(it);
            cout << "Deleted request with id: " << id << "\n";
            return;
        }
}