//
// Created by yusufyilmaz on 30.12.2022.
//

#ifndef EXERCISE_FIAT_H
#define EXERCISE_FIAT_H

#include "Car.h"

class Fiat : public Car {

    void start_impl() override;

    void run_impl() override;

    void stop_impl() override;

};

#endif //EXERCISE_FIAT_H
