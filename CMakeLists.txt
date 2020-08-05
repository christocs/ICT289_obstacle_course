cmake_minimum_required(VERSION 3.16)
set(PROJECT_NAME ICT289)
project(${PROJECT_NAME} LANGUAGES CXX)

add_executable(ICT289)

set_target_properties(ICT289 PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
)

add_subdirectory(src)
add_subdirectory(lib)

target_link_libraries(${PROJECT_NAME} PRIVATE
        freeglut
        ${OPENGL_gl_LIBRARY}
        ${OPENGL_glu_LIBRARY}
)
#libglu1-mesa-dev