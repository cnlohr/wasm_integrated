all : c-test.html

ifneq ("$(wildcard ~/git/emsdk/upstream/emscripten/emcc)","")
EMCC?=~/git/emsdk/upstream/emscripten/emcc
else
EMCC?=emcc
endif

EMCC_FLAGS:= --no-entry -s EXPORTED_FUNCTIONS='["_getCallStackData","_doLog","_animation"]' -s EXPORTED_RUNTIME_METHODS='["ccall", "cwrap"]' -s ERROR_ON_UNDEFINED_SYMBOLS=0
#-s SIDE_MODULE=1
#-s STANDALONE_WASM=1
#-s MODULARIZE

C_S:=cfile.c

cfile.wasm : $(C_S)
	$(EMCC) -o $@ $(C_S) $(EMCC_FLAGS)
	wasm-opt --asyncify $@ -o $@

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
