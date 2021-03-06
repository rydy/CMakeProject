CMAKE_MINIMUM_REQUIRED(VERSION 3.6.1 FATAL_ERROR)

PROJECT(mysql_soci_demo)

FILE(GLOB HDR_DEMO ${PROJECT_SOURCE_DIR}/*.h)	#文件操作命令
AUX_SOURCE_DIRECTORY(. SRC_DEMO)				#将源代码文件存储到变量中
ADD_EXECUTABLE(${PROJECT_NAME}
	${SRC_DEMO}
	${HDR_DEMO}
	data.sql)#添加可执行文件

#boost
IF($ENV{HOST_PLATFORM} STREQUAL PLATFORM_X86)
	IF($ENV{HOST_OS} STREQUAL OS_WINDOWS)
		#boost X86
		SET(BOOST_ROOT "$ENV{BOOST_X86_HOME}")	#ENV:BOOST_X86_HOME
		SET(Boost_USE_STATIC_LIBS ON)
		FIND_PACKAGE(Boost 1.62.0 REQUIRED COMPONENTS system regex date_time atomic chrono thread filesystem log log_setup program_options locale)
		IF(Boost_FOUND)
			INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
			TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${Boost_LIBRARIES})
		ELSE(Boost_FOUND)
			MESSAGE(FATAL_ERROR "Boost not found!")
		ENDIF(Boost_FOUND)
	ELSEIF($ENV{HOST_OS} STREQUAL OS_LINUX)
	ENDIF()
ELSEIF($ENV{HOST_PLATFORM} STREQUAL PLATFORM_X64)
	IF($ENV{HOST_OS} STREQUAL OS_WINDOWS)
		#boost X64
		SET(BOOST_ROOT "$ENV{BOOST_X64_HOME}")	#ENV:BOOST_X64_HOME
		SET(Boost_USE_STATIC_LIBS ON)
		FIND_PACKAGE(Boost 1.62.0 REQUIRED COMPONENTS system regex date_time atomic chrono thread filesystem log log_setup program_options locale)
		IF(Boost_FOUND)
			INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
			TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${Boost_LIBRARIES})
		ELSE(Boost_FOUND)
			MESSAGE(FATAL_ERROR "Boost not found!")
		ENDIF(Boost_FOUND)
	ELSEIF($ENV{HOST_OS} STREQUAL OS_LINUX)
	ENDIF()
ELSEIF($ENV{HOST_PLATFORM} STREQUAL PLATFORM_ARM)
ENDIF()

#Mysql
IF($ENV{HOST_PLATFORM} STREQUAL PLATFORM_X86)
	IF($ENV{HOST_OS} STREQUAL OS_WINDOWS)
		#soci SOCI_X86_HOME
		INCLUDE_DIRECTORIES("$ENV{SOCI_X86_HOME}")
		INCLUDE_DIRECTORIES("$ENV{SOCI_X86_HOME}/include")
		INCLUDE_DIRECTORIES("$ENV{SOCI_X86_HOME}/include/soci")
		INCLUDE_DIRECTORIES("$ENV{SOCI_X86_HOME}/include/soci/mysql")
		TARGET_LINK_LIBRARIES(${PROJECT_NAME} optimized "$ENV{SOCI_X86_HOME}/build/lib/Release/libsoci_core_4_0.lib" debug "$ENV{SOCI_X86_HOME}/build/lib/Debug/libsoci_core_4_0.lib")
		TARGET_LINK_LIBRARIES(${PROJECT_NAME} optimized "$ENV{SOCI_X86_HOME}/build/lib/Release/libsoci_mysql_4_0.lib" debug "$ENV{SOCI_X86_HOME}/build/lib/Debug/libsoci_mysql_4_0.lib")
		#MySql MYSQL_X86_HOME
		INCLUDE_DIRECTORIES("$ENV{MYSQL_X86_HOME}/include")
		TARGET_LINK_LIBRARIES(${PROJECT_NAME} "$ENV{MYSQL_X86_HOME}/lib/libmysql.lib")
	ELSEIF($ENV{HOST_OS} STREQUAL OS_LINUX)
	ENDIF()
ELSEIF($ENV{HOST_PLATFORM} STREQUAL PLATFORM_X64)
	IF($ENV{HOST_OS} STREQUAL OS_WINDOWS)
		#soci SOCI_X64_HOME
		INCLUDE_DIRECTORIES("$ENV{SOCI_X64_HOME}")
		INCLUDE_DIRECTORIES("$ENV{SOCI_X64_HOME}/include")
		INCLUDE_DIRECTORIES("$ENV{SOCI_X64_HOME}/include/soci")
		INCLUDE_DIRECTORIES("$ENV{SOCI_X64_HOME}/include/soci/mysql")
		TARGET_LINK_LIBRARIES(${PROJECT_NAME} optimized "$ENV{SOCI_X64_HOME}/build/lib/Release/libsoci_core_4_0.lib" debug "$ENV{SOCI_X64_HOME}/build/lib/Debug/libsoci_core_4_0.lib")
		TARGET_LINK_LIBRARIES(${PROJECT_NAME} optimized "$ENV{SOCI_X64_HOME}/build/lib/Release/libsoci_mysql_4_0.lib" debug "$ENV{SOCI_X64_HOME}/build/lib/Debug/libsoci_mysql_4_0.lib")
		#MySql MYSQL_X64_HOME
		INCLUDE_DIRECTORIES("$ENV{MYSQL_X64_HOME}/include")
		TARGET_LINK_LIBRARIES(${PROJECT_NAME} "$ENV{MYSQL_X64_HOME}/lib/libmysql.lib")
	ELSEIF($ENV{HOST_OS} STREQUAL OS_LINUX)
	ENDIF()
ELSEIF($ENV{HOST_PLATFORM} STREQUAL PLATFORM_ARM)
ENDIF()

IF(MSVC)
	CONFIGURE_FILE("${PROJECT_SOURCE_DIR}/../../other/VSUserTemplate.vcxproj.user" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}.vcxproj.user")
ENDIF(MSVC)
