
set(THREADING_SOURCES
	src/buffers.cpp
)

set(THREADING_HEADERS
	include/nlib/threading/buffers.hpp
)

add_library(threading ${THREADING_SOURCES} ${THREADING_HEADERS})

target_include_directories(threading INTERFACE
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>  
    $<INSTALL_INTERFACE:include>
)

add_library(nlib::threading ALIAS threading)

install(TARGETS threading
	EXPORT nlibTargets
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
	RUNTIME DESTINATION bin
)