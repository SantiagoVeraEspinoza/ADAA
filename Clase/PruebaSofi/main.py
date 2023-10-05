def towerOfHanoi(n, from_t, to_t, aux_t):
    if n == 0:
        return
    if n == 1:
        if (from_t == "A" and to_t == "C") or (from_t == "C" and to_t == "A"):
            print("Move", from_t, "to", aux_t)
            print("Move", aux_t, "to", to_t)
            return
        print("Move", from_t, "to", to_t)
        return

    if (from_t == "B" and to_t == "A") or (from_t == "B" and to_t == "C"):
        towerOfHanoi(n-1, from_t, aux_t, to_t)
        print("Move", from_t, "to", to_t)
        towerOfHanoi(n-1, aux_t, to_t, from_t)
        return

    towerOfHanoi(n-1, from_t, to_t, aux_t)
    print("Move", from_t, "to", aux_t)
    towerOfHanoi(n-1, to_t, from_t, aux_t)
    print("Move", aux_t, "to", to_t)
    towerOfHanoi(n-1, from_t, to_t, aux_t)

towerOfHanoi(3, "A", "C", "B")
