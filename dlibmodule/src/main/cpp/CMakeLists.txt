cmake_minimum_required(VERSION 3.4.1)
add_library( # Sets the name of the library.
        mathutil
        # Sets the library as a shared library.
        SHARED
        # Provides a relative path to your source file(s).
        MathUtils.cpp
        )

add_library( # Sets the name of the library.
        objectdetection
        # Sets the library as a shared library.
        SHARED
        # Provides a relative path to your source file(s).
        ImageProcessing/ObjectDetection.cpp
        )
add_library( # Sets the name of the library.
        algorithms
        # Sets the library as a shared library.
        SHARED
        # Provides a relative path to your source file(s).
        algorithms.cpp
        )
add_library( # Sets the name of the library.
        native-lib
        # Sets the library as a shared library.
        SHARED
        # Provides a relative path to your source file(s).
        native-lib.cpp
        )

include(dlib/cmake)
find_library( # Sets the name of the path variable.
        log-lib
        # Specifies the name of the NDK library that
        # you want CMake to locate.
        log)

target_link_libraries( # Specifies the target library.
        native-lib
        mathutil
        dlib
        # Links the target library to the log library
        # included in the NDK.
        ${log-lib})

target_link_libraries( # Specifies the target library.
        algorithms
        mathutil
        dlib
        # Links the target library to the log library
        # included in the NDK.
        ${log-lib})
target_link_libraries( # Specifies the target library.
        objectdetection
        mathutil
        dlib
        # Links the target library to the log library
        # included in the NDK.
        ${log-lib})
