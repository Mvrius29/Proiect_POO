#include "Service.h"
#include <iostream>

int main() {
    Service service;

   
        service.read_requests("requests.txt");
        service.show_all_requests();

    return 0;
}
