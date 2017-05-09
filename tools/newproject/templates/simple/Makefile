PROJECT_NAME=@ProjectName@
CMAKE_BUILD_TYPE=Debug
REVERSE_COMPANY_DOMAIN=com.example.myapp

COMMON_DEFINITIONS= \
	-DPROJECT_NAME=$(PROJECT_NAME) \
	-DCMAKE_BUILD_TYPE=$(CMAKE_BUILD_TYPE)
	
#############################################################################
#
#
#
ANDROID_ABI=armeabi-v7a
ANDROID_ACTIVITY_NAME=$(PROJECT_NAME)
ANDROID_BUILD_APPLICATION_ID=$(REVERSE_COMPANY_DOMAIN)
ANDROID_BUILD_MIN_SDK_VERSION=15
ANDROID_BUILD_SDK_VERSION=23
ANDROID_BUILD_TARGET_SDK_VERSION=23
ANDROID_BUILD_TOOLS_VERSION=25.0.3
ANDROID_JAVA_SOURCE_PATH=src/$(subst .,/,$(REVERSE_COMPANY_DOMAIN))
ANDROID_JNI_NATIVE_METHOD_NAME=$(subst .,_,$(REVERSE_COMPANY_DOMAIN))_$(ANDROID_ACTIVITY_NAME)
ANDROID_PACKAGE_NAME=$(ANDROID_BUILD_APPLICATION_ID)
ANDROID_PLATFORM=android-19

ifeq ($(CMAKE_BUILD_TYPE), Debug)
	ANDROID_BUILD_TYPE=debug
else ifeq ($(CMAKE_BUILD_TYPE), Release)
	ANDROID_BUILD_TYPE=release
endif

ANDROID:
	mkdir -p build/$@ && cd build/$@ && \
	((mkdir assets) || (rm -rf assets/*)) && \
	((mkdir jni) || (rm -rf jni/*)) && \
	((mkdir -p $(ANDROID_JAVA_SOURCE_PATH)) || (rm -rf $(ANDROID_JAVA_SOURCE_PATH)/*)) && \
	(android create project --name $(PROJECT_NAME) --path . --target $(ANDROID_PLATFORM) --package $(ANDROID_PACKAGE_NAME) --activity $(ANDROID_ACTIVITY_NAME) || \
	android update project --name $(PROJECT_NAME) --path . --target $(ANDROID_PLATFORM)) && \
	rm -rf libs/* && \
	mkdir -p obj/$(ANDROID_ABI) && cd obj/$(ANDROID_ABI) && \
	cmake \
	-DBUILD_PLATFORM=$@ \
	$(COMMON_DEFINITIONS) \
	-DANDROID_ACTIVITY_NAME=$(ANDROID_ACTIVITY_NAME) \
	-DANDROID_BUILD_APPLICATION_ID=$(ANDROID_BUILD_APPLICATION_ID) \
	-DANDROID_BUILD_MIN_SDK_VERSION=$(ANDROID_BUILD_MIN_SDK_VERSION) \
	-DANDROID_BUILD_SDK_VERSION=$(ANDROID_BUILD_SDK_VERSION) \
	-DANDROID_BUILD_TARGET_SDK_VERSION=$(ANDROID_BUILD_TARGET_SDK_VERSION) \
	-DANDROID_BUILD_TOOLS_VERSION=$(ANDROID_BUILD_TOOLS_VERSION) \
	-DANDROID_JAVA_SOURCE_PATH=$(ANDROID_JAVA_SOURCE_PATH) \
	-DANDROID_JNI_NATIVE_METHOD_NAME=$(ANDROID_JNI_NATIVE_METHOD_NAME) \
	-DANDROID_PACKAGE_NAME=$(ANDROID_PACKAGE_NAME) \
	-DCMAKE_TOOLCHAIN_FILE=../../../../../@weeny/src/platforms/ANDROID/android.toolchain.cmake \
	-DLIBRARY_OUTPUT_PATH_ROOT=../../. \
	../../../../	&& \
	make install -j 8 && \
	cd ../../. && \
	./gradlew $(ANDROID_BUILD_TYPE) && \
	adb install -r ./build/outputs/apk/$(PROJECT_NAME)-$(ANDROID_BUILD_TYPE).apk && \
	adb shell am start -n $(ANDROID_BUILD_APPLICATION_ID)/$(ANDROID_PACKAGE_NAME).$(ANDROID_ACTIVITY_NAME)
	
ANDROID_RUN:
	cd build/ANDROID && \
	adb install -r ./build/outputs/apk/$(PROJECT_NAME)-$(ANDROID_BUILD_TYPE).apk && \
	adb shell am start -n $(ANDROID_BUILD_APPLICATION_ID)/$(ANDROID_PACKAGE_NAME).$(ANDROID_ACTIVITY_NAME)

#############################################################################
#
#
#
IOS:
	mkdir -p build/$@ && cd build/$@ && \
	cmake -G Xcode \
	-DBUILD_PLATFORM=$@ \
	-DAPP_TYPE=MACOSX_BUNDLE \
	-DBUNDLE_IDENTIFIER=$(REVERSE_COMPANY_DOMAIN).$(PROJECT_NAME) \
	$(COMMON_DEFINITIONS) \
	../../ && \
	open $(PROJECT_NAME).xcodeproj

#############################################################################
#
#
#
UNAME_S := $(shell uname -s)
# http://stackoverflow.com/questions/714100/os-detecting-makefile
ifeq ($(UNAME_S),Darwin)
	GENERIC_MAKEFILE_GENERATOR="Xcode"
	APP_TYPE=MACOSX_BUNDLE
else
	GENERIC_MAKEFILE_GENERATOR="Unix Makefiles"
endif

GENERIC:
	mkdir -p build/$@ && cd build/$@ && \
	cmake -G $(GENERIC_MAKEFILE_GENERATOR) \
	-DBUILD_PLATFORM=$@ \
	-DAPP_TYPE=$(APP_TYPE) \
	$(COMMON_DEFINITIONS) \
	../../ && \
	open $(PROJECT_NAME).xcodeproj

#############################################################################
#
#
#
clean:
	rm -r ./build/$(target)
