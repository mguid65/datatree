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

### Usage

```c++
mguid::DataTree dt1;

// Node types
dt1["first"]["second"]["array"] = mguid::ArrayNodeType{{}, {}, {}, {}};
dt1["first"]["second"]["object"] = mguid::ObjectNodeType{};
dt1["first"]["second"]["value"] = mguid::ValueNodeType{};

// Value types
dt1["first"]["second"]["number_value_signed"] = 1;
dt1["first"]["second"]["number_value_unsigned"] = 1u;
dt1["first"]["second"]["number_value_double"] = 1.0;
dt1["first"]["second"]["bool_value_true"] = true;
dt1["first"]["second"]["bool_value_false"] = false;
dt1["first"]["second"]["null_value"] = mguid::Null;
dt1["first"]["second"]["string_literal_value"] = "Hello, World!";
dt1["first"]["second"]["string_value"] = std::string("42");

// Erase a key in an object node
dt1["first"]["second"].Erase("object");

// Erase an item in an array node
dt1["first"]["second"]["array"].Erase(2);

// Set path to another tree
mguid::DataTree dt2;
dt2["some_key"] = dt1;

// Unsafe API
const mguid::DataTree dt3 = dt1;

// Unsafe

//              Unsafe API
//                   |    
//                   V     
dt1.Unsafe([](auto&& unsafe) {
  // The UnsafeProxy operator[] returns another UnsafeProxy
  auto& second_unsafe_proxy = unsafe["first"]["second"];
  auto& obj1 = unsafe.GetObject();
  auto& obj2 = unsafe.Get<mguid::ObjectNodeType>();
  
  // Access the safe API with the Safe function
  auto& safe = unsafe["first"]["second"].Safe();
});

// ConstUnsafe

//                         Unsafe API
//                              |    
//                              V            
dt3.ConstUnsafe([](const auto&& unsafe) {
  // The UnsafeProxy operator[] returns another UnsafeProxy
  const auto& second_unsafe_proxy = unsafe["first"]["second"];
  const auto& obj1 = unsafe.GetObject();
  const auto& obj2 = unsafe.Get<mguid::ObjectNodeType>();
  
  // Access the safe API with the Safe function
  const auto& safe = unsafe["first"]["second"].Safe();
});

// Provide a second reference parameter to get a reference to the safe API

// Unsafe

//              Unsafe API  Reference to dt1
//                   |             |
//                   V             V        
dt1.Unsafe([](auto&& unsafe, auto& safe) {
  // The UnsafeProxy operator[] returns another UnsafeProxy
  auto& second_unsafe_proxy = unsafe["first"]["second"];
  auto& obj1 = unsafe.GetObject();
  auto& obj2 = unsafe.Get<mguid::ObjectNodeType>();
  
  // Access the safe API with the Safe function
  auto result = safe.TryGetObject();
});

// Const Unsafe

//                         Unsafe API        Reference to dt3
//                              |                   |
//                              V                   V             
dt3.ConstUnsafe([](const auto&& unsafe, const auto& safe) {
  // The UnsafeProxy operator[] returns another UnsafeProxy
  const auto& second_unsafe_proxy = unsafe["first"]["second"];
  const auto& obj1 = unsafe.GetObject();
  const auto& obj2 = unsafe.Get<mguid::ObjectNodeType>();
  
  // Access the safe API with the Safe function
  const auto result = safe.TryGetObject();
});
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
- [x] Data tree
- [ ] Data tree visitor and recursive visitor
- [ ] Serialization/Deserialization

### Experimental

- [ ] Templated Value Type Maybe?
