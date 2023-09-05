set(target freertos)

set(${target}_src
		${CMAKE_CURRENT_SOURCE_DIR}/kernel/croutine.c
		${CMAKE_CURRENT_SOURCE_DIR}/kernel/event_groups.c
		${CMAKE_CURRENT_SOURCE_DIR}/kernel/list.c
		${CMAKE_CURRENT_SOURCE_DIR}/kernel/queue.c
		${CMAKE_CURRENT_SOURCE_DIR}/kernel/tasks.c
		${CMAKE_CURRENT_SOURCE_DIR}/kernel/timers.c
		${CMAKE_CURRENT_SOURCE_DIR}/kernel/stream_buffer.c
		${CMAKE_CURRENT_SOURCE_DIR}/kernel/portable/MemMang/heap_4.c
		${CMAKE_CURRENT_SOURCE_DIR}/kernel/portable/GCC/ARM_CM4F/port.c)

add_library(${target} STATIC ${${target}_src})

target_include_directories(${target} PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/kernel/include
	${CMAKE_CURRENT_SOURCE_DIR}/kernel/portable/GCC/ARM_CM4F)

# target_compile_options(${target} PRIVATE -Wno-format -Wno-char-subscripts)
