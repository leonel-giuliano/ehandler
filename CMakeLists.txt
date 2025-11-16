cmake_minimum_required(VERSION 3.15)
project(eh C)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)  # for .a
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)  # for .so

include_directories(${CMAKE_SOURCE_DIR}/include)
file(GLOB SOURCES "src/*.c")

# Static library - default prefix "lib", so output will be lib${PROJECT_NAME}.a
add_library(${PROJECT_NAME}_static STATIC ${SOURCES})
target_compile_definitions(${PROJECT_NAME} PRIVATE USE_OPEMSG)
set_target_properties(${PROJECT_NAME}_static PROPERTIES
    OUTPUT_NAME "${PROJECT_NAME}"
    POSITION_INDEPENDENT_CODE ON
)

# Shared library - let CMake add prefix "lib" and suffix ".so"
# Versioning properly set to avoid extra suffixes
add_library(${PROJECT_NAME}_shared SHARED ${SOURCES})
target_compile_definitions(${PROJECT_NAME} PRIVATE USE_OPEMSG)
set_target_properties(${PROJECT_NAME}_shared PROPERTIES
    OUTPUT_NAME "${PROJECT_NAME}"
    VERSION 1.0.0
    SOVERSION 1
    POSITION_INDEPENDENT_CODE ON
)

# install libraries
install(TARGETS ${PROJECT_NAME}_static ${PROJECT_NAME}_shared
        ARCHIVE DESTINATION lib        # static .a
        LIBRARY DESTINATION lib        # shared .so (handles versioning & symlinks)
)

# install headers
install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/
        DESTINATION include/${PROJECT_NAME}
        FILES_MATCHING PATTERN "*.h"
)

# Symlink commands to get exact names in lib/
add_custom_command(TARGET ${PROJECT_NAME}_shared POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E chdir ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
        ${CMAKE_COMMAND} -E remove -f lib${PROJECT_NAME}.so
    COMMAND ${CMAKE_COMMAND} -E chdir ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
        ${CMAKE_COMMAND} -E remove -f lib${PROJECT_NAME}.so.1
    COMMAND ${CMAKE_COMMAND} -E chdir ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
        ${CMAKE_COMMAND} -E create_symlink lib${PROJECT_NAME}.so.1.0.0 lib${PROJECT_NAME}.so.1
    COMMAND ${CMAKE_COMMAND} -E chdir ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
        ${CMAKE_COMMAND} -E create_symlink lib${PROJECT_NAME}.so.1 lib${PROJECT_NAME}.so
    COMMENT "Fixing symbolic links for shared library"
)
