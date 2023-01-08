//
// Created by yusufyilmaz on 30.12.2022.
//

#include "Mercedes.h"
#include <iostream>

void Mercedes::start_impl()
{
    std::cout << "Mercedes has just started\n";
}

void Mercedes::run_impl()
{
    std::cout << "Mercedes is running\n";
}

void Mercedes::stop_impl()
{
    std::cout << "Mercedes has stopped\n";
}