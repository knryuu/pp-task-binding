# PawnPlus Task Binding
PawnPlus Task Binding to specific ID (currently support playerid)

## Functions
```c
/*
* Description:
* Will bind the task to OnPlayerDisconnect.
*
* Returns:
* Returns INVALID_TASK when the current task is invalid
* otherwise it will return the current task itself.
*/

forward Task:task_bind_player(playerid, Task:currentTask);
```

# Usage
If `PP_SYNTAX` or `PP_SYNTAX_AWAIT` is defined, await syntax can be used:
```c
await_plr(playerid) mysql_aquery(myHandle, str_format("SELECT ..."));
```
or
```c
await task_bind_player(playerid, mysql_aquery(myHandle, str_format("SELECT ...")));
```

If not using await syntax
```c
task_await(task_bind_player(playerid, mysql_aquery(myHandle, str_format("SELECT ..."))));
```