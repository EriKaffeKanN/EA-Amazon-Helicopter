cmake_minimum_required (VERSION 3.10.2)

set (CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

project (EA_Amazon_Helicopter)
file (GLOB_RECURSE SOURCES src/*.cpp)

if (WIN32)
	set(SFML_STATIC_LIBRARIES TRUE)
        set (SFML_DIR ${USER_SFML_BASE_PATH}/lib/cmake/SFML)
	find_package (SFML 2.5 COMPONENTS graphics window system REQUIRED)

        # Static libc++
        set (CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++ -static")
endif ()

add_executable (ea_ah ${SOURCES})

# Might add sfml audio later
target_link_libraries (ea_ah sfml-graphics sfml-window sfml-system)