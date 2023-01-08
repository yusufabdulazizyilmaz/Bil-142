//
// Created by yusufyilmaz on 30.12.2022.
//

#include "Fiat.h"
#include <iostream>

void Fiat::start_impl()
{
    std::cout << "Fiat has just started\n";
}

void Fiat::run_impl()
{
    std::cout << "Fiat is running\n";
}

void Fiat::stop_impl()
{
    std::cout << "Fiat has stopped\n";
}