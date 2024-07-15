# Hal
file(GLOB_RECURSE HAL_SRCS
    HAL/*.c
    HAL/*.cpp
)
set(HAL_INCS
    hal/
)

file(GLOB_RECURSE APP_SRCS
    APP/*.c
    APP/*.cpp
)
set(APP_INCS
    APP/
)

file(GLOB_RECURSE LVGL_PORT_SRCS
    lvgl_port/*.c
    lvgl_port/*.cpp
)
set(LVGL_PORT_INCS
    lvgl_port/
)

idf_component_register(SRCS "main.cpp""i2c_port.c" ${HAL_SRCS} ${APP_SRCS} ${LVGL_PORT_SRCS}
                    INCLUDE_DIRS "." ${HAL_INCS} ${APP_INCS} ${LVGL_PORT_INCS})
                    
component_compile_options(-Wno-error=format= -Wno-format)