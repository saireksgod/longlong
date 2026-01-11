# LongLong SAMP
Ну плагин расширяет ограничение int32 - 2.147.483.647 до uint64 18,446,744,073,709,551,615

Полезно если игроку надо иметь больше денег, ну крч инфляцияяяя

## Building on Windows

```bash
cd longlong
mkdir build
cd build
cmake .. -A Win32
cmake --build . --config RelWithDebInfo
```

# exapmple
```
#include <a_samp>
#include <longlong>
#include <Pawn.CMD>

main() {}

enum ePlayerInfo
{
        Name[MAX_PLAYER_NAME],
        Money[stlonglong],
};

new Players[MAX_PLAYERS][ePlayerInfo];

public OnPlayerConnect(playerid)
{
        GetPlayerName(playerid, Players[playerid][Name], MAX_PLAYER_NAME);

        llSetValueString(Players[playerid][Money], "10000000000000000"); // Устанавливаем 10 квадриллионов

        return 1;
}

CMD:mymoney(playerid)
{
        new dest[MAX_LONGLONG_LEN + 15];

        llGetValueString(Players[playerid][Money], dest);

        format(dest, sizeof dest, "Your money: %s", dest);
        SendClientMessage(playerid, -1, dest);
        return 1;
}

CMD:imrich(playerid)
{
        if (llcmpString(Players[playerid][Money], <, "2000000000000000")) return SendClientMessage(playerid, 0xAA0000FF, "YOU NOT RICH!!!");  // Если кол-во денег меньше, чем 2 квадриллиона

        llsubString(Players[playerid][Money], "2000000000000000"); // Забираем 2 квадриллиона
        return 1;
}
```
