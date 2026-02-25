/* 
 * PawnPlus Task Binding
 * Version: 0.2
 * Author: Kanaru Yuuki
 *
 * Description: 
 *   This binding task will ensure your existing task exists when the identifier exists in the server
 *   For now it's only supporting player, next version will support custom callback instead of this.
 *
 * Contributors:
 *   Kanaru Yuuki 
 *
 * ----------------------------------------------------------------------------------
 * MIT License
 * Copyright (c) 2026 Naru
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * ----------------------------------------------------------------------------------
*/

#if !defined _PawnPlus_included
    #error You need to include PawnPlus.inc before this.
#endif

static
    bool:PPBind_g_sSuppressed = false;

// Main function
stock Task:task_bind_player(playerid, Task:currentTask)
{
    if (!task_valid(currentTask))
    {
        return INVALID_TASK; 
    }

    if (!IsPlayerConnected(playerid))
    {
        PPBind_g_sSuppressed = true;
        task_set_error_ms(currentTask, amx_err_exit, 0);
        return currentTask;
    }

    new CallbackHandler:onError = pawn_register_callback("OnPlayerDisconnect", "TaskBindTriggered", _, "edd", currentTask, playerid);
    task_continue_with(currentTask, "TaskBindFinished", "i", _:onError);
    return currentTask;
}

// Handlers
public TaskBindFinished(CallbackHandler:h)
{
    pawn_unregister_callback(h);
    return 0;
}

public TaskBindTriggered(CallbackHandler:h, Task:t, holder, playerid, reason)
{
    if (holder == playerid)
    {
        pawn_unregister_callback(h);
        if (!task_valid(t)) return 0;
        if (task_completed(t)) return 0;

        PPBind_g_sSuppressed = true;

        if (task_state(t) == task_state_faulted) return 0;
        task_set_error_ms(t, amx_err_exit, 0);
    }
    return 0;
}

#if !defined CRASHDETECT_INC
forward OnRuntimeError(code, &bool:suppress);
#endif
public OnRuntimeError(code, &bool:suppress)
{
#if defined PPTB_OnRuntimeError
    new ret = PPTB_OnRuntimeError(code, suppress);

    if (suppress)
    {
        PPBind_g_sSuppressed = false;
        return ret;
    }
#else
    new ret = 1;
#endif

    suppress = PPBind_g_sSuppressed;
    PPBind_g_sSuppressed = false;
    return ret;
}

// Misc
#if defined _ALS_OnRuntimeError
    #undef OnRuntimeError
#else
    #define _ALS_OnRuntimeError
#endif
#define OnRuntimeError PPTB_OnRuntimeError

#if defined PPTB_OnRuntimeError
    forward PPTB_OnRuntimeError(playerid);
#endif

forward TaskBindFinished(CallbackHandler:h);
forward TaskBindTriggered(CallbackHandler:h, Task:t, holder, playerid, reason);
