cmake_minimum_required(VERSION 3.0.0)
project(Raytracer VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(Raytracer main.cpp vector3.h cor.h raio.h objetoAcertavel.h esfera.h objetosAcertaveis.h util.h camera.h)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
