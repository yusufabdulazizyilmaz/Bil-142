//
// Created by yusufyilmaz on 30.12.2022.
//
#include <cstdlib>
#include <iostream>
#include "Car.h"
#include "Bmw.h"
#include "Mercedes.h"
#include "Audi.h"
#include "Fiat.h"
#include "Volvo.h"
#include "Fiat124.h"
#include "Renault.h"
#include "Skoda.h"

Car* create_random_car()
{
    switch (rand() % 8)
    {
    case 0: std::cout << "Bmw Case\n"; return new Bmw;
    case 1: std::cout << "Mercedes Case\n"; return new Mercedes;
    case 2: std::cout << "Audi Case\n"; return new Audi;
    case 3: std::cout << "Fiat Case\n"; return new Fiat;
    case 4: std::cout << "Volvo Case\n"; return new Volvo;
    case 5: std::cout << "Fiat124 Case\n"; return new Fiat124;
    case 6: std::cout << "Renault Case\n"; return new Renault;
    case 7: std::cout << "Skoda Case\n"; return new Skoda;
    }

    return nullptr;
}
void game(Car& car)
{
    car.start();
    car.run();
    car.stop();
    std::cout << "----------------------------------------\n";
}

int main()
{
    srand((unsigned int)time(nullptr));

    for (;;)
    {
        auto p = create_random_car();
        game(*p);
        getchar();
        delete p;
    }
    return 0;
}