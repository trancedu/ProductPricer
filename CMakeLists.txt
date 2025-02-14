cmake_minimum_required(VERSION 3.10)
project(financial_pricing)

set(CMAKE_CXX_STANDARD 20)

add_executable(financial_pricing
    main.cpp
    data.cpp
    pricers.cpp
    visitor.cpp
    models.cpp
    model_factory.cpp
) 