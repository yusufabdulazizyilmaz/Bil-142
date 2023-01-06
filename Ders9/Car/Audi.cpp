//
// Created by yusufyilmaz on 30.12.2022.
//

#include "Audi.h"
#include <iostream>

void Audi::start_impl()
{
    std::cout << "Audi has just started\n";
}

void Audi::run_impl()
{
    std::cout << "Audi is running\n";
}

void Audi::stop_impl()
{
    std::cout << "Audi has stopped\n";
}