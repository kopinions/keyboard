add_library(vif INTERFACE IMPORTED GLOBAL)
target_include_directories(vif INTERFACE include)
add_library(kbd::vif ALIAS vif)