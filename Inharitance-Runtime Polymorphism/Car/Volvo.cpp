//
// Created by yusufyilmaz on 30.12.2022.
//

#include "Volvo.h"
#include <iostream>

void Volvo::start_impl()
{
    std::cout << "Volvo has just started\n";
}

void Volvo::run_impl()
{
    std::cout << "Volvo is running\n";
}

void Volvo::stop_impl()
{
    std::cout << "Volvo has stopped\n";
}