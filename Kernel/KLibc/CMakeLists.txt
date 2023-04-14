add_library(KLibc STATIC
    KLibc/stdio.cpp
    KLibc/stdlib.c
    KLibc/string.c
    KLibc/strlen.c
)

target_include_directories(Klibc
    PUBLIC
        ${CMAKE_SOURCE_DIR}/Kernel/KLibc/Include
        ${CMAKE_SOURCE_DIR}/Arch/Include
        ${CMAKE_SOURCE_DIR}/Kernel/Include)

target_compile_options(KLibc PRIVATE -ffreestanding)

target_link_libraries(BlobOS.bin PRIVATE KLibc)
