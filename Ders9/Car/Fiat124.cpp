//
// Created by yusufyilmaz on 30.12.2022.
//

#include "Fiat124.h"
#include <iostream>

void Fiat124::start_impl()
{
    std::cout << "Fiat124 has just started\n";
}

void Fiat124::run_impl()
{
    std::cout << "Fiat124 is running\n";
}

void Fiat124::stop_impl()
{
    std::cout << "Fiat124 has stopped\n";
}