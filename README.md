# LongLong SAMP
Ну плагин меняет ограничение int32 - 2.147.483.647 до uint64 18,446,744,073,709,551,615
Полезно если игроку надо иметь больше денег, ну крч инфляцияяяя

## Building on Windows

```bash
cd longlong
mkdir build
cd build
cmake .. -A Win32
cmake --build . --config RelWithDebInfo
```
