cmake_minimum_required(VERSION 2.8)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set(CMAKE_C_COMPILER "arm-none-eabi-gcc" CACHE STRING "" FORCE)
set(CMAKE_CXX_COMPILER "arm-none-eabi-g++" CACHE STRING "" FORCE)
set(CMAKE_AR "arm-none-eabi-ar" CACHE STRING "" FORCE)
set(CMAKE_OBJCOPY "arm-none-eabi-objcopy" CACHE STRING "" FORCE)
set(CMAKE_SIZE "arm-none-eabi-size" CACHE STRING "" FORCE)
set(CMAKE_DEBUGGER "arm-none-eabi-gdb" CACHE STRING "" FORCE)

set(CMAKE_FIND_ROOT_PATH "...")
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

set(CMAKE_C_COMPILER_WORKS 1)
set(CMAKE_CXX_COMPILER_WORKS 1)
set(CMAKE_ASM_COMPILER_WORKS 1)

set(CMAKE_C_FLAGS "-std=gnu99" CACHE STRING "" FORCE)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${MCU}" CACHE STRING "" FORCE)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ffunction-sections -fdata-sections" CACHE STRING "" FORCE)
set(CMAKE_C_FLAGS_DEBUG "-g -gdwarf-2" CACHE STRING "" FORCE)
set(CMAKE_C_FLAGS_MINSIZEREL "-Os -DNDEBUG" CACHE STRING "" FORCE)
set(CMAKE_C_FLAGS_RELEASE "-O2 -DNDEBUG" CACHE STRING "" FORCE)
set(CMAKE_C_FLAGS_RELWITHDEBINFO "-O2 -g -gdwarf-2" CACHE STRING "" FORCE)

set(CMAKE_CXX_FLAGS "" CACHE STRING "" FORCE)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${MCU}" CACHE STRING "" FORCE)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ffunction-sections -fdata-sections" CACHE STRING "" FORCE)
set(CMAKE_CXX_FLAGS_DEBUG "-g -gdwarf-2" CACHE STRING "" FORCE)
set(CMAKE_CXX_FLAGS_MINSIZEREL "-Os -DNDEBUG" CACHE STRING "" FORCE)
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG" CACHE STRING "" FORCE)
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g -gdwarf-2" CACHE STRING "" FORCE)

set(CMAKE_ASM_FLAGS "-Wall -fdata-sections -ffunction-sections" CACHE STRING "" FORCE)

set(CMAKE_EXE_LINKER_FLAGS "${MCU} -specs=nano.specs -specs=nosys.specs -T${LINKER_SCRIPT}" CACHE STRING "" FORCE)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Map=${PROJECT_BINARY_DIR}/${PROJECT_NAME}.map,--cref" CACHE STRING "" FORCE)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--gc-sections -Wl,-print-memory-usage" CACHE STRING "" FORCE)

# Let empty for root directory /
set(CMAKE_INSTALL_PREFIX "${PROJECT_SOURCE_DIR}/release" CACHE STRING "" FORCE)

link_libraries(m c nosys)

function(debug)
add_custom_target(debug
		COMMAND ${CMAKE_DEBUGGER} ${CMAKE_BINARY_DIR}/${PROJECT_NAME}
		DEPENDS ${PROJECT_NAME})
endfunction(debug)

function(gdbserver device)
add_custom_target(gdbserver
		COMMAND JLinkGDBServerCLExe -JLinkDevicesXMLPath ${PROJECT_SOURCE_DIR}/cmake/toolchain/hc32/jlink/ -device ${device} -if swd -speed auto -ir -vd)
endfunction(gdbserver)