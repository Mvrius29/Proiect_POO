#include "Service.h"

int Service::nr_rec = 0;

Service::Service()
{
    fstream file;
    file.open("./tests/Employee_raport.csv", ios::out);
    file << "Employees reading:\n ";
    file.close();

    file.open("./tests/Electronics_raport.csv", ios::out);
    file << "Electronics reading:\n ";
    file.close();

    file.open("./tests/Requests_raport.csv", ios::out);
    file << "Requests reading:\n ";
    file.close();
    read_employees("./tests/employees.txt");
    cout << "\n";
    read_electrocasnice("./tests/electrocasnice.txt");
    cout << "\n";
    read_requests("./tests/requests.txt");
    cout << "\n";
    try
    {
        share_requests_to_rec();
    }
    catch (const std::invalid_argument &e)
    {
        cout << e.what() << "\n";
    }
}

void get_unit_and_size(const string &diagonal_size_str, float &diagonal_size, string &unit)
{
    size_t pos = diagonal_size_str.find(' ');
    unit = diagonal_size_str.substr(pos + 1);
    diagonal_size = stof(diagonal_size_str.substr(0, pos));
}

void Service::read_employees(const string &filename)
{
    fstream file;
    int line_nr = 0;
    try
    {
        file.exceptions(fstream::badbit);
        file.open(filename, ios::in);
        string line;

        while (std::getline(file, line))
        {
            line_nr++;
            try
            {
                stringstream new_string(line);
                string role, name, second_name, cnp, employment_date, city;
                if (!std::getline(new_string, role, ',') || !std::getline(new_string, name, ',') || !std::getline(new_string, second_name, ',') || !std::getline(new_string, cnp, ',') || !std::getline(new_string, employment_date, ',') || !std::getline(new_string, city, ','))
                {
                    throw std::invalid_argument("Invalid certification format");
                }
                if (role == "T")
                {
                    string certifictions_str, type, firm;
                    vector<pair<string, string>> certifications;
                    while (new_string.good())
                    {
                        if (!std::getline(new_string, type, ',') || !std::getline(new_string, firm, ','))
                        {
                            throw std::invalid_argument("Invalid certification format");
                        }
                        certifications.emplace_back(type, firm);
                    }
                    add_employee_teh(role, name, second_name, cnp, employment_date, city, certifications);
                }
                else if (role == "R")
                {
                    string requests_str, request;
                    vector<string> requests;
                    add_employee_rec(role, name, second_name, cnp, employment_date, city, requests);
                }
                else if (role == "S")
                {
                    add_employee_sup(role, name, second_name, cnp, employment_date, city);
                }
            }
            catch (const std::invalid_argument &e)
            {
                cerr << "Error on reading on line:  " << line_nr << ": " << e.what() << endl;
            }
        }
    }
    catch (const fstream::failure &e)
    {
        cerr << "Error reading file on line " << line_nr << ": " << e.what() << endl;
    }
}

bool Service::verify_employees_existence(const string &cnp)
{
    for (vector<unique_ptr<Service_Employes>>::iterator it = Employees_list.begin(); it != Employees_list.end(); ++it)
        if ((*it)->get_CNP() == cnp)
        {
            return true;
        }
    return false;
}

void Service::add_employee_sup(const string &role, const string &name, const string &second_name, const string &cnp, const string &employment_date, const string &city)
{
    if (!verify_employees_existence(cnp))
    {
        Employees_list.push_back(std::make_unique<Supervisor>(name, second_name, cnp, employment_date, city));
        fstream file;
        file.open("./tests/Employee_raport.csv", ios::out | ios::app);
        file << "Added supervisor with CNP: " << cnp << endl;
        file.close();
    }
    else
        throw std::invalid_argument("You cannot add an employee who is already in service ");
}

