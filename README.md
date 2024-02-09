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

- [x] tl::expected
- [x] Error type
- [x] Null type
- [x] Number type
- [x] Value types
- [ ] Value node type
- [ ] Object node type
- [ ] Array node type
- [ ] Tree Node
- [ ] Data tree