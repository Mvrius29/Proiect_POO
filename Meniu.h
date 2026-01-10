#pragma once 
#include "Service.h"
#include "GetTime.h"
#include <fstream>
using namespace std;

void cnp_reading(string &);
void read_info_employ(string &, string &,string &,string &,string &);
void read_tv_details(float &, string &);
void read_fr_details(bool &);
void read_electronic_basic_info(string &, string &,string &,float &,int & );


void main_menu(Service &);
void employees_menu(Service &);
void electronics_menu(Service &);
void requests_menu(Service &);
void simulation_menu(Service &);

