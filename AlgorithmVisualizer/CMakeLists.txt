cmake_minimum_required(VERSION 3.0.0)
project(AlgorithmVisualizer VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_DEBUG "-g")
set(CMAKE_CXX_RELEASE "-O3")
set(CMAKE_CXX_STANDARD 20)

# This will put our executable file outside the cmake's inital build directory
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

###################################################
################## [ LIBRARIES ] ##################
###################################################

# Finding sdl2 and opencv4
find_package(SDL2 REQUIRED)
find_package(OpenCV REQUIRED)

# Finding SFML 2
find_package(SFML 2 REQUIRED COMPONENTS network audio graphics window system)

# Finding opengl, glfw, glew, and glut
find_package(glfw3 3.4 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLUT REQUIRED)

find_package(Boost 1.40 REQUIRED regex date_time system filesystem thread graph)
include_directories(${BOOST_INCLUDE_DIRS})
message("boost lib: ${Boost_LIBRARIES}")
message("boost inc:${Boost_INCLUDE_DIR}")

if(__APPLE__)

    # This is making sure we find the SDL libraries on mac
    include_directories(${SDL2_INCLUDE_DIRS})

    # This is making sure that opencv on mac has been found!
    if(OpenCV_Found)
        # Additional Include Directories
        include_directories( ${OpenCV_INCLUDE_DIRS} )

        # Additional Library Directories
        link_directories( ${OpenCV_LIB_DIR} )

        # Additional Dependencies
        # target_link_libraries( ${PROJECT_NAME} ${OpenCV_LIBS} )
    else()
        message("Opencv is not found on mac!")
        message("
            Make sure you installed opencv correctly!
            - Check homebrew
            - Check if opencv is installed correctly with homebrew.
        ")
    endif()


    target_link_libraries(${PROJECT_NAME} pthread)
    # Linking the libraries for Cocoa, OpenGL, IOKit, and glfw
    # Need this for opengl
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    # target_link_libraries(${PROJECT_NAME} glfw ${OPENGL_gl_LIBRARY})
    # target_link_libraries(${PROJECT_NAME} GLEW::GLEW) # This helps us get rid of the "___glewGenBuffers" reference error

endif(__APPLE__)

# Getting gtest to work with cmake...
if(APPLE)
    include(FetchContent)
        FetchContent_Declare(
            googletest
            URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
        )

        FetchContent_MakeAvailable(googletest)
endif(APPLE)

if(WIN32)
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif()

add_subdirectory(dependencies/formatCpp)

# Adding tests for this specific project
add_test(AllTestsInCompatibleCppProject compatible_tests)

add_executable(
    ${PROJECT_NAME}
    main.cpp
)

#target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
#target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
#target_link_libraries(${PROJECT_NAME} sfml-system sfml-window sfml-graphics)
#target_link_libraries(${PROJECT_NAME} glfw ${OPENGL_gl_LIBRARY})
#target_link_libraries(${PROJECT_NAME} GLEW::GLEW) # This helps us get rid of the "___glewGenBuffers" reference error


target_link_libraries(${PROJECT_NAME}
    ${SDL2_LIBRARIES}
    ${OpenCV_LIBS}
    sfml-system sfml-window sfml-graphics
    glfw ${OPENGL_gl_LIBRARY}
    GLEW::GLEW
    FormatCpp::FormatCpp
)

if(APPLE)
    target_link_libraries(${PROJECT_NAME} GTest::gtest_main)
    target_link_libraries(${PROJECT_NAME} ${BOOST_LIBRARIES})
endif(APPLE)