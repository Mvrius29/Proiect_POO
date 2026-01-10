#include "Tehnician.h"

int Tehnician::index = 0;

Tehnician::Tehnician(const string &name1, const string &second_name1, const string &cnp, const string &employment_date1, const string &city1,
                     const vector<pair<string, string>> &certifications1) : Service_Employes(name1, second_name1, cnp, employment_date1, city1), certifications{certifications1}
{
    index++;
    id = "T" + to_string(index);
    type = 'T';
}

float Tehnician::get_salary()
{
    int salary = 4000;
    if (city != "Bucuresti")
        salary += 400;
    salary += (get_time_with_company() / 3) * 0.05 * 4000;
    salary += repartions_bonus * 0.2;
    return salary;
}

void Tehnician::add_cerification(const string &type, const string &firm)
{
    for (vector<pair<string, string>>::const_iterator it = certifications.begin(); it != certifications.end(); ++it)
    {
        if (it->first == type && it->second == firm)
            throw std::invalid_argument("Certification already exists.");
    }
    certifications.push_back(make_pair(type, firm));
}

void Tehnician::display_info()
{
    cout << "Tehnician Information:\n";
    Service_Employes::display_info();
    cout << "Certifications:\n";
    for (vector<pair<string, string>>::const_iterator it = certifications.begin(); it != certifications.end(); ++it)
    {
        cout << "Firm : " << it->first << ", Type: " << it->second << '\n';
    }
}

int Tehnician::get_number_of_jobs() const
{
    return requestst_in_process.size();
}

int Tehnician::get_total_hours_worked() const
{
    return total_hours_worked;
}

bool Tehnician::verify_certification(const string &type, const string &firm)
{
    for (vector<pair<string, string>>::const_iterator it = certifications.begin(); it != certifications.end(); ++it)
    {
        if (it->first == type && it->second == firm)
            return true;
    }
    return false;
}

bool Tehnician::free_tehnician()
{
    return requestst_in_process.size() < 3;
}

void Tehnician::add_to_local_queue(Request *req)
{
    if (requestst_in_process.empty())
    {
        curent_task_time_left = req->get_reparation_time();
    }
    requestst_in_process.push_back(req);
}

void Tehnician::work()
{
    fstream file;
    file.open("./tests/Simulation.csv",ios::out | ios::app);
    if (!requestst_in_process.empty())
    {
        curent_task_time_left -= 1.0;

        if (curent_task_time_left <= 0)
        {
            file << "[Finished] " << name << " has finished " << requestst_in_process[0]->get_id_req() << "\n";
            repartions_bonus += requestst_in_process[0]->get_reparation_price();

            requestst_in_process.erase(requestst_in_process.begin());

            if (!requestst_in_process.empty())
            {
                curent_task_time_left = requestst_in_process[0]->get_reparation_time();
            }
        }
    }
    file.close();
}

void Tehnician::display_status() const
{
    fstream file;
    file.open("./tests/Simulation.csv",ios::out | ios::app);
    file << "Tehnician " << name << " (" << requestst_in_process.size() << "/3): ";
    if (requestst_in_process.empty())
        file << "No jobs ongoing";
    else
    {
        file << "Work on  " << requestst_in_process[0]->get_id_req()
             << " (Time left: " << curent_task_time_left << "s)";
        if (requestst_in_process.size() > 1)
        {
            file << " | In queue: ";
            for (size_t i = 1; i < requestst_in_process.size(); ++i)
                file << requestst_in_process[i]->get_id_req() << " ";
        }
    }
    file << endl;
}