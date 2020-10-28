# wasm_integrated
An eample of how you can fully integrate wasm into a webpage.  No need for feteching or any of that jazz.  What if someone's on a connection with a lot of latency?  What if you want to load a wasm app from your hard drive directly, like double-clicking on the HTML file?  Whelp, this is that.

Check it out live, here: [link](https://cnlohr.github.io/wasm_integrated/c-test.html)

It's a demo of how to integrate the whole shebang into one small HTML file.  Get your small .c file compiled into wasm and loaded without any hocus pocus.

```
# make clean all
rm -rf wasmtemplate cfile.wasm.b64 cfile.wasm
/home/cnlohr/git/emsdk/upstream/emscripten/emcc -o cfile.wasm cfile.c -s EXPORTED_FUNCTIONS='["_testcallback","_add2"]' -s EXPORTED_RUNTIME_METHODS='["ccall", "cwrap"]' -s ERROR_ON_UNDEFINED_SYMBOLS=0
warning: undefined symbol: writeout (referenced by top-level compiled C/C++ code)
cat cfile.wasm | base64 > cfile.wasm.b64
gcc -o wasmtemplate wasmtemplate.c
./wasmtemplate template.ht cfile.wasm.b64 > c-test.html
```
