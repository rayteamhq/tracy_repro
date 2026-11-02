cmake_minimum_required(VERSION 4.2)
project(tracy_repro)

set(CMAKE_CXX_STANDARD 20)

add_compile_options(-fsanitize=address,undefined)
add_compile_options(-fno-omit-frame-pointer)
add_link_options(-fsanitize=address,undefined)

include(FetchContent)

function(load_thirdparty name repository tag)
    set(FETCHCONTENT_QUIET FALSE)
    FetchContent_Declare(
        ${name}
        GIT_REPOSITORY ${repository}
        GIT_TAG ${tag}
        GIT_SHALLOW 1
        GIT_PROGRESS TRUE
    )
    FetchContent_MakeAvailable(${name})
endfunction()

set(TRACY_ENABLE ON CACHE BOOL "" FORCE)

load_thirdparty(
    tracy
    https://github.com/wolfpld/tracy.git
    v0.14.1
)

add_executable(tracy_repro main.cpp)
target_link_libraries(tracy_repro PRIVATE TracyClient)
