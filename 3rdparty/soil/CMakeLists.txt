cmake_minimum_required(VERSION 3.8)

project(soil)

include_directories(.)

set(HEADERS
	./SOIL.h
	./image_DXT.h
	./image_helper.h
	./stb_image_aug.h
	./stbi_DDS_aug.h
	./stbi_DDS_aug_c.h
	)

set(SRCS 
	./SOIL.c
	./image_DXT.c
	./image_helper.c
	./stb_image_aug.c
	)

add_library (${PROJECT_NAME} STATIC ${SRCS} ${HEADERS})
