# TODO
from cs50 import get_int
from math import floor


def main():
    # input
    card = get_int("Number: ")
    if not isCard(card):
        print("INVALID")
        return

    # check prefix
    firstTwo = int(str(card)[0]) * 10 + int(str(card)[1])
    if firstTwo == 34 or firstTwo == 37:
        print("AMEX")
    elif firstTwo >= 51 and firstTwo <= 55:
        print("MASTERCARD")
    elif floor(firstTwo / 10) == 4:
        print("VISA")
    else:
        print("INVALID")


# check if is a credit card via Luhn's algorithm
def isCard(cardNum):
    cardLen = len(str(cardNum))
    cardSum = 0

    # process even index
    for digit in range(cardLen - 2, -1, -2):
        adding = int(str(cardNum)[digit]) * 2
        if adding > 9:
            cardSum += adding % 10 + floor(adding / 10)
        else:
            cardSum += adding

    # process odd index
    for digit in range(cardLen - 1, -1, -2):
        cardSum += int(str(cardNum)[digit])

    # process sum
    if cardSum % 10 == 0:
        return True
    else:
        return False


main()