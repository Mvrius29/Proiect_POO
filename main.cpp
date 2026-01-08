#include "Service.h"
#include <iostream>
#include "Meniu.h"

int main() {
    Service service;
    service.read_employees("employees.txt");
    service.show_all_employees();
    service.read_electrocasnice("electrocasnice.txt");
    main_menu(service);

    return 0;
}
