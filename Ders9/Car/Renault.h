//
// Created by yusufyilmaz on 30.12.2022.
//

#ifndef EXERCISE_RENAULT_H
#define EXERCISE_RENAULT_H

#include "Car.h"

class Renault : public Car {

    void start_impl() override;

    void run_impl() override;

    void stop_impl() override;

};

#endif //EXERCISE_RENAULT_H
