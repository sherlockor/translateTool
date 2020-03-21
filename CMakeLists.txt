project(Translate)
cmake_minimum_required(VERSION 2.8)
aux_source_directory(. SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})
#add_library(${PROJECT_NAME} google_translate.cpp base_translate.cpp youdao_translate.cpp translate_factory.cpp)
#set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/out/)
#set_target_properties(${PROJECT_NAME} PROPERTIES VERSION 1.1 SOVERSION 1)

add_definitions(-std=c++11)

file(GLOB_RECURSE LibFiles "*.h")
add_custom_target(headers SOURCES ${LibFiles})

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME}
                        ${PROJECT_SOURCE_DIR}/libs/libcurl.a
                        ${PROJECT_SOURCE_DIR}/libs/libcurl.dll.a
                        ${PROJECT_SOURCE_DIR}/libs/libjsoncpp.a
)
set(CMAKE_BUILD_TYPE DEBUG)
