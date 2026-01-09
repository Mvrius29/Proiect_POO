#include "Service_Employes.h"

void Service_Employes::age_verification(const string &cnp)
{
    if (cnp.size() != 13)
        throw std::invalid_argument("CNP must have 13 digits.");
    string validation_number = "279146358279";
    int number = 0;
    for (int i = 0; i < 12; i++)
        number += (cnp[i] - '0') * (validation_number[i] - '0');
    if (number % 11 == 10)
        number = 1;
    else
        number = number % 11;
    if (number != (cnp[12] - '0'))
        throw std::invalid_argument("CNP is not valid.");
    int year = stoi(cnp.substr(1, 2));
    int month = stoi(cnp.substr(3, 2));
    int day = stoi(cnp.substr(5, 2));
    switch (cnp[0])
    {
    case '1':
    case '2':
        year += 1900;
        break;
    case '3':
    case '4':
        throw std::invalid_argument("CNP is not valid.");
        break;
    case '5':
    case '6':
        year += 2000;
        break;
    default:
        throw std::invalid_argument("CNP is not valid.");
    }

    int curentYear = GetTime::getcurentYear();
    int curentMonth = GetTime::getcurentMonth();
    int curentDay = GetTime::getcurentDay();

    int years = curentYear - year;

    if (curentMonth < month || (curentMonth == month && curentDay < day))
        years--;
    if (years < 16)
        throw std::invalid_argument("Employee must be over 16 years old.");
        else CNP = cnp;
}

void Service_Employes::set_name(const string &name1)
{
    if (name1.size() < 3 || name1.size() > 30)
        throw std::invalid_argument("Name must be between 3 and 30 characters.");
    name = name1;
}

void Service_Employes::set_second_name(const string &second_name1)
{
    if (second_name1.size() < 3 || second_name1.size() > 30)
        throw std::invalid_argument("Second name must be between 3 and 30 characters.");
    second_name = second_name1;
}

Service_Employes::Service_Employes(const string &name1, const string &second_name1, const string &cnp, const string &employment_date1, const string &city1)
    : employment_date{employment_date1}, city{city1}
{
    age_verification(cnp);
    set_name(name1);
    set_second_name(second_name1);
    cout << "Employee " << name << " " << second_name << " created successfully.\n";
}

void Service_Employes::modify_name(const string &new_name)
{
    set_name(new_name);
}

int Service_Employes::get_time_with_company()
{
    int curentDay = GetTime::getcurentDay();
    int curentMonth = GetTime::getcurentMonth();
    int curentYear = GetTime::getcurentYear();

    int employmentYear = stoi(employment_date.substr(0, 4));
    int employmentMonth = stoi(employment_date.substr(5, 2));
    int employmentDay = stoi(employment_date.substr(8, 2));

    int years = curentYear - employmentYear;
    if (curentMonth < employmentMonth || (curentMonth == employmentMonth && curentDay < employmentDay))
        years--;
    return years;
}

void Service_Employes::display_info()
{
    cout << "ID: " << id << '\n';
    cout << "Name: " << name << " " << second_name << '\n';
    cout << "CNP: " << CNP << '\n';
    cout << "Employment Date: " << employment_date << '\n';
    cout << "City: " << city << '\n';
    cout << "Curent salary: " << get_salary() << '\n';
}

const string &Service_Employes::get_CNP() const
{
    return CNP;
}

const string &Service_Employes::get_name() const
{
    return name;
}

const string &Service_Employes::get_second_name() const
{
    return second_name;
}

const string& Service_Employes::get_type() const{
     return type;
}

Service_Employes::~Service_Employes() {}