void Service::add_employee_teh(const string &role, const string &name, const string &second_name, const string &cnp, const string &employment_date, const string &city, const vector<pair<string, string>> &certifications)
{
    if (!verify_employees_existence(cnp))
    {
        Employees_list.push_back(std::make_unique<Tehnician>(name, second_name, cnp, employment_date, city, certifications));
        fstream file;
        file.open("./tests/Employee_raport.csv", ios::out | ios::app);
        file << "Added technician with CNP: " << cnp << endl;
        file.close();
    }
    else
        throw std::invalid_argument("You cannot add an employee who is already in service");
}

void Service::add_employee_rec(const string &role, const string &name, const string &second_name, const string &cnp, const string &employment_date, const string &city, const vector<string> &requests)
{
    if (!verify_employees_existence(cnp))
    {
        Employees_list.push_back(std::make_unique<Receptionist>(name, second_name, cnp, employment_date, city, requests));
        fstream file;
        file.open("./tests/Employee_raport.csv", ios::out | ios::app);
        file << "Added receptionist with CNP: " << cnp << endl;
        file.close();
        nr_rec++;
    }
    else
        throw std::invalid_argument("You cannot add an employee who is already in service");
}

void Service::delete_employee(const string &cnp)
{
    for (vector<unique_ptr<Service_Employes>>::iterator it = Employees_list.begin(); it != Employees_list.end(); ++it)
    {
        if ((*it)->get_CNP() == cnp)
        {
            if ((*it)->get_type() == "R")
            {
                nr_rec--;
                Employees_list.erase(it);
                share_requests_to_rec();
            }
            else
                Employees_list.erase(it);

            return;
        }
    }
    throw std::invalid_argument("Employee with the given CNP not found.");
}

void Service::show_all_employees() const
{
    for (vector<unique_ptr<Service_Employes>>::const_iterator it = Employees_list.begin(); it != Employees_list.end(); ++it)
    {
        (*it)->display_info();
        cout << '\n';
    }
}

void Service::run_top3_performers() const
{
    for (vector<unique_ptr<Service_Employes>>::const_iterator it = Employees_list.begin(); it != Employees_list.end(); ++it)
    {
        Supervisor *supervisor_ptr = dynamic_cast<Supervisor *>(it->get());
        if (supervisor_ptr)
        {
            supervisor_ptr->top3_performers(Employees_list);
            return;
        }
    }
    throw std::invalid_argument("No supervisor found in the employee list.");
}

void Service::find_employee(const string &cnp)
{
    for (vector<unique_ptr<Service_Employes>>::const_iterator it = Employees_list.begin(); it != Employees_list.end(); ++it)
    {
        if ((*it)->get_CNP() == cnp)
        {
            (*it)->display_info();
            return;
        }
    }
    throw std::invalid_argument("Employee with the given CNP not found.");
}

// Electrocasnice Management
void Service::read_electrocasnice(const string &filename)
{
    fstream file;
    int line_nr = 0;
    try
    {
        file.exceptions(fstream::badbit);
        file.open(filename, ios::in);
        string line;

        while (std::getline(file, line))
        {
            line_nr++;
            try
            {
                stringstream new_string(line);
                string type, firm, model, price, year;
                if (!std::getline(new_string, type, ',') || !std::getline(new_string, firm, ',') || !std::getline(new_string, model, ',') || !std::getline(new_string, price, ',') || !std::getline(new_string, year, ','))
                {
                    throw std::invalid_argument("Invalid certification format");
                }
                if (type == "TV")
                {
                    string diagonal_size_str;
                    if (!std::getline(new_string, diagonal_size_str, ','))
                    {
                        throw invalid_argument("Invalid model format");
                    }
                    float diagonal_size_float;
                    string unit_str;
                    get_unit_and_size(diagonal_size_str, diagonal_size_float, unit_str);
                    add_electrocasnic_and_firm(type, firm, model, stof(price), stoi(year), diagonal_size_float, unit_str);
                }
                else if (type == "FR")
                {
                    bool has_freezer;
                    string has_freezer_str;
                    if (!getline(new_string, has_freezer_str, ','))
                    {
                        throw invalid_argument("Invalid model format");
                    }
                    if (has_freezer_str == "true" || has_freezer_str == "1")
                        has_freezer = true;
                    else if (has_freezer_str == "false" || has_freezer_str == "0")
                        has_freezer = false;
                    else
                        throw invalid_argument("Invalid has_freezer value");
                    add_electrocasnic_and_firm(type, firm, model, stof(price), stoi(year), has_freezer);
                }
                else if (type == "MS")
                {
                    string load_capacity;
                    if (!getline(new_string, load_capacity, ','))
                    {
                        throw invalid_argument("Invalid model format");
                    }
                    add_electrocasnic_and_firm(type, firm, model, stof(price), stoi(year), stof(load_capacity));
                }
            }
            catch (const std::invalid_argument &e)
            {
                cout << "Error on reading on line:  " << line_nr << ": " << e.what() << endl;
            }
        }
    }
    catch (const fstream::failure &e)
    {
        cout << "Error reading file on line " << line_nr << ": " << e.what() << endl;
    }
}

