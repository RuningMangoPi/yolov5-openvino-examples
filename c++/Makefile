cc        := g++
CFLAGS += -g -O2 -Wall -W -pedantic
CXXFLAGS=$(CFLAGS) -std=c++11
CFLAGS += -pthread
LDFLAGS += -pthread


LOCAL_DIR	:= $(shell pwd)
$(info "[LOCAL_DIR]: $(LOCAL_DIR)") 


lean_protobuf  := $(LOCAL_DIR)/lean/protobuf3.11.4
lean_opencv    := $(LOCAL_DIR)/lean/opencv-3.4.6
# lean_opencv    := $(LOCAL_DIR)/lean//openvino_2021.4.752/opencv
lean_openvino    := $(LOCAL_DIR)/lean/openvino_2021.4.752

cpp_srcs  := $(shell find src -name "*.cpp")
cpp_objs  := $(cpp_srcs:.cpp=.cpp.o)
cpp_objs  := $(cpp_objs:src/%=objs/%)
cpp_mk    := $(cpp_objs:.cpp.o=.cpp.mk)


include_paths := $(LOCAL_DIR)/src        \
				/usr/include	\
				$(LOCAL_DIR)/src/common/format_reader       \
				$(LOCAL_DIR)/src/common/utils/include  \
				$(LOCAL_DIR)/include     \
			$(lean_protobuf)/include \
			$(lean_opencv)/include \
			$(lean_openvino)/deployment_tools/inference_engine/include \
			$(lean_openvino)/deployment_tools/ngraph/include

# all:
# 	echo $(include_paths)

library_paths := /usr/local/lib	\
			$(lean_protobuf)/lib \
			$(lean_opencv)/lib    \
			$(lean_openvino)/deployment_tools/inference_engine/lib/intel64 \
			$(lean_openvino)/deployment_tools/ngraph/lib

# all:
# 	echo $(library_paths)

link_librarys := opencv_core opencv_imgproc opencv_dnn opencv_videoio opencv_imgcodecs \
			stdc++ protobuf dl gflags inference_engine ngraph inference_engine_transformations


# HAS_PYTHON表示是否编译python支持
support_define    := 

ifeq ($(use_python), true) 
include_paths  += $(python_root)/include/$(python_name)
library_paths  += $(python_root)/lib
link_librarys  += $(python_name)
support_define += -DHAS_PYTHON
endif

empty         :=
export_path   := $(subst $(empty) $(empty),:,$(library_paths))

run_paths     := $(foreach item,$(library_paths),-Wl,-rpath=$(item))
include_paths := $(foreach item,$(include_paths),-I$(item))
library_paths := $(foreach item,$(library_paths),-L$(item))
link_librarys := $(foreach item,$(link_librarys),-l$(item))

cpp_compile_flags := -std=c++11 -lm -g -w -O3 -fPIC -lgflags -pthread -fopenmp $(support_define)
# cu_compile_flags  := -std=c++11 -g -w -O0 -Xcompiler "$(cpp_compile_flags)" $(cuda_arch) $(support_define)
link_flags        := -pthread -fopenmp -Wl,-rpath='$$ORIGIN'

cpp_compile_flags += $(include_paths)
# cu_compile_flags  += $(include_paths)
link_flags        += $(library_paths) $(link_librarys) $(run_paths)

ifneq ($(MAKECMDGOALS), clean)
-include $(cpp_mk) $(cu_mk)
endif

demo    : workspace/demo

library_path.txt : 
	@echo LD_LIBRARY_PATH=$(export_path):"$$"LD_LIBRARY_PATH > $@

workspace/demo : $(cpp_objs) $(cu_objs)
	@echo Link $@
	@mkdir -p $(dir $@)
	@$(cc) $^ -o $@ $(link_flags)

objs/%.cpp.o : src/%.cpp
	@echo Compile CXX $<
	@mkdir -p $(dir $@)
	@$(cc) -c $< -o $@ $(cpp_compile_flags)

clean :
	@rm -rf objs workspace/demo
	@rm -rf build


# 导出符号，使得运行时能够链接上
export LD_LIBRARY_PATH:=$(export_path):$(LD_LIBRARY_PATH)