while(1):
    inp = input("Height: ")
    if inp.isdigit():
        inp = int(inp)
        if 1 <= inp <= 8:
            break

for i in range(1, inp+1):
    print(" " * (inp - i) + "#" * i)

