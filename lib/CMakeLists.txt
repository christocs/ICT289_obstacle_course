add_subdirectory(freeglut/freeglut/freeglut)
option(FREEGLUT_BUILD_DEMOS OFF)
option(FREEGLUT_BUILD_STATIC_LIBS ON)
option(FREEGLUT_REPLACE_GLUT ON)

TARGET_INCLUDE_DIRECTORIES(freeglut
    PRIVATE
    "${CMAKE_BINARY_DIR}"
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/freeglut/freeglut/freeglut/src>
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/freeglut/freeglut/freeglut/include>
    $<INSTALL_INTERFACE:include>
)

