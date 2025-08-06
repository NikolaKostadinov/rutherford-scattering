cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

project(Rutherford)

find_package(Geant4 REQUIRED ui_all vis_all)
find_package(ROOT   REQUIRED)

include(${Geant4_USE_FILE})
include(${ROOT_USE_FILE})

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)
file(GLOB main    ${PROJECT_SOURCE_DIR}/main.cc)

add_executable(rutherford-scattering ${main} ${sources} ${headers})
target_include_directories(rutherford-scattering PRIVATE ${ROOT_LIBRARIES})
target_link_libraries(rutherford-scattering ${Geant4_LIBRARIES} ${ROOT_LIBRARIES})

file(COPY ${MACRO_FILES} DESTINATION ${PROJECT_BINARY_DIR})

add_custom_target(Rutherford DEPENDS rutherford-scattering)
