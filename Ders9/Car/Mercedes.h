//
// Created by yusufyilmaz on 30.12.2022.
//

#ifndef EXERCISE_MERCEDES_H
#define EXERCISE_MERCEDES_H

#include "Car.h"

class Mercedes : public Car {

    void start_impl() override;

    void run_impl() override;

    void stop_impl() override;

};

#endif //EXERCISE_MERCEDES_H
