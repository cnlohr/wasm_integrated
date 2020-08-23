all : c-test.html


ifneq ("$(wildcard ~/git/emsdk/upstream/emscripten/emcc)","")
EMCCFOLDER?=~/git/emsdk/upstream/
else
EMCCFOLDER?=
endif

EMCC?=$(EMCCFOLDER)emscripten/emcc
WASMLD?=$(EMCCFOLDER)bin/wasm-ld
WASMAS?=$(EMCCFOLDER)bin/wasm-as


EMCC_FLAGS:=  -s SIDE_MODULE=1 -s EXPORTED_FUNCTIONS='["_add2","_add2cwat"]' \

#-s EXPORTED_RUNTIME_METHODS='["ccall","cwrap"]' \
#-s ERROR_ON_UNDEFINED_SYMBOLS=0 -s ASYNCIFY=1 -s EXPORT_ALL=1 -s RELOCATABLE=1 -shared
#-s SIDE_MODULE=1
#-s STANDALONE_WASM=1
#-s MODULARIZE
#-s RELOCATABLE=1
#-s EXPORT_ALL=1

C_S:=cfile.c

watfile.wasm : watfile.wat
	wat2wasm -r $^

cfile.wasm : $(C_S)
	$(EMCC) -o $@ $(C_S) $(EMCC_FLAGS)

%.wasm.b64 : %.wasm
	cat $^ | base64 > $@

#watfile.wasm

c-test.wasm : cfile.wasm watfile.wasm main.c
	$(EMCC) -o $@ $^ -s LLD_REPORT_UNDEFINED -s EXPORTED_FUNCTIONS='["_add2","_main"]'

#/home/cnlohr/git/emsdk/upstream/bin/wasm-ld -o /tmp/emscripten_temp_gm7rlctw/c-test.wasm cfile.wasm -L/home/cnlohr/git/emsdk/upstream/emscripten/system/local/lib watfile.wasm -L/home/cnlohr/git/emsdk/upstream/emscripten/system/lib -L/home/cnlohr/git/emsdk/upstream/emscripten/cache/wasm /home/cnlohr/git/emsdk/upstream/emscripten/cache/wasm/crt1.o /home/cnlohr/git/emsdk/upstream/emscripten/cache/wasm/libc.a /home/cnlohr/git/emsdk/upstream/emscripten/cache/wasm/libcompiler_rt.a /home/cnlohr/git/emsdk/upstream/emscripten/cache/wasm/libc-wasm.a /home/cnlohr/git/emsdk/upstream/emscripten/cache/wasm/libc++-noexcept.a /home/cnlohr/git/emsdk/upstream/emscripten/cache/wasm/libc++abi-noexcept.a /home/cnlohr/git/emsdk/upstream/emscripten/cache/wasm/libdlmalloc.a /home/cnlohr/git/emsdk/upstream/emscripten/cache/wasm/libpthread_stub.a /home/cnlohr/git/emsdk/upstream/emscripten/cache/wasm/libstandalonewasm.a /home/cnlohr/git/emsdk/upstream/emscripten/cache/wasm/libc_rt_wasm.a /home/cnlohr/git/emsdk/upstream/emscripten/cache/wasm/libsockets.a -mllvm -combiner-global-alias-analysis=false -mllvm -enable-emscripten-sjlj -mllvm -disable-lsr --allow-undefined --strip-debug --export stackSave --export stackRestore --export stackAlloc --export __data_end --export fflush --export __errno_location -z stack-size=5242880 --initial-memory=16777216 --max-memory=16777216 --global-base=1024


# -s LLD_REPORT_UNDEFINED -s EXPORT_ALL=1

#	$(WASMLD) -o $@ $^
#	$(EMCC) -o $@ $^  -s EXPORTED_FUNCTIONS='["_add2","_add2cwat"]' -s ASYNCIFY=1 -s EXPORT_ALL=1 --no-entry -s STANDALONE_WASM=1 -s LLD_REPORT_UNDEFINED

c-test.html : c-test.template c-test.wasm.b64 ../wasmtemplate
	../wasmtemplate c-test.template c-test.wasm.b64 > $@

clean :
	rm -rf cfile.wasm.b64 cfile.wasm watfile.wasm 

clean_all : clean
	rm -rf c-test.html
