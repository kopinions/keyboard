add_library(stub_spi_flash INTERFACE)
target_include_directories(stub_spi_flash INTERFACE .)
add_library(idf::spi_flash ALIAS stub_spi_flash)
