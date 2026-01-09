#include "Meniu.h"

void cnp_reading(string &searched_cnp)
{
    cout << "Enter the cnp: ";
    cin >> searched_cnp;
}

void read_tv_details(float &diagonal_size, string &unit)
{
    cout << "\nDiagonal size: ";
    cin >> diagonal_size;
    cout << "\nUnit:";
    cin >> unit;
}

void read_fr_details(bool &has_freezer)
{
    string has_freezer_str;
    cout << "\nIt has freezer?(Y/N)";
    cin >> has_freezer_str;
    if (has_freezer_str == "Y")
        has_freezer = true;
    else if (has_freezer_str == "N")
        has_freezer = false;
    else
        throw invalid_argument("Invalid has_freezer value");
}

void read_info_employ(string &name, string &second_name, string &cnp, string &employment_date, string &city)
{
    cout << "Name: ";
    cin >> name;
    cout << "\nSecond Name: ";
    cin >> second_name;
    cout << "\nCNP: ";
    cin >> cnp;
    employment_date = GetTime::getEmploymentDate();
    cout << "\nCity: ";
    cin >> city;
}

void read_electronic_basic_info(string &type, string &firm, string &model, float &price, int &year)
{
    cout << "\nType: ";
    cin >> type;
    cout << "\nFirm name: ";
    cin >> firm;
    cout << "\nModel: ";
    cin >> model;
    cout << "\nPrice: ";
    cin >> price;
    cout << "\nYear: ";
    cin >> year;
}

void main_menu(Service &service)
{
    int option = -1;
    while (option)
    {
        cout << "Main menu for service FixitNow" << "\n";
        cout << "1 -> Employees administration" << "\n";
        cout << "2 -> Electrocasnic administration" << "\n";
        cout << "3 -> Requests administration" << "\n";
        cout << "4 -> Start simulation" << "\n";
        cout << "5 -> EXIT" << "\n";
        cin >> option;

        switch (option)
        {
        case 1:
            employees_menu(service);
            break;
        case 2:
            electronics_menu(service);
            break;
        case 3:
            requests_menu(service);
            break;
        case 4:
            if (service.verify_posibilyty_of_runing())
            {
                // start_simulation(service);
            }
            break;
        case 5:
            cout << "Exiting... Goodbye!\n";
            return;
        default:
            cout << "Invalid option!\n";
            break;
        }
    }
}

void employees_menu(Service &service)
{
    int mode = -1;
    cout << "\n1 -> Show all employees" << "\n";
    cout << "2 -> Search employee" << "\n";
    cout << "3 -> Add employee" << "\n";
    cout << "4 -> Delete employee" << "\n";
    cout << "5 -> Top 3 biggest salary of the month" << "\n";
    cout << "6 -> Back to main menu\n";

    cin >> mode;

    if (mode == 1)
    {
        service.show_all_employees();
        employees_menu(service);
    }
    else if (mode == 2)
    {
        string searched_cnp;
        cnp_reading(searched_cnp);
        try
        {
            service.find_employee(searched_cnp);
        }
        catch (const std::invalid_argument &e)
        {
            cout << e.what() << "\n";
        }
        employees_menu(service);
    }
    else if (mode == 3)
    {
        string type;
        cout << "Which type of employee do you want to add(T, R, S): ";
        cin >> type;
        cout << "\n";
        try
        {
            if (type == "T")
            {
                string name, second_name, cnp, employment_date, city;
                int number_of_certifications;
                string type, firm;
                read_info_employ(name, second_name, cnp, employment_date, city);
                cout << "Number of certifications: ";
                cin >> number_of_certifications;
                vector<pair<string, string>> cert;
                for (int i = 1; i <= number_of_certifications; i++)
                {
                    cout << "\nFirm: ";
                    cin >> firm;
                    cout << "\nType: ";
                    cin >> type;
                    cert.push_back(make_pair(firm, type));
                }
                service.add_employee_teh(type, name, second_name, cnp, employment_date, city, cert);
            }
            else if (type == "R")
            {
                string name, second_name, cnp, employment_date, city;
                read_info_employ(name, second_name, cnp, employment_date, city);
                int number_of_requests;
                vector<string> req;
                service.add_employee_rec(type, name, second_name, cnp, employment_date, city, req);
            }
            else if (type == "S")
            {
                string name, second_name, cnp, employment_date, city;
                read_info_employ(name, second_name, cnp, employment_date, city);
                service.add_employee_sup(type, name, second_name, cnp, employment_date, city);
            }
        }
        catch (const std::invalid_argument &e)
        {
            cout << e.what() << '\n';
        }
        employees_menu(service);
    }
    else if (mode == 4)
    {
        string searched_cnp;
        cnp_reading(searched_cnp);
        try
        {
            service.delete_employee(searched_cnp);
            cout<< "Emplyee with the CNP: " << searched_cnp << " deleted succesfully";
        }
        catch (const std::invalid_argument &e)
        {
            cout << e.what() << "\n";
        }
        employees_menu(service);
    }
    else if (mode == 5)
    {
        try
        {
            service.run_top3_performers();
            cout<<"Operation succeded!";
        }
        catch (const std::invalid_argument &e)
        {
            cout << e.what() << "\n";
        }
        employees_menu(service);
    }
    else if (mode == 6)
    {
        main_menu(service);
    }
}

