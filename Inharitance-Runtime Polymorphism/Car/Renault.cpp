//
// Created by yusufyilmaz on 30.12.2022.
//

#include "Renault.h"
#include <iostream>

void Renault::start_impl()
{
    std::cout << "Fiat has just started\n";
}

void Renault::run_impl()
{
    std::cout << "Fiat is running\n";
}

void Renault::stop_impl()
{
    std::cout << "Fiat has stopped\n";
}