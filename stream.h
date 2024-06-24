#include <concepts>
#include <ostream>
#include <type_traits>

template <typename T>
concept Store = requires(T t) {
  { t.begin() } -> std::same_as<typename T::iterator>;
  { t.end() } -> std::same_as<typename T::iterator>;
  { t.size() } -> std::integral;
};

template <typename StreamableType>
concept NativeStream = std::is_base_of<std::ostream, StreamableType>::value;

typedef unsigned long long int ProcUnit;

template <NativeStream streamT> class Stream {
public:
  virtual void render(streamT &stream) = 0;
  virtual void prerender(streamT &stream) = 0;
  virtual void RenderHead(streamT &stream) = 0;
  virtual void RenderCorpus(streamT &stream) = 0;
  virtual void RenderTail(streamT &stream) = 0;
};
