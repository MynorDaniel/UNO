cmake_minimum_required(VERSION 3.10.0)
project(Uno VERSION 0.1.0 LANGUAGES C CXX)

add_executable(Uno src/main.cpp src/Juego/Juego.cpp src/Jugador/Jugador.cpp src/Carta/Carta.cpp src/Lado/Lado.cpp
    src/Lado/LadoNumero.cpp)

