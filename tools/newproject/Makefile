###########################################################################
#
# make NEWPROJECT name=ProjectName root=ProjectRoot
#
# Цель NEWPROJECT создаёт новый проект ProjectName
# в папке ProjectRoot, по умолчанию ../../../
# Xgen подключается или ссылкой или субмодулем git, по умолчанию ссылкой
#
NEWPROJECT:
ifeq ($(name),)
	@echo 'usage:'
	@echo 'make NEWPROJECT name=<ProjectName> [root=<ProjectRoot>]'
	@echo
	@echo 'name: name of your new project'
	@echo
	@echo 'root: path to new project root folder. default is ../../../'
	@echo
	@echo 'ERROR: name parameter required'
	@echo
	exit 1
endif
ifeq (,$(shell which node))
	@echo 'nodejs required'
	exit 1
endif
ifeq (,$(shell which convert))
	@echo 'ImageMagic convert required'
	exit 1
endif
ifeq ($(root),)
	$(eval root=../../../)
	@echo 'WARNING: use $(root) as root folder'
endif
ifeq ($(template),)
	$(eval templatePath=./templates/simple)
else
	$(eval templatePath=./templates/$(template))
endif
	@echo 'template path is $(templatePath)'
	$(eval ppath=$(abspath $(root)$(name)))
	mkdir -p $(ppath)
ifeq ($(OS),Windows_NT)
	cp -r $(templatePath)/* $(ppath)/
else
	cp -r $(templatePath)/ $(ppath)/
endif
ifeq ($(weeny_home),)
	$(eval weeny_home=$(shell basename $(shell cd ../../ && pwd)))
endif
	(sed -i.bak -e "s/@ProjectName@/$(name)/g" $(ppath)/Makefile) && (rm -rf $(ppath)/Makefile.bak)
	(sed -i.bak -e "s/@weeny_home@/$(weeny_home)/g" $(ppath)/Makefile) && (rm -rf $(ppath)/Makefile.bak)
	(sed -i.bak -e "s/@weeny_home@/$(weeny_home)/g" $(ppath)/CMakeLists.txt) && (rm -rf $(ppath)/CMakeLists.txt.bak)
##########################################################################
#
# Создание иконок для всех платформ
#
ifeq ($(OS),Windows_NT)
	$(eval png=)
else
	$(eval png=png32:)
endif

	$(eval icons=./identicons/identicon.js)
	$(eval xpmFileName=icon.xpm)
	node $(icons) $(name) $(xpmFileName)
#
# Иконки OSX
#
	mkdir -p $(ppath)/targets/GENERIC/addres/icons/icons.iconset
	convert -filter box -resize 16x16 $(xpmFileName) $(png)$(ppath)/targets/GENERIC/addres/icons/icons.iconset/icon_16x16.png
	convert -filter box -resize 32x32 $(xpmFileName) $(png)$(ppath)/targets/GENERIC/addres/icons/icons.iconset/icon_16x16@2x.png
	convert -filter box -resize 32x32 $(xpmFileName) $(png)$(ppath)/targets/GENERIC/addres/icons/icons.iconset/icon_32x32.png
	convert -filter box -resize 64x64 $(xpmFileName) $(png)$(ppath)/targets/GENERIC/addres/icons/icons.iconset/icon_32x32@2x.png
	convert -filter box -resize 128x128 $(xpmFileName) $(png)$(ppath)/targets/GENERIC/addres/icons/icons.iconset/icon_128x128.png
	convert -filter box -resize 256x256 $(xpmFileName) $(png)$(ppath)/targets/GENERIC/addres/icons/icons.iconset/icon_128x128@2x.png
	convert -filter box -resize 256x256 $(xpmFileName) $(png)$(ppath)/targets/GENERIC/addres/icons/icons.iconset/icon_256x256.png
	convert -filter box -resize 512x512 $(xpmFileName) $(png)$(ppath)/targets/GENERIC/addres/icons/icons.iconset/icon_256x256@2x.png
	convert -filter box -resize 512x512 $(xpmFileName) $(png)$(ppath)/targets/GENERIC/addres/icons/icons.iconset/icon_512x512.png
	convert -filter box -resize 1024x1024 $(xpmFileName) $(png)$(ppath)/targets/GENERIC/addres/icons/icons.iconset/icon_512x512@2x.png
ifeq (,$(shell which iconutil))
else
	iconutil -c icns -o $(ppath)/targets/GENERIC/addres/icons/icons.icns $(ppath)/targets/GENERIC/addres/icons/icons.iconset
endif
#
# Иконки IOS
#
	mkdir -p $(ppath)/targets/IOS/addres/icons
	convert -filter box -resize 57x57 $(xpmFileName) $(png)$(ppath)/targets/IOS/addres/icons/Icon57.png
	convert -filter box -resize 60x60 $(xpmFileName) $(png)$(ppath)/targets/IOS/addres/icons/Icon60.png
	convert -filter box -resize 72x72 $(xpmFileName) $(png)$(ppath)/targets/IOS/addres/icons/Icon72.png
	convert -filter box -resize 76x76 $(xpmFileName) $(png)$(ppath)/targets/IOS/addres/icons/Icon76.png
	convert -filter box -resize 114x114 $(xpmFileName) $(png)$(ppath)/targets/IOS/addres/icons/Icon114.png
	convert -filter box -resize 120x120 $(xpmFileName) $(png)$(ppath)/targets/IOS/addres/icons/Icon120.png
	convert -filter box -resize 144x144 $(xpmFileName) $(png)$(ppath)/targets/IOS/addres/icons/Icon144.png
	convert -filter box -resize 152x152 $(xpmFileName) $(png)$(ppath)/targets/IOS/addres/icons/Icon152.png
	convert -filter box -resize 180x180 $(xpmFileName) $(png)$(ppath)/targets/IOS/addres/icons/Icon180.png
#
# Иконки ANDROID
#
	mkdir -p $(ppath)/targets/ANDROID/addres/icons
	convert -filter box -resize 48x48 $(xpmFileName) $(png)$(ppath)/targets/ANDROID/addres/icons/Icon48.png
	convert -filter box -resize 72x72 $(xpmFileName) $(png)$(ppath)/targets/ANDROID/addres/icons/Icon72.png
	convert -filter box -resize 96x96 $(xpmFileName) $(png)$(ppath)/targets/ANDROID/addres/icons/Icon96.png
	convert -filter box -resize 144x144 $(xpmFileName) $(png)$(ppath)/targets/ANDROID/addres/icons/Icon144.png
	convert -filter box -resize 192x192 $(xpmFileName) $(png)$(ppath)/targets/ANDROID/addres/icons/Icon192.png
#
	rm $(xpmFileName)
