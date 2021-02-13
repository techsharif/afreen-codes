while(1):
    inp = input("Change owed: ")
    try:
        inp = float(inp)
        if inp > 0.0:
            break
    except:
        pass

cents = int(inp * 100)
count = 0

count = count + (cents // 25)
cents = cents % 25

count = count + (cents // 10)
cents = cents % 10

count = count + (cents // 5)
cents = cents % 5

count = count + cents

print(count)

