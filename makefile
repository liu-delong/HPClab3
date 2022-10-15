# 统一windows和linux
ifeq ($(OS),Windows_NT)
	Windows:=true
	rm:=-del /F /S /Q
	rm_folder:=-rd /Q /S
	path_seperator:=;
	subpath_sign=\\
	detected_OS := Windows

else
    detected_OS := $(shell sh -c 'uname 2>/dev/null || echo Unknown')
	path_seperator:=:
	Linux:=true
	rm:=-rm -rf
	subpath_sign=/
	rm_folder:=-rm -rf
endif

common_src:=$(wildcard src/common/*.cpp)
common_src:=$(notdir $(common_src))
common_obj:=$(patsubst %.cpp,%.o,$(common_src))
src:=$(wildcard src/*.cpp)
src:=$(notdir $(src))
obj:=$(patsubst %.cpp,%.o,$(src))
# 设置环境变量，使得源代码#include时不用指定路径
ptemp:=$(CPLUS_INCLUDE_PATH)$(path_seperator).$(subpath_sign)src$(subpath_sign)$(path_seperator).$(subpath_sign)src$(subpath_sign)common$(subpath_sign)$(path_seperator)
export CPLUS_INCLUDE_PATH=$(ptemp)
temp_path:=$(PATH)$(path_seperator).$(subpath_sign)obj
export PATH=$(temp_path)
export LIBRARY_PATH=.$(subpath_sign)obj
VPATH=obj src src$(subpath_sign)common

 
# 统一windows和linux创建文件夹操作
ifeq ($(detected_OS),Windows)
	create_folder_obj:=if exist obj (mkdir abc.no.use.temp && rd abc.no.use.temp) else mkdir obj
endif

ifeq ($(detected_OS),Linux)
	create_folder_obj:=if test -d obj;then echo;else mkidr obj; fi
endif



target:=main1 main2
ifeq ($(detected_OS),Windows)
	target:=$(patsubst %,%.exe,$(target))
endif

# 开始定义规则

all:run

# 自动依赖生成
depend_file:=$(patsubst %.o,%.d,$(common_obj) $(obj))
depend_file:=$(wildcard $(addprefix obj/,$(depend_file)))

ifneq ($(depend_file),)
include $(depend_file)
endif

.PHONY:all clean

scale:=512 1024 1536 2048
core_num:=1 2 3 4 5 6 7 8
mpi_gemm:MPI_GEMM.cpp matrix_tool.cpp 
	mpicxx -o $@ $^
mpi_group:MPI_group.cpp matrix_tool.cpp
	mpicxx -o $@ $^
rmpi_gemm:mpi_gemm
	@echo mpi_gemm:
	@for s in $(scale); do \
		for c in $(core_num); do \
			mpirun -np $$c -hosts 127.0.0.1 ./mpi_gemm $$s $$s $$s; \
		done \
	done
rmpi_group:mpi_group
	@echo mpi_group:
	@for s in $(scale); do \
		for c in $(core_num); do \
			mpirun -np $$c -hosts 127.0.0.1 ./mpi_group $$s $$s $$s; \
		done \
	done 
run:rmpi_gemm rmpi_group

matrix_mul:CoppersmithWinograd.cpp loop_expansion.cpp matrix_tool.cpp Strassen.cpp universal.cpp
	g++ $^ -fPIC -shared -o lib$@.so
so_demo:so_demo.cpp matrix_mul.so
	g++ $< -L. -lmatrix_mul -o $@
obj/%.o:%.cpp
	$(shell $(create_folder_obj))
	g++ -c $< -o $@ -MD

clean:
	$(rm) *.exe $(addprefix obj$(subpath_sign),*.o *.d)
# 创建obj文件夹，存放编译中间过程