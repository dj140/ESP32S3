set(srcs 
    "src/JPEGDEC.cpp"
    "src/jpeg.inl"
)
idf_component_register(SRCS ${srcs}      
                    INCLUDE_DIRS "src"
)
