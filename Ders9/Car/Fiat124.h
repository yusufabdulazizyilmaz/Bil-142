//
// Created by yusufyilmaz on 30.12.2022.
//

#ifndef EXERCISE_FIAT124_H
#define EXERCISE_FIAT124_H

#include "Fiat.h"

class Fiat124 final : public Fiat {

    void start_impl() override;

    void run_impl() override;

    void stop_impl() override;

};

#endif //EXERCISE_FIAT124_H
