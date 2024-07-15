# Source files directories
set(esp_lcd_sh8601_SRC_DIRS
    src/
)
# Head files directories
set(esp_lcd_sh8601_INC_DIRS
    src/
)

idf_component_register(SRC_DIRS ${esp_lcd_sh8601_SRC_DIRS} INCLUDE_DIRS ${esp_lcd_sh8601_INC_DIRS} PRIV_REQUIRES "driver" REQUIRES "esp_lcd")