bool Service::verify_electrocasnic_existence(const string &firm, const string &type) const
{
    for (vector<unique_ptr<Electrocasnice>>::const_iterator it = Electrocasnice_list.begin(); it != Electrocasnice_list.end(); ++it)
    {
        if ((*it)->get_firm() == firm && (*it)->get_type() == type)
        {
            return true;
        }
    }
    return false;
}

void Service::add_electrocasnic_and_firm(const string &type, const string &firm, const string &model, const float &price, const int &year, const float &diagonal_size, const string &unit)
{
    if (!verify_electrocasnic_existence(firm, type))
    {
        Electrocasnice_list.push_back(std::make_unique<TV>(firm, type, model, price, year, diagonal_size, unit));
        fstream file;
        file.open("./tests/Electronics_raport.csv", ios::out | ios::app);
        file << "Added TV from firm: " << firm << endl;
        file.close();
    }
    else
        throw std::invalid_argument("You cannot add an existing electronic to the service. ");
}
void Service::add_electrocasnic_and_firm(const string &type, const string &firm, const string &model, const float &price, const int &year, const bool &has_freezer)
{
    if (!verify_electrocasnic_existence(firm, type))
    {
        Electrocasnice_list.push_back(std::make_unique<Frigider>(firm, type, model, price, year, has_freezer));
        fstream file;
        file.open("./tests/Electronics_raport.csv", ios::out | ios::app);
        file << "Added Frigider from firm: " << firm << endl;
        file.close();
    }
    else
        throw std::invalid_argument("You cannot add an existing electronic to the service. ");
}

void Service::add_electrocasnic_and_firm(const string &type, const string &firm, const string &model, const float &price, const int &year, const float &load_capacity)
{
    if (!verify_electrocasnic_existence(firm, type))
    {
        Electrocasnice_list.push_back(std::make_unique<Washer>(firm, type, model, price, year, load_capacity));
        fstream file;
        file.open("./tests/Electronics_raport.csv", ios::out | ios::app);
        file << "Added Washer from firm: " << firm << endl;
        file.close();
    }
    else
        throw std::invalid_argument("You cannot add an existing electronic to the service. ");
}

void Service::delete_firm(const string &firm, const string &type)
{
    int found = 0;
    for (vector<unique_ptr<Electrocasnice>>::iterator it = Electrocasnice_list.begin(); it != Electrocasnice_list.end(); ++it)
    {
        if ((*it)->get_firm() == firm && (*it)->get_type() == type)
        {
            it = Electrocasnice_list.erase(it);
            found++;
            it--;
        }
    }
    if (found == 0)
        throw std::invalid_argument("Electrocasnic with the given firm and type not found.");
}

