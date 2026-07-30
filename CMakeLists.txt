cmake_minimum_required(VERSION 3.5)

project(ubctl_so VERSION ${PROJECT_VERSION} LANGUAGES C CXX)

include_directories(./)
include_directories(./common)
include_directories(./feature)
include_directories(./protocol_layer)
file(GLOB UTOOL_SRC
    ./*.c
    ./common/*.c
    ./feature/*.c
    ./protocol_layer/*.c)

set(UTOOL_SRC_LIB ${UTOOL_SRC})
list(REMOVE_ITEM UTOOL_SRC_LIB
    ${CMAKE_CURRENT_SOURCE_DIR}/u_utool_main.c
)

add_library(ubctl_so SHARED ${UTOOL_SRC_LIB})

target_link_directories(ubctl_so PRIVATE ${CMAKE_INSTALL_PREFIX}/lib)

set_target_properties(ubctl_so PROPERTIES
    SOVERSION ${LIB_SOVERSION}
    VERSION ${PROJECT_VERSION}
    POSITION_INDEPENDENT_CODE ON
    OUTPUT_NAME "ubctl"
)

install(TARGETS ubctl_so LIBRARY DESTINATION lib64 OPTIONAL)

add_executable(ubctl ${UTOOL_SRC})

target_link_directories(ubctl PRIVATE ${CMAKE_INSTALL_PREFIX}/lib)

target_link_libraries(ubctl PRIVATE rt)


set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wuninitialized -Wno-error=format -Wundef -Wunused -Wdate-time -Wfloat-equal -Wshadow -Wvla \
    -Wdisabled-optimization -Wempty-body -Wignored-qualifiers -Wimplicit-fallthrough=3 -Wtype-limits -Wshift-negative-value -Wswitch-default \
    -Wframe-larger-than=8192 -Wshift-overflow=2 -Wwrite-strings -Wmissing-format-attribute -Wformat-nonliteral -Wduplicated-cond -Wtrampolines \
    -Wlogical-op -Wsuggest-attribute=format -Wduplicated-branches -Wmissing-include-dirs -Wformat-signedness -Wmissing-declarations \
    -Wreturn-local-addr -Wredundant-decls -Wfloat-conversion -Wmissing-prototypes -Wstrict-prototypes")

install(TARGETS ubctl RUNTIME DESTINATION bin OPTIONAL)
install(FILES include/u_utool_user_api.h DESTINATION include/)
