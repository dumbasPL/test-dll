# test dll

This project provides a simple "victim" executable that prints "I'm fine!" in a 
loop and a simple "hook" dll that once injected into the victim replaces the 
"I'm fine!" message with "I'm an evil hook!". I's designed for quick testing of
DLL injectors.

## Building

```bash
cmake -B build
cmake --build build
```

or use your favorite IDE with a CMake integration.