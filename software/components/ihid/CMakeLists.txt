idf_component_register(
        SRCS "hid.cpp" "hid_device_le_prf.cpp"
        INCLUDE_DIRS "include"
        REQUIRES vif esp_if keyboard bt)