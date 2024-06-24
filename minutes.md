```cpp
class StreamType< ContainerType, Keyspace > {
  ContainerType< Keyspace > nodes;
}
```

The ContainerType is a container: `std::vector`, `std::map` etc. It is a template parameter
Keyspace is a parameter pack that is a template parameter

The last parameter of the Keyspace should be checked to see if it has the following functions

```bash
stream();
StreamHead();
StreamCorpus();
StreamTail();
render();
RenderHead();
RenderCorpus();
RenderTail();
```

Streamable Type:

```cpp
template <typename T>
concept Streamable = requires(T t) {
  { t.render() } -> std::same_as<typename Stream::render>;
  { t.stream() } -> std::same_as<typename Stream::stream>;
}
```
