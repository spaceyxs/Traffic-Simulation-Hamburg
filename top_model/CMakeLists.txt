
add_executable(${PROJECT_NAME} main.cpp)


target_include_directories(${PROJECT_NAME} PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/../include"
    "${CMAKE_CURRENT_SOURCE_DIR}/../atomics"
    "${CMAKE_CURRENT_SOURCE_DIR}/../data_structures"
    "/home/spacey/cadmium_v2/include"   # Path to Cadmium headers
)

target_compile_options(${PROJECT_NAME} PRIVATE -std=gnu++2b)
