add_library(stub_log INTERFACE)
target_include_directories(stub_log INTERFACE .)
add_library(idf::log ALIAS stub_log)
