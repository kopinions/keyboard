add_library(stub_freertos STATIC)
target_sources(stub_freertos PRIVATE src/task.c)
target_include_directories(stub_freertos PUBLIC include)
add_library(idf::freertos ALIAS stub_freertos)
target_compile_features(stub_freertos PUBLIC cxx_std_17)