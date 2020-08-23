all : c-test.html

ifneq ("$(wildcard ~/git/emsdk/upstream/emscripten/emcc)","")
EMCC?=~/git/emsdk/upstream/emscripten/emcc
else
EMCC?=emcc
endif

EMCC_FLAGS:= -s EXPORTED_FUNCTIONS='["_testcallback","_add2","_animationFrame", \
	"_testmain","_csleep",\
	"_asyncify_stop_unwind",\
	"_asyncify_start_rewind","_asyncify_start_unwind","_asyncify_stop_rewind"]' \
	-s EXPORTED_RUNTIME_METHODS='["ccall","cwrap"]' \
	-s ERROR_ON_UNDEFINED_SYMBOLS=0 -s ASYNCIFY=1

# -s EXPORT_ALL=1
# -s SIDE_MODULE=1
#-s STANDALONE_WASM=1
#-s MODULARIZE

C_S:=cfile.c watfile.wasm

watfile.wasm : watfile.wat
	wat2wasm -r $^

cfile.wasm : $(C_S)
	$(EMCC) -o $@ $(C_S) $(EMCC_FLAGS)

%.wasm.b64 : %.wasm
	cat $^ | base64 > $@

#c-test.wasm : cfile.wasm watfile.wasm
#	$(EMCC) -o $@ $^  -s ASYNCIFY=1 -s EXPORT_ALL=1 --no-entry

c-test.html : template.ht cfile.wasm.b64 wasmtemplate
	./wasmtemplate template.ht c-test.wasm.b64 > $@


wasmtemplate : wasmtemplate.c
	gcc -o $@ $^


clean :
	rm -rf wasmtemplate cfile.wasm.b64 cfile.wasm watfile.wasm

clean_all : clean
	rm -rf c-test.html
