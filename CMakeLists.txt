cmake_minimum_required(VERSION 3.16)
project(MyResearch1 LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(SFML_LIBRARIES sfml-system sfml-window sfml-graphics sfml-audio sfml-network)

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)

FetchContent_MakeAvailable(SFML)

file(GLOB_RECURSE HEADERS "include/*.hpp")
file(GLOB SOURCES "src/*.cpp")

add_executable(MyResearch1 ${HEADERS} ${SOURCES})

target_include_directories(MyResearch1 PRIVATE include)
target_link_libraries(MyResearch1 PRIVATE ${SFML_LIBRARIES})
target_compile_features(MyResearch1 PRIVATE cxx_std_20)

if(MSVC)
    target_compile_options(MyResearch1 PRIVATE /W4 /WX)
else()
    target_compile_options(MyResearch1 PRIVATE -Wall -Wpedantic -Werror)
endif()

if(WIN32)
    add_custom_command(
        TARGET MyResearch1
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:MyResearch1>
        VERBATIM)
endif()

install(TARGETS MyResearch1)