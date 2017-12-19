###############################################################################
#
# 1.
#
#	Строка необходима, так как язык cmake меняется от версии к версии
#	В проекте выбираем версию cmake такую же, как и в @weeny
#
cmake_minimum_required (VERSION 2.8.8)

if (NOT DEFINED BUILD_PLATFORM)
	set(BUILD_PLATFORM "GENERIC")
endif()

set(WEENY "${CMAKE_CURRENT_SOURCE_DIR}/../@weeny_home@")

###############################################################################
#
#	2. заголовок проекта, макросы
#
project (${PROJECT_NAME})

if (${BUILD_PLATFORM} STREQUAL "IOS")
	# эту переменную не удалось перенести в Makefile
	# она должна определяться после команды project (${PROJECT_NAME})
	# иначе не работает
	set(CMAKE_OSX_SYSROOT "iphoneos")
endif()

add_definitions('-DPROJECT_NAME="${PROJECT_NAME}"')

###############################################################################
#
#	3. Подключение проекта Micro Kernel Game Engine
#
add_subdirectory(${WEENY} ${CMAKE_BINARY_DIR}/weeny)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${WEENY}/include)
include_directories(${WEENY}/src/platforms/${BUILD_PLATFORM})
include_directories(${WEENY}/3rdparty)

###############################################################################
#
#	4. собираем имена файлов с исходными текстами
#    в две переменные ALL_HEADERS и ALL_SOURCES
#
file(GLOB
    ALL_HEADERS

    ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h
    )

file(GLOB
	ALL_SOURCES

	${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
	)

###############################################################################
#
#	5. Настройки, необходимые для создания таргета
#
if (${BUILD_PLATFORM} STREQUAL "ANDROID")
	configure_file (${WEENY}/src/platforms/ANDROID/jni/jni.cpp ${CMAKE_BINARY_DIR}/jni/jni.cpp)
	list (APPEND ALL_SOURCES ${CMAKE_BINARY_DIR}/jni/jni.cpp)
	
	configure_file (${CMAKE_CURRENT_SOURCE_DIR}/targets/ANDROID/addres/strings.xml ${CMAKE_BINARY_DIR}/../../res/values/strings.xml)
	configure_file (${CMAKE_CURRENT_SOURCE_DIR}/targets/ANDROID/cmake/ant.properties ${CMAKE_BINARY_DIR}/../../ant.properties)
	configure_file (${CMAKE_CURRENT_SOURCE_DIR}/targets/ANDROID/cmake/AndroidManifest.xml ${CMAKE_BINARY_DIR}/../../AndroidManifest.xml)

	configure_file (${CMAKE_CURRENT_SOURCE_DIR}/targets/ANDROID/addres/icons/Icon48.png ${CMAKE_BINARY_DIR}/../../res/drawable-mdpi/ic_launcher.png COPYONLY)
	configure_file (${CMAKE_CURRENT_SOURCE_DIR}/targets/ANDROID/addres/icons/Icon72.png ${CMAKE_BINARY_DIR}/../../res/drawable-hdpi/ic_launcher.png COPYONLY)
	configure_file (${CMAKE_CURRENT_SOURCE_DIR}/targets/ANDROID/addres/icons/Icon96.png ${CMAKE_BINARY_DIR}/../../res/drawable-xhdpi/ic_launcher.png COPYONLY)
	configure_file (${CMAKE_CURRENT_SOURCE_DIR}/targets/ANDROID/addres/icons/Icon144.png ${CMAKE_BINARY_DIR}/../../res/drawable-xxhdpi/ic_launcher.png COPYONLY)
	configure_file (${CMAKE_CURRENT_SOURCE_DIR}/targets/ANDROID/addres/icons/Icon192.png ${CMAKE_BINARY_DIR}/../../res/drawable-xxxhdpi/ic_launcher.png COPYONLY)

elseif (${BUILD_PLATFORM} STREQUAL "GENERIC")
	
	if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
		set(MACOSX_BUNDLE_ICON_FILE "icons.icns")
		file(GLOB APP_ICONS "${CMAKE_CURRENT_SOURCE_DIR}/targets/GENERIC/addres/icons/icons.icns")
		set_source_files_properties(${APP_ICONS} PROPERTIES MACOSX_PACKAGE_LOCATION Resources)		
	endif()	

elseif (${BUILD_PLATFORM} STREQUAL "IOS")
	# сделано для IOS, что бы сработал MacOSXBundleInfo.plist.in
	set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/targets/${BUILD_PLATFORM}/cmake" ${CMAKE_MODULE_PATH})

	# !!! АХТУНГ !!! без правильной картинки Default-568h@2x.png не работает fullscreen
	file(GLOB APP_ICONS 
			"${CMAKE_CURRENT_SOURCE_DIR}/targets/${BUILD_PLATFORM}/addres/icons/*.png"
			"${CMAKE_CURRENT_SOURCE_DIR}/targets/${BUILD_PLATFORM}/addres/defaultscreens/*.png"
		)
	set_source_files_properties(${APP_ICONS} PROPERTIES MACOSX_PACKAGE_LOCATION Resources)
endif()

###############################################################################
#
#	6. Создание таргета проекта
#
if (${BUILD_PLATFORM} STREQUAL "ANDROID")
	add_library (
		${PROJECT_NAME}
		SHARED
		${ALL_HEADERS}
		${ALL_SOURCES}
		${RESOURCES}
		)
else()
	add_executable(
		${PROJECT_NAME}
		${APP_TYPE}
		${APP_ICONS}
		${ALL_HEADERS}
		${ALL_SOURCES}
		${RESOURCES}
		)
endif()

target_link_libraries(${PROJECT_NAME} weeny ${USED_FRAMEWORKS})

###############################################################################
#
#	7. Настройки таргета
#
if (${BUILD_PLATFORM} STREQUAL "ANDROID")
	install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_BINARY_DIR}/libs/armeabi)
elseif (${BUILD_PLATFORM} STREQUAL "IOS")
	set_target_properties(
		${PROJECT_NAME} 
		PROPERTIES 
	  XCODE_ATTRIBUTE_TARGETED_DEVICE_FAMILY "1,2"
	)
endif()

###############################################################################
#
#	8. Сборка ресурсов
#
