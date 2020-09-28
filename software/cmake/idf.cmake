include(FetchContent)
FetchContent_Declare(
        idf
        GIT_REPOSITORY https://github.com/espressif/esp-idf.git
)
FetchContent_GetProperties(idf)
if (NOT idf_POPULATED)
    FetchContent_Populate(idf)
    add_subdirectory(${idf_SOURCE_DIR} ${idf_BINARY_DIR})
    include_directories(${idf_SOURCE_DIR}/include)
    include(${idf_BINARY_DIR}/tools/cmake/project.cmake)
endif ()