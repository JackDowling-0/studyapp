cmake_minimum_required(VERSION 3.14)
project(studyapp)

file(GLOB SOURCES
    "src/*.cpp"
)

add_executable(${PROJECT_NAME} ${SOURCES})
 
