//
// Created by yusufyilmaz on 30.12.2022.
//

#include "Bmw.h"
#include <iostream>

void Bmw::start_impl()
{
    std::cout << "BMW has just started\n";
}

void Bmw::run_impl()
{
    std::cout << "BMW is running\n";
}

void Bmw::stop_impl()
{
    std::cout << "BMW has stopped\n";
}