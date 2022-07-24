cmake_minimum_required(VERSION 3.22)
project(philo C)

set(CMAKE_C_STANDARD 99)

add_executable(philo
        main.c
        ft_atoi.c
        pthread.c
        utils.c
        utils1.c
        utils2.c

        inc/philo.h
        )
target_link_libraries(philo
        pthread
        )