add_library(stub_freertos STATIC task.c)
target_include_directories(stub_freertos PUBLIC .)
add_library(idf::freertos ALIAS stub_freertos)
target_compile_features(stub_freertos PUBLIC cxx_std_17)