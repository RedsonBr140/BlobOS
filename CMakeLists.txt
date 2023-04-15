cmake_minimum_required(VERSION 3.0)
project(BlobOS VERSION 0.1.2 LANGUAGES C CXX ASM_NASM)

set(CMAKE_C_FLAGS "-O0 -ffreestanding -Wall -Wextra -g")
set(CMAKE_CXX_FLAGS "-O0 -ffreestanding -Wall -Wextra -std=c++17 -mno-sse -g")
set(CMAKE_ASM_NASM_FLAGS "-f elf64")
set(CMAKE_POSITION_INDEPENDENT_CODE FALSE)

# Set linker flags
set(LINKER_SCRIPT "${CMAKE_SOURCE_DIR}/Arch/x86_64/linker.ld")
set(CMAKE_EXE_LINKER_FLAGS "-nostdlib -T ${LINKER_SCRIPT} -no-pie -z noexecstack")

# Add include directories
set(GLOBAL_INC_DIR ".")
include_directories(${GLOBAL_INC_DIR})

file(GLOB_RECURSE ARCH_SOURCES "Arch/x86_64/*.cpp" "Arch/x86_64/*.asm")
file(GLOB_RECURSE KERNEL_SOURCES "Kernel/*.cpp")
file(GLOB_RECURSE LIBK_SOURCES "Kernel/LibK/*.cpp" "Kernel/LibK/*.c")

add_library(LIBK STATIC ${LIBK_SOURCES})

add_executable(BlobOS.bin ${ARCH_SOURCES} ${KERNEL_SOURCES})
set_property(TARGET BlobOS.bin PROPERTY POSITION_INDEPENDENT_CODE FALSE)
target_link_libraries(BlobOS.bin LIBK)
