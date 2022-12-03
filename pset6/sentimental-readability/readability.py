# TODO
from cs50 import get_string


def main():
    # input
    text = get_string("Text: ")

    # function calls
    l = count_letters(text)
    w = count_words(text)
    s = count_sentences(text)

    # grading
    grade = 0.0588 * (l * 100 / w) - 0.296 * (s * 100 / w) - 15.8
    grade = round(grade)

    # printing
    if grade < 1:
        print("Before Grade 1")
    elif grade >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {grade:.2f}")


# count letters
def count_letters(text):
    counter = 0
    for letter in text:
        if letter.isalpha():
            counter += 1
    return counter


# count words
def count_words(text):
    counter = 0
    for letter in text:
        if letter == " ":
            counter += 1

    # adjusting counter
    if len(text) != 0:
        counter += 1
    return counter


# count sentences
def count_sentences(text):
    counter = 0
    for letter in text:
        if letter == "." or letter == "?" or letter == "!":
            counter += 1
    return counter


main()