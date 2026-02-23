cmake_minimum_required(VERSION 3.10.0)
project(Uno VERSION 0.1.0 LANGUAGES C CXX)

add_executable(Uno
    src/main.cpp
    src/Juego/Juego.cpp
    src/Jugador/Jugador.cpp
    src/Carta/Carta.cpp
    src/Lado/Lado.cpp
    src/Lado/LadoNumero.cpp
    src/Lado/LadoMasDos.cpp
    src/Lado/LadoMasCuatro.cpp
    src/Lado/LadoSalto.cpp
    src/Lado/LadoReversa.cpp
    src/Lado/LadoComodin.cpp
    src/Lado/LadoRayosX.cpp
    src/Lado/LadoCambio.cpp
    src/Lado/Flip/LadoFlip.cpp
    src/Lado/Flip/LadoMasUnoFlip.cpp
    src/Lado/Flip/LadoMasDosFlip.cpp
    src/Lado/Flip/LadoMasTresFlip.cpp
    src/Lado/Flip/LadoMasSeisFlip.cpp
    src/Lado/Flip/LadoSaltaTodos.cpp
    src/Lado/Flip/LadoColorEterno.cpp
)

