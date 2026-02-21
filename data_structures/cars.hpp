#ifndef CARS_HPP
#define CARS_HPP

#include <iostream>

struct Cars {
    int model_id;
    Cars() : model_id(0) {}
    explicit Cars(int id) : model_id(id) {}
    friend std::ostream& operator<<(std::ostream& os, const Cars& car) {
        os << car.model_id;
        return os;
    }
};

#endif