void Service::delete_model(const string &model, const string &type)
{
    int found = 0;
    for (vector<unique_ptr<Electrocasnice>>::iterator it = Electrocasnice_list.begin(); it != Electrocasnice_list.end(); ++it)
    {
        if ((*it)->get_model() == model && (*it)->get_type() == type)
        {
            it = Electrocasnice_list.erase(it);
            found++;
            it--;
        }
    }
    if (found == 0)
        throw std::invalid_argument("Electrocasnic with the given firm and type not found.");
}

void Service::show_all_electrocasnice() const
{
    for (vector<unique_ptr<Electrocasnice>>::const_iterator it = Electrocasnice_list.begin(); it != Electrocasnice_list.end(); ++it)
    {
        (*it)->display_info();
        cout << '\n';
    }
}

Electrocasnice *Service::find_type_from_firm(const string &firm, const string &type)
{
    if (verify_electrocasnic_existence(firm, type))
    {
        for (vector<unique_ptr<Electrocasnice>>::const_iterator it = Electrocasnice_list.begin(); it != Electrocasnice_list.end(); ++it)
            if ((*it)->get_firm() == firm && (*it)->get_type() == type)
                return it->get();
    }
    return nullptr;
}
// Request Management

void Service::read_requests(const string &filename)
{
    fstream file;
    int line_nr = 0;
    try
    {
        file.exceptions(fstream::badbit);
        file.open(filename, ios::in);
        string line;

        while (std::getline(file, line))
        {
            line_nr++;
            try
            {
                stringstream new_string(line);
                string complexity_str, type, firm, model, price, year;
                std::getline(new_string, complexity_str, ',');
                if (complexity_str < "0" || complexity_str > "5'")
                    throw invalid_argument("Complexity level must be between 0 and 5.");

                if (!std::getline(new_string, type, ',') || !std::getline(new_string, firm, ',') || !std::getline(new_string, model, ',') || !std::getline(new_string, price, ','))
                {
                    throw std::invalid_argument("Invalid format");
                }
                if (stof(price) < 0)
                    throw invalid_argument("Price cannot be negative.");

                std::getline(new_string, year, ',');
                if (stoi(year) < 1900 || stoi(year) > GetTime::getcurentYear())
                    throw invalid_argument("Year is not valid.");
                if (verify_electrocasnic_existence(firm, type) == false)
                {
                    Electrocasnice_irreparable[make_pair(firm, type)]++;
                    throw invalid_argument("Electrocasnic with the given firm and type does not exist.");
                }
                else
                {
                    if (type == "TV")
                    {
                        string diagonal_size;
                        getline(new_string, diagonal_size, ',');

                        float diagonal_size_float;
                        string unit_str;
                        get_unit_and_size(diagonal_size, diagonal_size_float, unit_str);
                        add_request_tv(stoi(complexity_str), type, firm, model, stof(price), stoi(year), diagonal_size_float, unit_str);
                    }
                    else if (type == "FR")
                    {
                        string has_freezer;
                        getline(new_string, has_freezer, ',');
                        bool has_freezer1;
                        if (has_freezer == "true" || has_freezer == "1")
                            has_freezer1 = true;
                        else if (has_freezer == "false" || has_freezer == "0")
                            has_freezer1 = false;
                        else
                            throw invalid_argument("Invalid has_freezer value");
                        add_request_frigider(stoi(complexity_str), type, firm, model, stof(price), stoi(year), has_freezer1);
                    }
                    else if (type == "MS")
                    {
                        string load_capacity;
                        getline(new_string, load_capacity, ',');
                        add_request_washer(stoi(complexity_str), type, firm, model, stof(price), stoi(year), stof(load_capacity));
                    }
                }
            }
            catch (const std::invalid_argument &e)
            {
                cout << "Error on reading on line:  " << line_nr << ": " << e.what() << endl;
            }
        }
    }
    catch (const fstream::failure &e)
    {
        cout << "Error reading file on line " << line_nr << ": " << e.what() << endl;
    }
}

