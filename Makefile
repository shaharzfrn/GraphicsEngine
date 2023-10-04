PROJECT := CGApp
EXE_OUT := main
EXECUTABLE := main


SOURCE_DIR := ./src
SOURCES = $(shell find $(SOURCE_DIR) -name '*.cpp')
BUILD_DIR := ./build

CC := g++
C_FLAGS := -std=c++20
CXX_FLAGS := -Werror -I./src -I./src/math -I./src/shader -I./src/cgl -I./src/window -I./src/Irit -I./src/Irit/inc_irit

OBJECTS := $(patsubst $(SOURCE_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SOURCES))
OBJ := 	\
	./src/math/math.o 	\
	./src/math/vec.o 	\
	./src/math/mat.o 	\
	./src/math/box.o 	\
	\
	./src/cgl/cgl.o 		\
	./src/cgl/buffer.o 		\
	./src/cgl/clip.o 		\
	./src/cgl/texture.o 		\
	./src/cgl/shadow.o 		\
	./src/cgl/interpolate.o 	\
	\
	./src/window/window.o 	\
	./src/window/frame.o 		\
	./src/window/panel.o 		\
	./src/window/object_settings.o\
	./src/window/application.o 	\
	./src/window/bitmap_utils.o 	\
	./src/window/abstract_light_dialog.o 	\
	./src/window/light_dialog.o 	\
	\
	./src/shader/shader.o 	\
	./src/shader/model_shader.o 	\
	./src/shader/phong_shader.o 	\
	./src/shader/gouraud_shader.o \
	./src/shader/flat_shader.o \
	./src/shader/shadow_shader.o \
	./src/shader/cgl_shaders.o \
	./src/shader/silhouette_shader.o \
	./src/shader/line_shader.o \
	./src/shader/bounding_box_shader.o \
	\
	./src/loader.o 	\
	./src/model.o 	\
	./src/cgl_app.o 	\
	./src/light.o 	\
	./src/camera.o 	\
	./src/projection.o 	\
	./src/init.o 		\
	\


IRIT_LIBS := 	src/Irit/circlink/circlink.o 		\
		-Lsrc/Irit/lib 			\
		-lIritExt -lIritGrap -lIritUser    	\
		-lIritRndr -lIritBool -lIritPrsr   	\
		-lIritVMdl -lIritMdl -lIritMvar    	\
		-lIritTrim -lIritTriv -lIritTrng   	\
		-lIritSymb -lIritCagd -lIritGeom   	\
		-lIritMisc -lIritXtra              	\
		-lz

WX_CXX_FLAGS := wx-config --cxxflags
WX_LIBS := wx-config --libs all

LIBS := -lm -lpng

all: build_dir $(BUILD_DIR)/$(EXECUTABLE)
	
build_dir:
	@mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/$(EXECUTABLE): $(OBJECTS)
	@echo "Create executable"
	@$(CC) $^ $(C_FLAGS) $(CXX_FLAGS) `$(WX_LIBS)` $(IRIT_LIBS) $(LIBS) -o $(@F)
	@echo "Executable $(@F) ready to use."
	@echo "Use ./$(@F) to run"

$(OBJECTS): $(BUILD_DIR)/%.o : $(SOURCE_DIR)/%.cpp
	@echo "Compile $^ into $@"
	@mkdir -p $(@D)
	@$(CC) -c $< $(C_FLAGS) $(CXX_FLAGS) `$(WX_CXX_FLAGS)` -o $@

clean_all:
	@rm -rf $(BUILD_DIR)

clean:
	@rm -rf $(BUILD_DIR)/*
