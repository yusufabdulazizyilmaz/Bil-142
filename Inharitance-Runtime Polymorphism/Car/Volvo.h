//
// Created by yusufyilmaz on 30.12.2022.
//

#ifndef EXERCISE_VOLVO_H
#define EXERCISE_VOLVO_H

#include "Car.h"

class Volvo : public Car {

    void start_impl() override;

    void run_impl() override;

    void stop_impl() override;

};

#endif //EXERCISE_VOLVO_H
