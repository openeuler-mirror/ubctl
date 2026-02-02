cmake_minimum_required(VERSION 3.5)
set(UB_TOOL_VERSION 0.1.0)

project(ubctl VERSION ${UB_TOOL_VERSION} LANGUAGES C CXX)

include_directories(./)
file(GLOB UTOOL_SRC
    ./*.c)

add_executable(ubctl ${UTOOL_SRC})

target_link_directories(ubctl PRIVATE ${CMAKE_INSTALL_PREFIX}/lib)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wuninitialized -Wno-error=format -Wundef -Wunused -Wdate-time -Wfloat-equal -Wshadow -Wvla \
    -Wdisabled-optimization -Wempty-body -Wignored-qualifiers -Wimplicit-fallthrough=3 -Wtype-limits -Wshift-negative-value -Wswitch-default \
    -Wframe-larger-than=8192 -Wshift-overflow=2 -Wwrite-strings -Wmissing-format-attribute -Wformat-nonliteral -Wduplicated-cond -Wtrampolines \
    -Wlogical-op -Wsuggest-attribute=format -Wduplicated-branches -Wmissing-include-dirs -Wformat-signedness -Wmissing-declarations \
    -Wreturn-local-addr -Wredundant-decls -Wfloat-conversion -Wmissing-prototypes -Wstrict-prototypes")

install(TARGETS ubctl RUNTIME DESTINATION bin OPTIONAL)
