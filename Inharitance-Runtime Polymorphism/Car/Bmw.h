//
// Created by yusufyilmaz on 30.12.2022.
//

#ifndef EXERCISE_BMW_H
#define EXERCISE_BMW_H

#include "Car.h"

class Bmw : public Car {

    void start_impl() override;

    void run_impl() override;

    void stop_impl() override;

};

#endif //EXERCISE_BMW_H
