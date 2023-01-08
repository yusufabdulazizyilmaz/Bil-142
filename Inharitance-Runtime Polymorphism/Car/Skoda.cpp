//
// Created by yusufyilmaz on 30.12.2022.
//

#include "Skoda.h"
#include <iostream>

void Skoda::start_impl()
{
    std::cout << "Skoda has just started\n";
}

void Skoda::run_impl()
{
    std::cout << "Skoda is running\n";
}

void Skoda::stop_impl()
{
    std::cout << "Skoda has stopped\n";
}