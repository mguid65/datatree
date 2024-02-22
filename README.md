# DataTree

DataTree library just for fun

You might look at this and say "that looks like JSON"...

## Build

### Release

```
conan install . -b missing
cmake --preset conan-release
cmake --build --preset conan-release
./build/Release/sample
```

### Debug

```
conan install . -s build_type=Debug -b missing
cmake --preset conan-debug
cmake --build --preset conan-debug
./build/Debug/sample
```

### TODO

- [x] Add expected-lite dependency
- [x] Add stduuid dependency
- [x] Error type
- [x] Null type
- [x] Number type
- [x] Value types
- [x] Value node type
- [x] Object node type
- [x] Array node type
- [x] Tree Node
- [ ] Data tree

### Note

I won't update the library version until I have an MVP of all existing stub classes; a usable data tree.