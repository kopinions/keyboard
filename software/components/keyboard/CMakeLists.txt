add_library(kdb SHARED)
target_sources(kdb PRIVATE
        src/keyboard.cpp
        src/layout.cpp
        src/matrix.cpp
        src/config.cpp)
target_include_directories(kdb PUBLIC include)
target_compile_features(kdb PUBLIC cxx_std_17)
target_compile_options(kdb PUBLIC "$<$<NOT:$<CXX_COMPILER_ID:AppleClang>>:-mlongcalls>")
target_compile_options(kdb PUBLIC "$<$<CXX_COMPILER_ID:AppleClang>:-mlong-calls>")
target_compile_options(kdb PUBLIC "$<$<CONFIG:DEBUG>:-g3>")
target_compile_options(kdb PUBLIC "$<$<CONFIG:RELEASE>:-O2>")
target_link_libraries(kdb PUBLIC idf::esp_timer idf::log idf::driver idf::bt)
target_link_libraries(kdb PUBLIC kbd::esp_if kbd::vif)
add_library(kbd::kbd ALIAS kdb)