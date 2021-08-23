add_library(link STATIC)
target_sources(link PRIVATE
        src/message.cpp
        src/link_control.cpp
        src/link.cpp)
target_include_directories(link PUBLIC include)
target_compile_features(link PUBLIC cxx_std_17)
target_compile_options(link PUBLIC "$<$<NOT:$<CXX_COMPILER_ID:AppleClang>>:-mlongcalls>")
target_compile_options(link PUBLIC "$<$<CXX_COMPILER_ID:AppleClang>:-mlong-calls>")
target_compile_options(link PUBLIC "$<$<CONFIG:DEBUG>:-g3>")
target_compile_options(link PUBLIC "$<$<CONFIG:RELEASE>:-O2>")
add_library(kbd::link ALIAS link)