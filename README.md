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
```c
await task_bind_player(playerid, mysql_aquery(myHandle, str_format("SELECT ...")));
```
