###############################################################################
#
# 1.
#
#	Строка необходима, так как язык cmake меняется от версии к версии
#	В проекте выбираем версию cmake такую же, как и в EZE
#
cmake_minimum_required (VERSION 3.10.1)

set(3RDPARTY "${CMAKE_CURRENT_SOURCE_DIR}/..")

###############################################################################
#
#	2. заголовок проекта, макросы
#
project (weeny)

if(NOT DEFINED BUILD_PLATFORM)
	set(BUILD_PLATFORM "GENERIC")
endif()

if (${BUILD_PLATFORM} STREQUAL "DIRECTX_PLATFORM")
else()
	set(GRAPICS_LIBRRARY "OpenGL")
endif()

add_definitions(-DBUILD_${BUILD_PLATFORM})
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set (CMAKE_C_FLAGS ${CMAKE_C_FLAGS} PARENT_SCOPE)
set (CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} PARENT_SCOPE)

###############################################################################
#
#	3. Подключение проекта 
#    заголовочных файлов
#
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/3rdparty)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/platforms/${BUILD_PLATFORM})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/graphics/${GRAPICS_LIBRRARY})

###############################################################################
#
#	4. собираем имена файлов с исходными текстами
#    в две переменные ALL_HEADERS и ALL_SOURCES
# 
# общие исходники
# 
file(GLOB
	ALL_HEADERS

	include/*.h
	include/base/*.h
	include/graphics/OpenGL/*.h
	include/universe/*.h
)
file(GLOB
	ALL_SOURCES

	src/*.cpp
	src/base/*.cpp
	src/universe/*.cpp
)
# 
# платформо-зависимые исходники
# 
file(GLOB
	PLATFORM_HEADERS
	src/platforms/${BUILD_PLATFORM}/*.h
)
file(GLOB
	PLATFORM_SOURCES
	src/platforms/${BUILD_PLATFORM}/*.cpp
	src/platforms/${BUILD_PLATFORM}/*.m
	src/platforms/${BUILD_PLATFORM}/*.mm
)
list(APPEND ALL_HEADERS ${PLATFORM_HEADERS})
list(APPEND ALL_SOURCES ${PLATFORM_SOURCES})
# 
# исходники, зависящие от графической библиотеки
# 
file(GLOB GRAPHICS_HEADERS src/graphics/${GRAPICS_LIBRRARY}/*.h)
file(GLOB GRAPHICS_SOURCES src/graphics/${GRAPICS_LIBRRARY}/*.cpp)
list(APPEND ALL_HEADERS ${GRAPHICS_HEADERS})
list(APPEND ALL_SOURCES ${GRAPHICS_SOURCES})

message(${ALL_SOURCES})

###############################################################################
#
#	5. Настройки, необходимые для создания таргета
#
if (${BUILD_PLATFORM} STREQUAL "ANDROID")
	configure_file (src/platforms/ANDROID/javasrc/MainActivity.java ${CMAKE_BINARY_DIR}/../../${ANDROID_JAVA_SOURCE_PATH}/${ANDROID_ACTIVITY_NAME}.java)

	configure_file (src/platforms/ANDROID/gradle_files/build.gradle ${CMAKE_BINARY_DIR}/../../build.gradle)
	configure_file (src/platforms/ANDROID/gradle_files/settings.gradle ${CMAKE_BINARY_DIR}/../../settings.gradle)
	configure_file (src/platforms/ANDROID/gradle_files/gradle.properties ${CMAKE_BINARY_DIR}/../../gradle.properties)
	file(COPY src/platforms/ANDROID/gradle_files/gradlew DESTINATION ${CMAKE_BINARY_DIR}/../../)
	file(COPY src/platforms/ANDROID/gradle_files/gradlew.bat DESTINATION ${CMAKE_BINARY_DIR}/../../)
	file(COPY src/platforms/ANDROID/gradle_files/gradle DESTINATION ${CMAKE_BINARY_DIR}/../../)
	file(COPY src/platforms/ANDROID/gradle_files/my-release-key.jks DESTINATION ${CMAKE_BINARY_DIR}/../../)

	set (USED_FRAMEWORKS
		${USED_FRAMEWORKS}

		GLESv1_CM
		GLESv2
		m c dl log z
	)

elseif (${BUILD_PLATFORM} STREQUAL "IOS")
	set (USED_FRAMEWORKS
		${USED_FRAMEWORKS}

		"-framework Foundation"
		"-framework OpenGLES"
		"-framework QuartzCore"
		"-framework UIKit"
		"-ObjC"
	)
elseif (${BUILD_PLATFORM} STREQUAL "GENERIC")
	# Find includes in corresponding build directories
	set(CMAKE_INCLUDE_CURRENT_DIR ON)
	# Instruct CMake to run moc automatically when needed.
	set(CMAKE_AUTOMOC ON)
	# Find the QtWidgets library
	find_package(Qt5Widgets)
	# Find the Qt5OpenGL library
	find_package(Qt5OpenGL)
	# Use the Widgets module from Qt 5.
	set (USED_FRAMEWORKS
		${USED_FRAMEWORKS}

		Qt5::Widgets
		Qt5::OpenGL
		)

	if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	    set (USED_FRAMEWORKS
			${USED_FRAMEWORKS}

	        "-framework OpenGL"
	    )
	endif()
endif()

###############################################################################
#
#	6. Создание таргета проекта
#
add_library(
	${PROJECT_NAME}
	STATIC
	${ALL_HEADERS}
	${ALL_SOURCES}
)

###############################################################################
#
#	7. Настройки таргета
#
target_link_libraries(${PROJECT_NAME} ${USED_FRAMEWORKS})

###############################################################################
#
#	8. Сборка ресурсов
#
