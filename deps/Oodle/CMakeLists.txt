add_library(OodleNet STATIC IMPORTED GLOBAL)

set_target_properties(
	OodleNet
	PROPERTIES
	IMPORTED_IMPLIB "${CMAKE_SOURCE_DIR}/deps/Oodle/liboo2netlinux64.a"
	IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/deps/Oodle/liboo2netlinux64.a"
	LINKER_LANGUAGE C
)