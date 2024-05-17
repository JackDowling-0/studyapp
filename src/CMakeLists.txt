include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/raylib/include
)

add_executable(
    ${PROJECT_NAME} 
    flashcardmanager.cpp 
    main.cpp 
    menus.cpp 
    parser.cpp
)

target_compile_options(
    ${PROJECT_NAME} 
    PRIVATE
    -O2
    -Wall
    -Wextra
)

target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/raylib/lib/libraylib.a)