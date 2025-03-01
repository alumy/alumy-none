set(target 3rd-party)

set(LWIP_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lwip-2.1.3)
set(LWIP_CONTRIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/contrib-2.1.0)
include(${CMAKE_CURRENT_SOURCE_DIR}/lwip.cmake)

FILE (GLOB_RECURSE ${target}_src
	${CMAKE_CURRENT_SOURCE_DIR}/letter-shell-3.1.2/src/*.c
	${CMAKE_CURRENT_SOURCE_DIR}/mbedtls-3.2.1/library/*.c
	${CMAKE_CURRENT_SOURCE_DIR}/freemodbus/modbus/ascii/*.c
	${CMAKE_CURRENT_SOURCE_DIR}/freemodbus/modbus/functions/*.c
	${CMAKE_CURRENT_SOURCE_DIR}/freemodbus/modbus/rtu/*.c
	${CMAKE_CURRENT_SOURCE_DIR}/freemodbus/modbus/*.c
	${CMAKE_CURRENT_SOURCE_DIR}/freemodbus/port/*.c
	${CMAKE_CURRENT_SOURCE_DIR}/qpn/src/qfn/qepn.c
	${CMAKE_CURRENT_SOURCE_DIR}/port/*.c
	${CMAKE_CURRENT_SOURCE_DIR}/paho.mqtt.embedded-c-1.1.0/MQTTPacket/src/*.c
	${CMAKE_CURRENT_SOURCE_DIR}/tiny-AES-c/aes.c
	${CMAKE_CURRENT_SOURCE_DIR}/littlefs-2.10.1/lfs_util.c
	${CMAKE_CURRENT_SOURCE_DIR}/littlefs-2.10.1/lfs.c)

add_library(${target} OBJECT ${${target}_src} ${lwipsrc} ${lwipcontribsrc})

target_compile_options(${target} PRIVATE
	-Wno-format -Wno-strict-aliasing -Wno-unused-const-variable -Wno-unused-function
	-Wno-unused-but-set-variable)

target_compile_definitions(${target} PRIVATE MQTT_CLIENT)

target_include_directories(${target}
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/letter-shell-3.1.2/src
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/mbedtls-3.2.1/library
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/mbedtls-3.2.1/include
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lwip-2.1.3/src/include
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/freemodbus/modbus/include
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/freemodbus/port
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/freemodbus/modbus/rtu
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/freemodbus/modbus/ascii
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/qpn/include
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/port/include
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/paho.mqtt.embedded-c-1.1.0/MQTTPacket/src
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/tiny-AES-c
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/littlefs-2.10.1)


