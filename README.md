# lazy-dispatch
lazy-dispatch defers the lookup of a target function's address until runtime.
This means that a lazy-dispatched function's address doesn't need to be known at compile-time.

Calling a function now requires `sizeof(return_type) + 1` hashtable lookups and a malloc() call, but is that really such a high price to pay for getting rid of that circular dependency?


## Setting up clangd Intellisense
```shell
bazel run @hedron_compile_commands//:refresh_all
```

## Building the project
```shell
bazel build lib:lazy-dispatch
```

## Running the example
```shell
bazel run example:even-odd-example
```

## Usage
Create a function, then register it with `REGISTER_FN(function_name)`

```cpp
#include "lib/lazy.h"

int add(int a, int b) {
    return a + b;
}

REGISTER_FN(add);
```

Call any registered function name with `FN(function_name)(args...)`

```cpp
#include "add.h"
#include <iostream>

int main(void) {
    std::cout << FN(add)(3, 4) << std::endl;
}
```
Neither the arguments nor the return type are checked by the compiler, so don't mess up.

For a complete example, look in [example/](example/)
