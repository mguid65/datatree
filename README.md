# datatree

datatree library just for fun

You might look at this and say "That looks like JSON" and you would be correct, but it doesn't matter. I'm only writing this to show that I have something to show and in fact do know how to write C++.

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