void Service::add_request_tv(const int &complexity, const string &type, const string &firm, const string &model, const float &price, const int &year, const float &diagonal_size, const string &unit)
{
    Requests_list.push_back(std::make_unique<Request>(complexity, type, firm, model, price, year, diagonal_size, unit));
    fstream file;
    file.open("./tests/Requests_raport.csv", ios::out | ios::app);
    file << "Added TV request for model: " << model << endl;
    file.close();
}

void Service::add_request_frigider(const int &complexity, const string &type, const string &firm, const string &model, const float &price, const int &year, const bool &has_freezer)
{
    Requests_list.push_back(std::make_unique<Request>(complexity, type, firm, model, price, year, has_freezer));
    fstream file;
    file.open("./tests/Requests_raport.csv", ios::out | ios::app);
    file << "Added Frigider request for model: " << model << endl;
    file.close();
}

void Service::add_request_washer(const int &complexity, const string &type, const string &firm, const string &model, const float &price, const int &year, const float &load_capacity)
{
    Requests_list.push_back(std::make_unique<Request>(complexity, type, firm, model, price, year, load_capacity));
    fstream file;
    file.open("./tests/Requests_raport.csv", ios::out | ios::app);
    file << "Added Washer request for model: " << model << endl;
    file.close();
}

void Service::show_all_requests() const
{

    for (vector<unique_ptr<Request>>::const_iterator it = Requests_list.begin(); it != Requests_list.end(); ++it)
    {
        cout << "Request ID: " << (*it)->get_id_req() << '\n';
        cout << "Timestamp: " << (*it)->get_timestamp() << '\n';
        cout << "Complexity Level: " << (*it)->get_complexity_level() << '\n';
        cout << "Vechime: " << (*it)->get_vechime() << " years\n";
        cout << "Reparation Time: " << (*it)->get_reparation_time() << " hours\n";
        cout << "Reparation Price: " << (*it)->get_reparation_price() << '\n';
        cout << '\n';
    }
}

bool Service::search_electronic_in_requests(const string &type, const string &firm, const string &model, const int &year)
{
    for (vector<unique_ptr<Request>>::const_iterator it = Requests_list.begin(); it != Requests_list.end(); ++it)
    {
        if ((*it)->get_type() == type && (*it)->get_firm() == firm && (*it)->get_model() == model && (*it)->get_year() == year)
            return true;
    }
    return false;
}

void Service::delete_request(const string &type, const string &firm, const string &model, const int &year)
{
    int found = 0;
    for (vector<unique_ptr<Request>>::iterator it = Requests_list.begin(); it != Requests_list.end(); ++it)
    {
        if ((*it)->get_firm() == firm && (*it)->get_type() == type && (*it)->get_model() == model && (*it)->get_year() == year)
        {
            it = Requests_list.erase(it);
            found++;
            it--;
        }
    }
    if (found == 0)
        throw std::invalid_argument("Electrocasnic with the given firm and type not found.");
}

void Service::clear_requests_lists()
{
    sort(Employees_list.begin(), Employees_list.end(), [](const std::unique_ptr<Service_Employes> &a, const std::unique_ptr<Service_Employes> &b)
         { return a->get_type() < b->get_type(); });

    for (vector<unique_ptr<Service_Employes>>::iterator it = Employees_list.begin(); it != Employees_list.end(); ++it)
    {
        if ((*it)->get_type() == "R")
        {
            Receptionist *rec_ptr = dynamic_cast<Receptionist *>(it->get());
            rec_ptr->clear_request();
        }
    }
}

void Service::share_requests_to_rec()
{
    clear_requests_lists();
    vector<unique_ptr<Service_Employes>>::iterator it = Employees_list.begin();
    vector<unique_ptr<Request>>::const_iterator re = Requests_list.begin();
    int nr = 0;

    if (nr_rec == 0)
        throw std::invalid_argument("No receptionist found");

    while (re != Requests_list.end())
    {
        if ((*it)->get_type() == "R")
        {
            nr++;
            Receptionist *rec_ptr = dynamic_cast<Receptionist *>(it->get());
            if (rec_ptr)
            {
                rec_ptr->add_request((*re)->get_id_req());
            }
            re++;
            if (nr == nr_rec)
                it = Employees_list.begin();
            else
                it++;
        }
        else
            it = Employees_list.begin();
    }
}

