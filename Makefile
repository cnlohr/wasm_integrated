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

runtime.wasm : runtime.wat
	wat2wasm -r -o $@ $^

cfile.o : $(C_S)
	$(EMCC) -o $@ -c $(C_S) $(EMCC_FLAGS)

prog.wasm: cfile.o runtime.wasm
	/opt/emscripten-llvm/bin/wasm-ld --no-entry -o $@ cfile.o runtime.wasm --export=_run
	wasm-opt --asyncify $@ -o $@

%.wasm.b64 : %.wasm
	cat $^ | base64 > $@

c-test.html : template.ht prog.wasm.b64 wasmtemplate
	./wasmtemplate template.ht prog.wasm.b64 > $@


wasmtemplate : wasmtemplate.c
	gcc -o $@ $^


clean :
	rm -rf wasmtemplate prog.wasm.b64 prog.wasm cfile.o runtime.wasm

clean_all : clean
	rm -rf c-test.html
