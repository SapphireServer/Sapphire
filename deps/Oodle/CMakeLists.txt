add_library(OodleNet STATIC IMPORTED GLOBAL)

set_target_properties(
	OodleNet
	PROPERTIES
	IMPORTED_IMPLIB "${CMAKE_SOURCE_DIR}/deps/Oodle/oo2net_9_win64.lib"
	IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/deps/Oodle/oo2net_9_win64.lib"
	LINKER_LANGUAGE C
)