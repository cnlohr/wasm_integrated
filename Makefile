all : c-test.html

C_S:=cfile.c

cfile.wasm : $(C_S)
	clang -Wl,--no-entry,--allow-undefined,--export=runAnimation,--export=runTimer,--export=reenterAnimation,--export=reenterTimer,--export=submitFrame,--export=timerSleep -nostdlib --target=wasm32 -o $@ $(C_S)
	wasm2wat -o cfile.wat cfile.wasm
	sed -i 's/$$start_unwind/$$asyncify_start_unwind/g' cfile.wat
	sed -i 's/$$stop_unwind/$$asyncify_stop_unwind/g' cfile.wat
	sed -i 's/$$start_rewind/$$asyncify_start_rewind/g' cfile.wat
	sed -i 's/$$stop_rewind/$$asyncify_stop_rewind/g' cfile.wat
	sed -i 's/(import "env" "start_unwind"/(import "asyncify" "start_unwind"/g' cfile.wat
	sed -i 's/(import "env" "stop_unwind"/(import "asyncify" "stop_unwind"/g' cfile.wat
	sed -i 's/(import "env" "start_rewind"/(import "asyncify" "start_rewind"/g' cfile.wat
	sed -i 's/(import "env" "stop_rewind"/(import "asyncify" "stop_rewind"/g' cfile.wat
	wat2wasm -o cfile.wasm cfile.wat
	wasm-opt --asyncify $@ -o $@

%.wasm.b64 : %.wasm
	cat $^ | base64 > $@

c-test.html : template.ht cfile.wasm.b64 wasmtemplate
	./wasmtemplate template.ht cfile.wasm.b64 > $@


wasmtemplate : wasmtemplate.c
	gcc -o $@ $^


clean :
	rm -rf wasmtemplate cfile.wasm.b64 cfile.wasm cfile.wat

clean_all : clean
	rm -rf c-test.html
