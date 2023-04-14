cmake_minimum_required(VERSION 3.0)
project(BlobOS VERSION 0.1.2 LANGUAGES C CXX ASM_NASM)

set(CMAKE_C_FLAGS "-O0 -ffreestanding -m32 -Wall -Wextra")
set(CMAKE_CXX_FLAGS "-O0 -ffreestanding -m32 -Wall -Wextra -std=c++17 -mno-sse")

# Set linker flags
set(LINKER_SCRIPT "${CMAKE_SOURCE_DIR}/Arch/x86_64/linker.ld")
set(CMAKE_EXE_LINKER_FLAGS "-nostdlib -z noexecstack -T ${LINKER_SCRIPT}")

# Add include directories
set(GLOBAL_INC_DIR ".")
include_directories(${GLOBAL_INC_DIR})

file(GLOB_RECURSE ARCH_SOURCES "Arch/x86_64/*.cpp" "Arch/x86_64/*.asm")
file(GLOB_RECURSE KERNEL_SOURCES "Kernel/*.cpp")
file(GLOB_RECURSE LIBK_SOURCES "Kernel/LibK/*.cpp" "Kernel/LibK/*.c")
file(GLOB_RECURSE ARCH_32BIT_SOURCES "Arch/x86_64/32bit*.asm")

# Remove 32-bit sources from ARCH_SOURCES
foreach(file IN LISTS ARCH_32BIT_SOURCES)
    get_filename_component(file_name ${file} NAME)
    list(REMOVE_ITEM ARCH_SOURCES "${CMAKE_SOURCE_DIR}/Arch/x86_64/${file_name}")
endforeach()

# Create a library from the 32-bit sources.
add_library(ARCH_32BIT_SOURCES_LIB STATIC ${ARCH_32BIT_SOURCES})
set_target_properties(ARCH_32BIT_SOURCES_LIB PROPERTIES COMPILE_FLAGS "-f elf32")

add_library(LIBK STATIC ${LIBK_SOURCES})

set(CMAKE_ASM_NASM_COMPILE_OBJECT "<CMAKE_ASM_NASM_COMPILER> <INCLUDES> <FLAGS> -o <OBJECT> <SOURCE>")

add_executable(BlobOS.bin ${ARCH_SOURCES} ${KERNEL_SOURCES})
target_link_libraries(BlobOS.bin ARCH_32BIT_SOURCES_LIB)
target_link_libraries(BlobOS.bin LIBK)
