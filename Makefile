all : c-test.html

ifneq ("$(wildcard ~/git/emsdk/upstream/emscripten/emcc)","")
EMCC?=~/git/emsdk/upstream/emscripten/emcc
else
EMCC?=emcc
endif

EMCC_FLAGS:= --no-entry -s EXPORTED_FUNCTIONS='["_run","_animation"]' -s EXPORTED_RUNTIME_METHODS='["ccall", "cwrap"]'
#-s SIDE_MODULE=1
#-s STANDALONE_WASM=1
#-s MODULARIZE

C_S:=cfile.c

env.wasm : env.wat
	wat2wasm -r -o $@ $^

cfile.wasm : $(C_S) env.wasm
	$(EMCC) -o $@ $(C_S) env.wasm $(EMCC_FLAGS)
	wasm-opt --asyncify $@ -o $@

%.wasm.b64 : %.wasm
	cat $^ | base64 > $@

c-test.html : template.ht cfile.wasm.b64 wasmtemplate
	./wasmtemplate template.ht cfile.wasm.b64 > $@


wasmtemplate : wasmtemplate.c
	gcc -o $@ $^


clean :
	rm -rf wasmtemplate cfile.wasm.b64 cfile.wasm env.wasm

clean_all : clean
	rm -rf c-test.html
