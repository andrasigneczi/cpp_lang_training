Simple surface for a complex system

--------          --------
|Client|--------->|Facade|
--------          --------
                     /|\
                    / | --
                   /  |   \
------------------/---|----\------------------
|Subsystem      --    |     ---------        |
|              /      |              \       |
|    ----------      ------          ------  |
|    |Obj1|          |Obj2|          |Obj3|  |
|    ------          ------          ------  |
|                                            |
|                                            |
---------------------------------------------|