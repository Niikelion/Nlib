cmake_minimum_required(VERSION 3.9.2)
project(Nlib VERSION 1.0.0 DESCRIPTION "Utility library")

add_subdirectory(threading)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
	nlibConfigVersion.cmake
	VERSION ${PACKAGE_VERSION}
	COMPATIBILITY AnyNewerVersion
)
	
install(EXPORT nlibTargets
	FILE nlibTargets.cmake
	NAMESPACE nlib::
	DESTINATION lib/cmake/nlib
)

configure_file(nlibConfig.cmake.in nlibConfig.cmake @ONLY)
install(FILES 	"${CMAKE_CURRENT_BINARY_DIR}/nlibConfig.cmake"
				"${CMAKE_CURRENT_BINARY_DIR}/nlibConfigVersion.cmake"
	DESTINATION lib/cmake/nlib
)

export(TARGETS threading NAMESPACE nlib:: FILE nlibTargets.cmake)