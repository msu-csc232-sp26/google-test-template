# Deep Dive: Task 3

Our final task is to further _extend_ the behavior of it inherited from the `plain_box<T>` template class. From our UML class diagram, we have one more method to define, namely, the `unlock()` method. To unlock the lock box, one must supply the correct password. If a client attempts to unlock a locked lock box with an incorrect password, the box remains locked. Further, the number of successive failed attempts is incremented. If there are three (3) successive failed attempts to unlock the lock box, it will forever remain locked (i.e., it is locked out by setting the `locked_out_` data member to `true`). Regardless, a failed attempt to unlock the lock box results in a `false` return value.

On the other hand, if a client provides the correct password to unlock the lock box, then the box is unlocked (by setting the `locked_` data member to `false`). Further, upon successfully unlocking the lock box, the previous number of failed attempts (as held by the data member `failed_attempts`) is reset to 0 and the method returns `true`.

Below is a flow chart exemplifying this expected behavior:

![Unlocking Flow Chart](img/unlock-flow-chart.png)