void Service::add_request_to_an_rec(const string &id)
{
    int min = Requests_list.size();
    Receptionist *poz = nullptr;

    for (vector<unique_ptr<Service_Employes>>::const_iterator it = Employees_list.begin(); it != Employees_list.end(); ++it)
    {
        if ((*it)->get_type() == "R")
        {
            Receptionist *rec_ptr = dynamic_cast<Receptionist *>(it->get());
            if (rec_ptr->requests_list_size() < min)
                min = rec_ptr->requests_list_size();
            poz = rec_ptr;
        }
    }
    if (poz != nullptr)
    {
        poz->add_request(id);
    }
    else
        throw std::invalid_argument("No receptionist found in service");
}

int Service::get_request_list_dim() const
{
    int dim = Requests_list.size();
    return dim;
}

Request *Service::get_last_request()
{
    return Requests_list.back().get();
}

const string &Service::get_request_id(const string &type, const string &firm, const string &model, const int &year)
{
    int found = 0;
    for (vector<unique_ptr<Request>>::iterator it = Requests_list.begin(); it != Requests_list.end(); ++it)
    {
        if ((*it)->get_firm() == firm && (*it)->get_type() == type && (*it)->get_model() == model && (*it)->get_year() == year)
            return (*it)->get_id_req();
    }
    throw std::invalid_argument("Request doesnt exit in our service");
}

void Service::delete_request_from_an_rec(const string &id)
{
    for (vector<unique_ptr<Electrocasnice>>::iterator it = Electrocasnice_list.begin(); it != Electrocasnice_list.end(); ++it)
    {
        if ((*it)->get_type() == "R")
        {
            Receptionist *rec_ptr = dynamic_cast<Receptionist *>(it->get());
            if (rec_ptr->verify_request(id))
            {
                rec_ptr->delete_request(id);
                return;
            }
        }
    }
}

// Reports Management
void Service::irreparable_report() const
{
    vector<pair<pair<string, string>, int>> irreparable_list_sorted;
    for (map<pair<string, string>, int>::const_iterator it = Electrocasnice_irreparable.begin(); it != Electrocasnice_irreparable.end(); ++it)
    {
        irreparable_list_sorted.push_back(make_pair(it->first, it->second));
    }

    sort(irreparable_list_sorted.begin(), irreparable_list_sorted.end(), [](const pair<pair<string, string>, int> &a, const pair<pair<string, string>, int> &b)
         { return a.second > b.second; });

    fstream file;
    try
    {
        file.exceptions(fstream::failbit | fstream::badbit);
        file.open("./tests/irreparable_report.csv", ios::out);
        for (vector<pair<pair<string, string>, int>>::const_iterator it = irreparable_list_sorted.begin(); it != irreparable_list_sorted.end(); ++it)
        {
            file << "Firm: " << it->first.first << ", Type: " << it->first.second << ", Irreparable Count: " << it->second << '\n';
        }
        file.close();
    }
    catch (const fstream::failure &e)
    {
        cout << "Error irreparable report: " << e.what() << endl;
    }
}

// Simulation Management

bool Service::verify_posibilyty_of_runing() const
{
    int teh_nr = 0;
    int rec_nr = 0;
    int sup_nr = 0;
    for (vector<unique_ptr<Service_Employes>>::const_iterator it = Employees_list.begin(); it != Employees_list.end(); ++it)
    {
        Tehnician *teh_ptr = dynamic_cast<Tehnician *>(it->get());
        Receptionist *rec_ptr = dynamic_cast<Receptionist *>(it->get());
        Supervisor *sup_ptr = dynamic_cast<Supervisor *>(it->get());
        if (teh_ptr != nullptr)
            teh_nr++;
        else if (rec_ptr != nullptr)
            rec_nr++;
        else if (sup_ptr != nullptr)
            sup_nr++;
    }
    if (teh_nr >= 3 && rec_nr >= 1 && sup_nr >= 1)
    {
        cout << " Sufficient employees available to run the service.\n";
        return true;
    }
    cout << " Insufficient employees to run the service.\n";
    return false;
}

