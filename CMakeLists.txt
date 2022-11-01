cmake_minimum_required(VERSION 3.23)
project(MainProject)

set(CMAKE_CXX_STANDARD 14)

add_executable(MainProject main.cpp src/Map/Map.cpp src/Map/Map.h src/Map/Intersection.cpp src/Map/Intersection.h src/Map/Path.cpp src/Map/Path.h src/Map/Node.cpp src/Map/Node.h src/Map/Place/Place.cpp src/Map/Place/Place.h src/Map/Place/Residence/Residence.cpp src/Map/Place/Residence/Residence.h src/Map/Place/Residence/House.cpp src/Map/Place/Residence/House.h src/Map/Place/WorkPlace/WorkPlace.cpp src/Map/Place/WorkPlace/WorkPlace.h src/Map/LineType/BezierCurve.cpp src/Map/LineType/BezierCurve.h src/Trajet/TrajetElement.cpp src/Trajet/TrajetElement.h src/Trajet/Trajet.cpp src/Trajet/Trajet.h src/Trajet/TrajetTransport.cpp src/Trajet/TrajetTransport.h src/Trajet/TrajetPersonnal.cpp src/Trajet/TrajetPersonnal.h src/Resident/Resident.cpp src/Resident/Resident.h src/Resident/Adult.cpp src/Resident/Adult.h src/Resident/YoungAdult.cpp src/Resident/YoungAdult.h src/Resident/Child.cpp src/Resident/Child.h src/Resident/Senior.cpp src/Resident/Senior.h src/Map/LineType/Line.cpp src/Map/LineType/Line.h src/View/MapView.cpp src/View/MapView.h)


set(SFML_ROOT "C:/dev/Transport/SFML-2.5.1")
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")

set (source "${CMAKE_SOURCE_DIR}/assets")
set (destination "${CMAKE_CURRENT_BINARY_DIR}/assets")
add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E create_symlink ${source} ${destination}
        DEPENDS ${destination}
        COMMENT "symbolic link resources folder from ${source} => ${destination}"
)


add_custom_command(TARGET ${CMAKE_PROJECT_NAME} PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E create_symlink
        ${CMAKE_SOURCE_DIR}/config $<TARGET_FILE_DIR:${PROJECT_NAME}>/config)

FIND_PACKAGE(SFML 2 REQUIRED graphics network audio window system)
if(SFML_FOUND)
    message(STATUS "It works!")
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()