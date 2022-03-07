cmake_minimum_required(VERSION 3.15...3.21)
project(Acceptance_calc_v4)

set(CMAKE_CXX_FLAGS "-Ofast -w -mtune=native -march=native -fcolor-diagnostics")

list(APPEND CMAKE_PREFIX_PATH  $ENV{ROOTSYS})
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} $ENV{ROOTSYS}/etc/cmake)

find_package(ROOT REQUIRED COMPONENTS XMLIO XMLParser)
include(${ROOT_USE_FILE})

include_directories(${ROOT_INCLUDE_DIRS})

option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

add_library(Acceptance_lib SHARED ${sources} ${headers})
target_link_libraries(Acceptance_lib ${ROOT_LIBRARIES} ${Geant4_LIBRARIES})
add_executable(Acceptance_calculation Main.cc)
target_link_libraries(Acceptance_calculation Acceptance_lib)
#target_compile_options(Acceptance_calculation PUBLIC -Ofast -w -mtune=native -march=native)


set(ACCCALC_SCRIPTS
  #nohup.out
  test_run.mac
  run.mac
  run4ep.mac
  vis.mac
  )

foreach(_script ${ACCCALC_SCRIPTS})
  configure_file(
    ${PROJECT_SOURCE_DIR}/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY
    )
endforeach()

add_custom_target(Acceptance_calc_v4 DEPENDS Acceptance_calculation)
install(TARGETS Acceptance_calculation DESTINATION bin)
