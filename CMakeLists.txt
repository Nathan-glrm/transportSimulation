cmake_minimum_required(VERSION 3.23)
project(MainProject)

set(CMAKE_CXX_STANDARD 14)

add_executable(MainProject main.cpp)


set(SFML_ROOT "C:/dev/Transport/SFML-2.5.1")
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")

set (source "${CMAKE_SOURCE_DIR}/src/assets")
set (destination "${CMAKE_CURRENT_BINARY_DIR}/src/assets")
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