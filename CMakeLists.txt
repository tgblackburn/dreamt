cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(dreamt)

find_package(Geant4 REQUIRED)
include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)

set(sources src/DetectorConstruction.cpp src/PrimaryGeneratorAction.cpp src/RunAction.cpp src/TrackingAction.cpp src/EventAction.cpp)
set(headers include/DetectorConstruction.hpp include/PrimaryGeneratorAction.hpp include/RunAction.hpp include/TrackingAction.hpp include/EventAction.hpp)

add_executable(dreamt main.cpp ${sources} ${headers})
target_link_libraries(dreamt ${Geant4_LIBRARIES})
