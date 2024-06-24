#include <concepts>
#include <ios>
#include <iostream>
#include <type_traits>

template<typename T>
concept Store = requires(T t) {
 { t.begin() } -> std::same_as<typename T::iterator>;
 { t.end() } -> std::same_as<typename T::iterator>;
 { t.size() } -> std::integral;
};

template<typename T>
 requires std::is_base_of<
									std::basic_ios<typename T::char_type, typename T::traits_type>,
									std::remove_pointer_t<T>>::value
using NativeStream = T;

typedef unsigned long long int ProcUnit;

namespace Approach::Render {
 class Stream {
 public:
	template<typename StreamT>
	void render(NativeStream<StreamT> &stream) {};
	template<typename StreamT>
	void RenderHead(NativeStream<StreamT> &stream) {};
	template<typename StreamT>
	void RenderCorpus(NativeStream<StreamT> &stream) {};
	template<typename StreamT>
	void RenderTail(NativeStream<StreamT> &stream) {};
 };
}// namespace Approach::Render
