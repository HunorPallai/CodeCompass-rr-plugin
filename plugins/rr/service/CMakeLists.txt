include_directories(
	include
	${CMAKE_CURRENT_BINARY_DIR}/gen-cpp
	${PROJECT_SOURCE_DIR}/util/include
	${PROJECT_SOURCE_DIR}/webserver/include
	${PLUGIN_DIR}/model/include
	${PROJECT_BINARY_DIR}/service/project/gen-cpp
	${PROJECT_SOURCE_DIR}/service/project/include
	${PLUGIN_DIR}/model/include)

include_directories(
	${THRIFT_LIBTHRIFT_INCLUDE_DIRS})

add_custom_command(
	OUTPUT
		${CMAKE_CURRENT_BINARY_DIR}/gen-cpp/rr_constants.h
		${CMAKE_CURRENT_BINARY_DIR}/gen-cpp/rr_constants.cpp
		${CMAKE_CURRENT_BINARY_DIR}/gen-cpp/rr_types.h
		${CMAKE_CURRENT_BINARY_DIR}/gen-cpp/rr_types.cpp
		${CMAKE_CURRENT_BINARY_DIR}/gen-cpp/RRService.h
		${CMAKE_CURRENT_BINARY_DIR}/gen-cpp/RRService.cpp
		${CMAKE_CURRENT_BINARY_DIR}/gen-cpp
		${CMAKE_CURRENT_BINARY_DIR}/gen-js
	COMMAND
		${THRIFT_EXECUTABLE} --gen cpp --gen js
			-o ${CMAKE_CURRENT_BINARY_DIR}
			${CMAKE_CURRENT_SOURCE_DIR}/rr.thrift
	DEPENDS
		${CMAKE_CURRENT_SOURCE_DIR}/rr.thrift
	COMMENT
		"Generating Thrift for rr.thrift")

add_library(rrthrift STATIC
	#${CMAKE_CURRENT_BINARY_DIR}/gen-cpp/rr_constants.cpp
	#${CMAKE_CURRENT_BINARY_DIR}/gen-cpp/rr_types.cpp
	${CMAKE_CURRENT_BINARY_DIR}/gen-cpp/RRService.cpp)

target_compile_options(rrthrift PUBLIC -fPIC)

add_library(rrservice SHARED
	src/plugin.cpp
	src/rrservice.cpp)

target_compile_options(rrservice PUBLIC -Wno-unknown-pragmas)

target_link_libraries(rrservice
	util
	${THRIFT_LIBTHRIFT_LIBRARIES}
	${ODB_LIBRARIES}
	rrthrift)

install(TARGETS rrservice DESTINATION ${INSTALL_SERVICE_DIR})
install_js_thrift()