void electronics_menu(Service &service)
{
    int mode;
    cout << "\n1 -> Show all serviceable electronics" << "\n";
    cout << "2 -> Show all unserviceable eletronics" << "\n";
    cout << "3 -> Add model" << "\n";
    cout << "4 -> Delete model" << "\n";
    cout << "5 -> Add firm" << "\n";
    cout << "6 -> Delete firm\n";
    cout << "7 -> Back to main menu\n";

    cin >> mode;

    if (mode == 1)
    {
        service.show_all_electrocasnice();
        electronics_menu(service);
    }
    else if (mode == 2)
    {
        service.irreparable_report();
        cout << "Verify irreparable_report.csv to see the results";
        electronics_menu(service);
    }
    else if (mode == 3 || mode == 5)
    {
        string type, firm, model;
        float price;
        int year;
        cout << "Enter the type of electronic which you want to add(TV, FR, MS): ";
        read_electronic_basic_info(type, firm, model, price, year);
        try
        {
            if (type == "TV")
            {
                string unit;
                float diagonal_size;
                read_tv_details(diagonal_size, unit);
                service.add_electrocasnic_and_firm(type, firm, model, price, year, diagonal_size, unit);
            }
            else if (type == "FR")
            {
                bool has_freezer;
                read_fr_details(has_freezer);
                service.add_electrocasnic_and_firm(type, firm, model, price, year, has_freezer);
            }
            else if (type == "MS")
            {
                float load_capacity;
                cout << "\nLoad capacity: ";
                cin >> load_capacity;
                service.add_electrocasnic_and_firm(type, firm, model, price, year, load_capacity);
            }
        }
        catch (const std::invalid_argument &e)
        {
            cout << e.what();
        }
        electronics_menu(service);
    }
    else if (mode == 4)
    {
        string model, type;
        cout << "\nEnter type: ";
        cin >> type;
        cout << "\nEnter the model name: ";
        cin >> model;
        try
        {
            service.delete_model(model, type);
             cout<<"Electronic model  : " << model << " " << type << " deleted successfully";
        }
        catch (const std::invalid_argument &e)
        {
            cout << e.what() << "\n";
        }
        electronics_menu(service);
    }
    else if (mode == 6)
    {
        string firm, type;
        cout << "\nEnter type: ";
        cin >> type;
        cout << "\nEnter the firm name: ";
        cin >> firm;
        try
        {
            service.delete_firm(firm, type);
            cout<<"Electronic : " << firm << " " << type << " deleted successfully";
        }
        catch (const std::invalid_argument &e)
        {
            cout << e.what() << "\n";
        }
        electronics_menu(service);
    }
    else if (mode == 7)
    {
        main_menu(service);
    }
}

void requests_menu(Service &service)
{

    int mode;
    cout << "\n1 -> Show all requests" << "\n";
    cout << "2 -> Add request" << "\n";
    cout << "3 -> Delete request" << "\n";
    cout << "4 -> Back to main menu\n";

    cin >> mode;

    if (mode == 1)
    {
        service.show_all_requests();
        requests_menu(service);
    }
    else if (mode == 2)
    {
        string type, firm, model;
        float price;
        int year, complexity;
        cout << "\n Complexity";
        cin >> complexity;
        read_electronic_basic_info(type, firm, model, price, year);
        try
        {if(!service.search_electronic_in_requests(type,firm,model,year)){
            if (type == "TV")
            {
                float diagonal_size;
                string unit;
                read_tv_details(diagonal_size, unit);
                service.add_request_tv(complexity, type, firm, model, price, year, diagonal_size, unit);
            }
            else if (type == "FR")
            {
                bool has_freezer;
                read_fr_details(has_freezer);
                service.add_request_frigider(complexity, type, firm, model, price, year, has_freezer);
            }
            else if (type == "MS")
            {
                float load_capacity;
                cout << "\nLoad capacity: ";
                cin >> load_capacity;
                service.add_request_washer(complexity, type, firm, model, price, year, load_capacity);
            }
        }
        else throw std::invalid_argument("A request for this model is already existing in our system");
        }
        catch (const std::invalid_argument &e)
        {
            cout << e.what() << "\n";
        }
        requests_menu(service);
    }
    else if (mode == 3)
    {
        string type, firm, model;
        float price;
        int year;
        read_electronic_basic_info(type, firm, model, price, year);
        if(!service.search_electronic_in_requests(type,firm,model,year)){
             throw std::invalid_argument("This request doesnt exist in our system");
        }
        else {
            try{
                service.delete_request(type,firm,model,year);
                cout<<"Request for: " << type << " " << firm << " -> " << model << " -> " << year << " deleted succesfully";
            }catch(const std::invalid_argument &e){
                cout << e.what() << "\n";
            }  
        } 
         requests_menu(service);
    }
    else if(mode == 4)
       main_menu(service);
}