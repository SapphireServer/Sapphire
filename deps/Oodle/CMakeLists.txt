add_library(OodleNet STATIC IMPORTED GLOBAL)

if(WIN32)
	set_target_properties(
		OodleNet
		PROPERTIES
		IMPORTED_IMPLIB "${CMAKE_SOURCE_DIR}/deps/Oodle/oo2net_9_win64.lib"
		IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/deps/Oodle/oo2net_9_win64.lib"
		LINKER_LANGUAGE C
	)
elseif(UNIX)
	set_target_properties(
		OodleNet
		PROPERTIES
		IMPORTED_IMPLIB "${CMAKE_SOURCE_DIR}/deps/Oodle/liboo2netlinux64.a"
		IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/deps/Oodle/liboo2netlinux64.a"
		LINKER_LANGUAGE C
	)
endif()