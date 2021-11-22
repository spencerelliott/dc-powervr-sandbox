cmake_minimum_required(VERSION 3.0)
project(PVRTest)

set(GENROMFS "$ENV{KOS_BASE}/utils/genromfs/genromfs")
set(VQENC $ENV{KOS_BASE}/utils/vqenc/vqenc)
set(DCBUMPGEN $ENV{KOS_BASE}/utils/dcbumpgen/dcbumpgen)
set(BIN2O $ENV{KOS_BASE}/utils/bin2o/bin2o)
set(ROMDISK_IMG "${CMAKE_SOURCE_DIR}/romdisk/romdisk.img")
set(ROMDISK_O "${CMAKE_SOURCE_DIR}/romdisk/romdisk.o")
set(ROMDISK_DIR "${CMAKE_SOURCE_DIR}/romdisk")

message("\nPLATFORM_DREAMCAST: ${PLATFORM_DREAMCAST}")

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)

include_directories(src)

set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O3 --fast-math")

set(
    SOURCES
    src/main.cpp
    src/debug.cpp
    src/game/game.cpp
    src/platform/platform.cpp
    src/scene/scene.cpp
    src/components/light.cpp
    src/components/sprite.cpp
    src/components/actor.cpp
)

set(
    SCRATCH_SOURCES
    scratchpad/main.cpp
)

if(ENGINE_DEBUG)
    add_definitions(-DENGINE_DEBUG)
endif()

if(PLATFORM_DREAMCAST)
    if(EXISTS ${ROMDISK_DIR})
        message("Generating sprites and bumpmaps")
        add_custom_command(
            OUTPUT bricks.kmg
            COMMAND ${VQENC} -t -v -q -k bricks.png
            DEPENDS bricks.png
        )

        add_custom_command(
            OUTPUT bumpmap.raw
            COMMAND ${DCBUMPGEN} bumpmap.png bumpmap.raw
            DEPENDS bumpmap.png
        )

        message("Generating romdisk")
        add_custom_command(
            OUTPUT ${ROMDISK_IMG}
            COMMAND ${GENROMFS} -f ${ROMDISK_IMG} -d ${ROMDISK_DIR} -v
        )

        add_custom_command(
            OUTPUT ${ROMDISK_O}
            COMMAND ${BIN2O} romdisk.img romdisk romdisk.o
            DEPENDS ${ROMDISK_IMG}
            WORKING_DIRECTORY ${ROMDISK_DIR}
        )

        set(EXTRA_OBJS ${ROMDISK_O})
        include_directories(${ROMDISK_DIR})
    endif()

    add_definitions(-DDREAMCAST)
    set(SOURCES ${SOURCES} src/platform/platform_dc.cpp)
    set(SOURCES ${SOURCES} src/renderer/renderer_dc.cpp)

    link_libraries(GLdc)
    link_libraries(kmg)
    link_libraries(kosutils)
else()
    set(SOURCES ${SOURCES} src/platform/platform_pc.cpp)

    link_libraries(GL)
    link_libraries(GLU)

endif()

execute_process(
    COMMAND git describe --abbrev=4 --dirty --always --tags
    OUTPUT_VARIABLE BUILD_VERSION
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

#configure_file(GL/version.c.in ${CMAKE_CURRENT_BINARY_DIR}/version.c)
link_libraries(m)

if(PLATFORM_DREAMCAST)
    add_executable(PVRTest ${EXTRA_OBJS} ${SOURCES})
    add_executable(PVRTest_Scratch ${EXTRA_OBJS} ${SCRATCH_SOURCES})
    set_target_properties(PVRTest_Scratch PROPERTIES LINKER_LANGUAGE CXX) 
else()
    add_definitions(-g)
    if(WIN32)
        add_executable(PVRTest.exe ${EXTRA_OBJS} ${SOURCES})
    else()
        add_executable(PVRTest ${EXTRA_OBJS} ${SOURCES})
    endif()
endif()
