//
// Created by yusufyilmaz on 30.12.2022.
//

#include "Car.h"
#include <iostream>

Car::Car()
{
    std::cout << "Car Constructor\n";
    run_impl();
}

void Car::start()
{
    start_impl();
}
void Car::run()
{
run_impl();
}

void Car::stop()
{
start_impl();
}

void Car::start_impl()
{
    std::cout << "Car has just started\n";
}

void Car::run_impl()
{
    std::cout << "Car is running\n";
}

void Car::stop_impl()
{
    std::cout << "Car has stopped\n";
}

void Car::maintain()
{
    std::cout << "Araba bakima girdi calistiriliyor\n";
    start_impl();
}





