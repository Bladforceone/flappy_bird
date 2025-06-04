cmake_minimum_required(VERSION 3.16)
project(flappy_bird LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_executable(game WIN32 src/main.cpp src/model/body/body.cpp src/model/body/body.h src/model/body/pipe.cpp src/model/body/pipe.h src/model/body/bird.cpp src/model/body/bird.h src/state.h src/model/factory/factory.h src/controller.cpp src/controller.h src/model/model.cpp src/model/model.h src/view/view.h src/view/gl_view.cpp src/view/gl_view.h src/model/factory/simple_factory.cpp src/model/factory/simple_factory.h)
target_link_libraries(game PRIVATE sfml-system sfml-audio sfml-graphics)
target_compile_features(game PRIVATE cxx_std_17)

set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++ -static")
add_custom_command(
        TARGET game
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:game>
        VERBATIM)