#ifndef __LAZY_H
#define __LAZY_H

#include <cstring>
#include <functional>
#include <string>
#include <stdexcept>
#include <unordered_map>

#ifndef LAZY_MAX_RET_SIZE
#define LAZY_MAX_RET_SIZE 1024
#endif

namespace __lazy {
  template <typename R, typename ...A>
  R deduce_return_type(R(*)(A...));

  class dynamic {
    public:
      dynamic(void* ptr) {
        memory = ptr;
      }

      template<typename T>
      operator T() const {
        T ret;
        memcpy(&ret, memory, sizeof(T));
        free(memory);
        return ret;
      }

    private:
      void* memory;
  };

  std::unordered_map<size_t, std::unordered_map<std::string, void*>>& ftable() {
    static std::unordered_map<size_t, std::unordered_map<std::string, void*>> ft;
    return ft;
  }

  bool __register_fn(const std::string& key, void* fptr, size_t ret_size) {
    ftable()[ret_size][key] = fptr;
    return true;
  }

  template <size_t N, typename ...A>
  dynamic __fn_result_dynamic(size_t expected_size, void* f, A... args) {
    if (N == expected_size) {
      std::array<unsigned char, N> a = ((std::array<unsigned char, N> (*) (...))f)(args...);
      void* ret = malloc(N);
      memcpy(ret, &a, N);
      return ret;
    }
    else {
      if constexpr(N < LAZY_MAX_RET_SIZE) {
        return __fn_result_dynamic<N + 1>(expected_size, f, args...);
      }
      else {
        throw std::invalid_argument("The return type exceeds " + std::to_string(LAZY_MAX_RET_SIZE) + " bytes. #define LAZY_MAX_RET_SIZE " + std::to_string(expected_size) + " before #include \"lazy.h\" and try again.");
      }
    }
  }

  template <typename ...A>
  dynamic __invoke_fn(const std::string& key, A... args) {
    for (auto pair : ftable()) {
      if (pair.second.find(key) != pair.second.end()) {
        return __fn_result_dynamic<0>(pair.first, pair.second[key], args...);
      }
    }
    throw std::invalid_argument("No registered function '" + key + "'");
  }

  auto __macro_invoke_fn(const std::string& key) {
    return [key](auto ...ps) {
      return __invoke_fn(key, ps...);
    };
  }
}

#define REGISTER_FN(f) \
  namespace __lazy_##f { \
    bool _ = ::__lazy::__register_fn(#f, (void*)f, sizeof(decltype(::__lazy::deduce_return_type(f)))); \
  }

#define FN(f) \
  ::__lazy::__macro_invoke_fn(#f)

#endif
