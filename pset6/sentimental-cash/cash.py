# TODO
from cs50 import get_float
from math import floor


def main():
    # get input
    cents = get_cents()
    cents *= 100

    # calculate quarters
    quarters = cal_quarters(cents)
    cents = cents - quarters * 25

    # calculate dims
    dims = cal_dims(cents)
    cents = cents - dims * 10

    # calculate nickles
    nickels = cal_nickels(cents)
    cents = cents - nickels * 5

    # calculate pennies
    pennies = cal_pennies(cents)
    cents = cents - pennies * 1

    # Sum coins
    coins = quarters + dims + nickels + pennies

    # Print result
    print(f"{coins:.0f}")


def get_cents():
    while True:
        cents = get_float("Change owed: ")
        if cents > 0:
            return cents


def cal_quarters(cents):
    return floor(cents / 25)


def cal_dims(cents):
    return floor(cents / 10)


def cal_nickels(cents):
    return floor(cents / 5)


def cal_pennies(cents):
    return cents


main()