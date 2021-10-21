IF(NOT ASL_FOUND)
	IF(${ASL_FIND_REQUIRED})
		FIND_PACKAGE(NLC REQUIRED)
	ELSE()
		FIND_PACKAGE(NLC)
	ENDIF()

	SET(ASL_INCLUDE)
	SET(ASL_LIBRARIES)
	SET(ASL_FFTW_LIBRARIES)

	IF(${NLC_FOUND})
		# Determine if we need OpenMP ------------------------------------------
		IF(${OpenMP_FOUND})
			SET(ASL_OPENMP "_openmp")
			SET(ASL_OPENMP_MSG "OpenMP")
		ELSE()
			SET(ASL_OPENMP "_sequential")
			SET(ASL_OPENMP_MSG "Sequential")
		ENDIF()

		# Determine library type -----------------------------------------------
		IF(${ASL_STATIC})
			SET(ASL_LIB "a")
			SET(ASL_LIB_MSG "Static")
		ELSE()
			SET(ASL_LIB "so")
			SET(ASL_LIB_MSG "Shared")
		ENDIF()

		IF(ASL_LIB_INT64)
			SET(ASL_INT "_i64")
			SET(ASL_INT_MSG "INT64")
		ELSE()
			SET(ASL_INT "")
			SET(ASL_INT_MSG "INT32")
		ENDIF()

		LIST(APPEND ASL_LIBRARIES "${NLC_PATH}/lib/libasl${ASL_OPENMP}${ASL_INT}.${ASL_LIB}")
		LIST(APPEND ASL_FFTW_LIBRARIES "${NLC_PATH}/lib/libaslfftw3${ASL_INT}.${ASL_LIB}")
		SET(ASL_INCLUDE ${NLC_PATH}/include)

		SET(ASL_FOUND TRUE)
		FOREACH(A ${ASL_LIBRARIES} ${ASL_FFTW_LIBRARIES})
			IF(NOT EXISTS ${A})
				IF(${ASL_FIND_REQUIRED})
					MESSAGE(FATAL_ERROR "Unable to find ${A}")
				ENDIF()
				SET(ASL_FOUND FALSE)
			ENDIF()
		ENDFOREACH()

		IF(${ASL_FOUND})
			MESSAGE(STATUS "Using NLC ${NLC_VERSION} ASL ${ASL_OPENMP_MSG} ${ASL_LIB_MSG} ${ASL_INT_MSG}")
		ELSE()
			SET(ASL_INCLUDE)
			SET(ASL_LIBRARIES)
			SET(ASL_FFTW_LIBRARIES)
		ENDIF()
	
		UNSET(ASL_LIB)
		UNSET(ASL_LIB_MSG)
		UNSET(ASL_INT)
		UNSET(ASL_INT_MSG)
		UNSET(ASL_OPENMP)
		UNSET(ASL_OPENMP_MSG)
	ENDIF()

	SET(ASL_INCLUDE ${ASL_INCLUDE} CACHE STRING "")
	SET(ASL_LIBRARIES ${ASL_LIBRARIES} CACHE STRING "")
	SET(ASL_FFTW_LIBRARIES ${ASL_FFTW_LIBRARIES} CACHE STRING "")
	SET(ASL_FOUND TRUE CACHE BOOL "")
	MARK_AS_ADVANCED(ASL_INCLUDE ASL_LIBRARIES ASL_FFTW_LIBRARIES ASL_FOUND)
ENDIF()