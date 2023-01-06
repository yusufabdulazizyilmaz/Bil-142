//
// Created by yusufyilmaz on 30.12.2022.
//

#ifndef EXERCISE_CAR_H
#define EXERCISE_CAR_H

class Car {
public:
    Car();
    virtual ~Car() = default;  // destructor public virtual olmalı

    // Non-Virtual Interface
    void start();
    void run();
    void stop();

private:
    virtual void start_impl();

    virtual void run_impl();

    virtual void stop_impl();

    void maintain();



};

#endif //EXERCISE_CAR_H
