all : c-test.html

ifneq ("$(wildcard ~/git/emsdk/upstream/emscripten/emcc)","")
EMCC?=~/git/emsdk/upstream/emscripten/emcc
else
EMCC?=emcc
endif

EMCC_FLAGS:= -s EXPORTED_FUNCTIONS='["_testcallback","_add2","_Wmain","_mymain","_asyncify_start_unwind","_asyncify_stop_rewind","_asyncify_stop_unwind","_asyncify_start_rewind","_setThrew"]' -s EXPORTED_RUNTIME_METHODS='["ccall", "cwrap"]' -s ERROR_ON_UNDEFINED_SYMBOLS=0 -s ASYNCIFY
#-s SIDE_MODULE=1
#-s STANDALONE_WASM=1
#-s MODULARIZE

C_S:=cfile.c


cfile.wasm : $(C_S)
	$(EMCC) -o $@ $(C_S) $(EMCC_FLAGS)

%.wasm.b64 : %.wasm
	cat $^ | base64 > $@

c-test.html : template.ht cfile.wasm.b64 wasmtemplate
	./wasmtemplate template.ht cfile.wasm.b64 > $@


wasmtemplate : wasmtemplate.c
	gcc -o $@ $^


clean :
	rm -rf wasmtemplate cfile.wasm.b64 cfile.wasm

clean_all : clean
	rm -rf c-test.html
