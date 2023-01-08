//
// Created by yusufyilmaz on 30.12.2022.
//

#ifndef EXERCISE_AUDI_H
#define EXERCISE_AUDI_H

#include "Car.h"

class Audi : public Car {

    void start_impl() override;

    void run_impl() override;

    void stop_impl() override;

};

#endif //EXERCISE_AUDI_H
