//
// Created by yusufyilmaz on 30.12.2022.
//

#ifndef EXERCISE_SKODA_H
#define EXERCISE_SKODA_H

#include "Car.h"

class Skoda : public Car {

    void start_impl() override;

    void run_impl() override;

    void stop_impl() override;

};

#endif //EXERCISE_SKODA_H
