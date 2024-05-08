cmake_minimum_required(VERSION 3.29.2)
project(studyapp)

file(GLOB SOURCES
    "src/*.cpp"
)

add_executable(${PROJECT_NAME} ${SOURCES})
 
