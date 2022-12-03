# TODO
# Prompting input with checking range
while (True):
    try:
        n = int(input("Height: "))
        if n > 0 and n < 9:
            break
    except ValueError:
        print("Not an integer!")

# Loop
for i in range(n):
    for j in range(n - i - 1):
        print(" ", end="")
    for k in range(i + 1):
        print("#", end="")
    print("  ", end="")
    for k in range(i + 1):
        print("#", end="")
    print()