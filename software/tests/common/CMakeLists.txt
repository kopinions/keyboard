add_library(testing INTERFACE)
target_include_directories(testing INTERFACE include)
target_compile_features(testing INTERFACE cxx_std_17)
