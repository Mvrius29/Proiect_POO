#include "Service.h"

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
        file.exceptions(fstream::failbit | fstream::badbit);
        file.open(filename, ios::in);
        string line;

        while (getline(file, line))
        {
            line_nr++;
            try
            {
                stringstream new_string(line);
                string role, name, second_name, cnp, employment_date, city;
                getline(new_string, role, ',');
                getline(new_string, name, ',');
                getline(new_string, second_name, ',');
                getline(new_string, cnp, ',');
                getline(new_string, employment_date, ',');
                getline(new_string, city, ',');
                if (role == "T")
                {
                    string certifictions_str, type, firm;
                    vector<pair<string, string>> certifications;
                    while (new_string.good())
                    {
                        if (!getline(new_string, type, ',') || !getline(new_string, firm, ','))
                        {
                            throw invalid_argument("Invalid certification format");
                        }
                        certifications.emplace_back(type, firm);
                    }
                    add_employee_teh(role, name, second_name, cnp, employment_date, city, certifications);
                }
                else if (role == "R")
                {
                    string requests_str, request;
                    vector<string> requests;
                    while (getline(new_string, request, ','))
                    {
                        requests.push_back(request);
                    }
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

void Service::add_employee_sup(const string &role, const string &name, const string &second_name, const string &cnp, const string &employment_date, const string &city)
{
    Employees_list.push_back(std::make_unique<Supervisor>(name, second_name, cnp, employment_date, city));
    cout << "Added supervisor with CNP: " << cnp << endl;
}

void Service::add_employee_teh(const string &role, const string &name, const string &second_name, const string &cnp, const string &employment_date, const string &city, const vector<pair<string, string>> &certifications)
{
    Employees_list.push_back(std::make_unique<Tehnician>(name, second_name, cnp, employment_date, city, certifications));
    cout << "Added technician with CNP: " << cnp << endl;
}

void Service::add_employee_rec(const string &role, const string &name, const string &second_name, const string &cnp, const string &employment_date, const string &city, const vector<string> &requests)
{
    Employees_list.push_back(std::make_unique<Receptionist>(name, second_name, cnp, employment_date, city, requests));
    cout << "Added receptionist with CNP: " << cnp << endl;
}

void Service::delete_employee(const string &cnp)
{
    for (vector<unique_ptr<Service_Employes>>::iterator it = Employees_list.begin(); it != Employees_list.end(); ++it)
    {
        if ((*it)->get_CNP() == cnp)
        {
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
        file.exceptions(fstream::failbit | fstream::badbit);
        file.open(filename, ios::in);
        string line;

        while (getline(file, line))
        {
            line_nr++;
            try
            {
                stringstream new_string(line);
                string type, firm, model, price, year, number_of_models;
                vector<pair<pair<string, float>, int>> model_price_year;
                getline(new_string, type, ',');
                getline(new_string, firm, ',');

                if (type == "TV")
                {
                    string diagonal_size, unit;

                    while (new_string.good())
                    {
                        if (!getline(new_string, diagonal_size, ',') || !getline(new_string, model, ',') || !getline(new_string, price, ',') || !getline(new_string, year, ','))
                        {
                            throw invalid_argument("Invalid model format");
                        }
                        model_price_year.push_back(make_pair(make_pair(model, stoi(price)), stoi(year)));
                    }
                    float diagonal_size_float;
                    string unit_str;
                    get_unit_and_size(diagonal_size, diagonal_size_float, unit_str);
                    add_electrocasnic_and_firm(type, firm, model_price_year, diagonal_size_float, unit_str);
                }
                else if (type == "FR")
                {
                    bool has_freezer;
                    string has_freezer_str;
                    while (new_string.good())
                    {
                        if (!getline(new_string, has_freezer_str, ',') || !getline(new_string, model, ',') || !getline(new_string, price, ',') || !getline(new_string, year, ','))
                        {
                            throw invalid_argument("Invalid model format");
                        }
                        if (has_freezer_str == "true")
                            has_freezer = true;
                        else if (has_freezer_str == "false")
                            has_freezer = false;
                        else
                            throw invalid_argument("Invalid has_freezer value");
                        model_price_year.push_back(make_pair(make_pair(model, stoi(price)), stoi(year)));
                    }
                    add_electrocasnic_and_firm(type, firm, model_price_year, has_freezer);
                }
                else if (type == "MS")
                {
                    string load_capacity;
                    while (new_string.good())
                    {
                        if (!getline(new_string, load_capacity, ',') || !getline(new_string, model, ',') || !getline(new_string, price, ',') || !getline(new_string, year, ','))
                        {
                            throw invalid_argument("Invalid model format");
                        }
                        model_price_year.push_back(make_pair(make_pair(model, stoi(price)), stoi(year)));
                    }
                    add_electrocasnic_and_firm(type, firm, model_price_year, stof(load_capacity));
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

void Service::add_electrocasnic_and_firm(const string &type, const string &firm, const vector<pair<pair<string, float>, int>> &model_price_year, const float &diagonal_size, const string &unit)
{
    Electrocasnice_list.push_back(std::make_unique<TV>(firm, type, model_price_year, diagonal_size, unit));
    cout << "Added TV from firm: " << firm << endl;
}

void Service::add_electrocasnic_and_firm(const string &type, const string &firm, const vector<pair<pair<string, float>, int>> &model_price_year, const bool &has_freezer)
{
    Electrocasnice_list.push_back(std::make_unique<Frigider>(firm, type, model_price_year, has_freezer));
    cout << "Added Frigider from firm: " << firm << endl;
}

void Service::add_electrocasnic_and_firm(const string &type, const string &firm, const vector<pair<pair<string, float>, int>> &model_price_year, const float &load_capacity)
{
    Electrocasnice_list.push_back(std::make_unique<Washer>(firm, type, model_price_year, load_capacity));
    cout << "Added Washer from firm: " << firm << endl;
}

void Service::delete_firm(const string &firm, const string &type)
{
    for (vector<unique_ptr<Electrocasnice>>::iterator it = Electrocasnice_list.begin(); it != Electrocasnice_list.end(); ++it)
    {
        if ((*it)->get_firm() == firm && (*it)->get_type() == type)
        {
            Electrocasnice_list.erase(it);
            return;
        }
    }
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

// Request Management

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

void Service::read_requests(const string &filename)
{
    fstream file;
    int line_nr = 0;
    try
    {
        file.exceptions(fstream::failbit | fstream::badbit);
        file.open(filename, ios::in);
        string line;

        while (getline(file, line))
        {
            line_nr++;
            try
            {
                stringstream new_string(line);
                string complexity_str, type, firm, model, price, year;
                getline(new_string, complexity_str, ',');
                if (complexity_str < "0" || complexity_str > "5'")
                    throw invalid_argument("Complexity level must be between 0 and 5.");

                getline(new_string, type, ',');
                getline(new_string, firm, ',');
                getline(new_string, model, ',');
                getline(new_string, price, ',');
                if (stof(price) < 0)
                    throw invalid_argument("Price cannot be negative.");

                getline(new_string, year, ',');
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
                        if (diagonal_size_float <= 0)
                            throw invalid_argument("Diagonal size must be positive.");

                        if (unit_str.empty() || (unit_str != "cm" && unit_str != "inch"))
                            throw invalid_argument("Invalid unit value");
                        add_request_tv(stoi(complexity_str), type, firm, model, stof(price), stoi(year), diagonal_size_float, unit_str);
                    }
                    else if (type == "FR")
                    {
                        string has_freezer;
                        getline(new_string, has_freezer, ',');
                        bool has_freezer1;
                        if (has_freezer == "true")
                            has_freezer1 = true;
                        else if (has_freezer == "false")
                            has_freezer1 = false;
                        else
                            throw invalid_argument("Invalid has_freezer value");
                        add_request_frigider(stoi(complexity_str), type, firm, model, stof(price), stoi(year), has_freezer1);
                    }
                    else if (type == "MS")
                    {
                        string load_capacity;
                        getline(new_string, load_capacity, ',');
                        if (stof(load_capacity) <= 0)
                            throw invalid_argument("Load capacity must be positive.");
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
    cout << "Added TV request for model: " << model << endl;
}

void Service::add_request_frigider(const int &complexity, const string &type, const string &firm, const string &model, const float &price, const int &year, const bool &has_freezer)
{
    Requests_list.push_back(std::make_unique<Request>(complexity, type, firm, model, price, year, has_freezer));
    cout << "Added Frigider request for model: " << model << endl;
}

void Service::add_request_washer(const int &complexity, const string &type, const string &firm, const string &model, const float &price, const int &year, const float &load_capacity)
{
    Requests_list.push_back(std::make_unique<Request>(complexity, type, firm, model, price, year, load_capacity));
    cout << "Added Washer request for model: " << model << endl;
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
    if (teh_nr >= 3 && rec_nr >= 1 && sup_nr >= 1){
        cout <<" Sufficient employees available to run the service.\n";
        return true;
    }
    cout<<" Insufficient employees to run the service.\n";
    return false;
}


// Reports Management
void Service::irreparable_report() const{
    vector<pair<pair<string,string>,int>> irreparable_list_sorted;
    for(map<pair<string,string>,int>::const_iterator it = Electrocasnice_irreparable.begin(); it != Electrocasnice_irreparable.end(); ++it){
        irreparable_list_sorted.push_back(make_pair(it->first, it->second));
    }

    sort(irreparable_list_sorted.begin(), irreparable_list_sorted.end(), [](const pair<pair<string,string>,int> &a, const pair<pair<string,string>,int> &b){
        return a.second > b.second;
    });

    fstream file;
    try{
        file.exceptions(fstream::failbit | fstream::badbit);
        file.open("irreparable_report.csv", ios::out);
        for(vector<pair<pair<string,string>,int>>::const_iterator it = irreparable_list_sorted.begin(); it != irreparable_list_sorted.end(); ++it){
            file << "Firm: " << it->first.first << ", Type: " << it->first.second << ", Irreparable Count: " << it->second << '\n';
        }
        file.close();
    }catch(const fstream::failure &e){
        cout << "Error irreparable report: " << e.what() << endl;
    }
}