Tehnician *Service::get_correct_tehnician(const string &type, const string &firm)
{
    int min_jobs = 4;
    long int min_hours_worked = 10000000000;
    Tehnician *poz = nullptr;
    for (vector<unique_ptr<Service_Employes>>::const_iterator it = Employees_list.begin(); it != Employees_list.end(); ++it)
    {
        if ((*it)->get_type() == "T")
        {

            Tehnician *teh_ptr = dynamic_cast<Tehnician *>(it->get());
            if (teh_ptr->verify_certification(type, firm))
            {
                if (teh_ptr->get_number_of_jobs() < 3)
                {
                    if (teh_ptr->get_number_of_jobs() < min_jobs)
                    {
                        min_jobs = teh_ptr->get_number_of_jobs();
                        min_hours_worked = teh_ptr->get_total_hours_worked();
                        poz = teh_ptr;
                    }
                    else if (teh_ptr->get_number_of_jobs() == min_jobs)
                    {
                        if (teh_ptr->get_total_hours_worked() < min_hours_worked)
                        {
                            min_hours_worked = teh_ptr->get_total_hours_worked();
                            poz = teh_ptr;
                        }
                    }
                }
            }
        }
    }
    return poz;
}

bool Service::teh_working() const
{
    for (vector<unique_ptr<Service_Employes>>::const_iterator it = Employees_list.begin(); it != Employees_list.end(); it++)
    {
        if ((*it)->get_type() == "T")
        {
            Tehnician *teh = dynamic_cast<Tehnician *>((*it).get());
            if (teh != nullptr && teh->get_number_of_jobs() > 0)
                return true;
        }
    }
    return false;
}

void Service::simulate()
{
    if (verify_posibilyty_of_runing())
    {
        queue<Request *> Pending_requests;
        queue<Request *> irreparable_req;

        for (vector<unique_ptr<Request>>::iterator it = Requests_list.begin(); it != Requests_list.end(); ++it)
            Pending_requests.push((*it).get());

        int timestamp = 0;

        while (!Pending_requests.empty() || teh_working())
        {
            timestamp++;
            fstream file;
            file.open("./tests/Simulation.csv", ios::out | ios::app);

            file << "\n--- Second " << timestamp << " ---\n";
            file.close();
            int current_queue_size = Pending_requests.size();
            for (int i = 0; i < current_queue_size; ++i)
            {
                Request *req = Pending_requests.front();
                Pending_requests.pop();
                Tehnician *teh = get_correct_tehnician(req->get_type(), req->get_firm());

                if (teh)
                {
                    fstream file;
                    file.open("./tests/Simulation.csv", ios::out | ios::app);
                    teh->add_to_local_queue(req);
                    file << "[Allocation] Request " << req->get_id_req() << " add to " << teh->get_name() << "\n";
                    file.close();
                }
                else
                {
                    irreparable_req.push(req);
                }
            }
            for (vector<unique_ptr<Service_Employes>>::const_iterator it = Employees_list.begin(); it != Employees_list.end(); it++)
            {
                if ((*it)->get_type() == "T")
                {
                    Tehnician *teh = dynamic_cast<Tehnician *>((*it).get());
                    teh->work();
                    teh->display_status();
                }
            }
        }
        fstream file;
        file.open("./tests/Simulation.csv", ios::out | ios::app);
        file << "\nSimulation finished at second: " << timestamp << ".\n";
        file.close();
    }
    else
    {
        fstream file;
        file.open("./tests/Simulation.csv", ios::out | ios::app);
        file << "Simulation cant start!";
        file.close();
    }
}
