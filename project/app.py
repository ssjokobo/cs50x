from flask import Flask, render_template, request
from helpers import cycle, avail_fb, inversions, generate_scale, check_progression, check_spell, check_space_overlap, check_range, check_bass, check_parallel, check_hidden, check_doub, check_leadt, check_dissb5, check_leap, check_bass_leap


app = Flask(__name__)


# Prep of general information
data = {}


# Getting key and amount of chords
@app.route("/", methods=["GET"])
def index():
    if request.method == "GET":
        data = {}
        return render_template("index.html", keys=cycle[5:20])


# Getting figured bass
@app.route("/roman", methods=["GET"])
def roman():
    if request.method == "GET":
        data["key"] = request.args.get("key")
        data["amount"] = int(request.args.get("amount"))

        return render_template("roman.html", key=data["key"], amount=data["amount"],
               avail_fb=list(avail_fb.keys()), inversions=inversions)


# Getting four-part
@app.route("/input", methods=["GET"])
def input():
    if request.method == "GET":
        data["fb"] = []
        for i in range(data["amount"]):
            data["fb"].append({"num": "", "inv": ""})
            data["fb"][i]["num"] = request.args.get(f"fb{i}")
            data["fb"][i]["inv"] = request.args.get(f"inv{i}")
        retrogression = check_progression(data["fb"])
        return render_template("input.html", key=data["key"], amount=data["amount"],
               fb=data["fb"], retrogression=retrogression)


# execution
@app.route("/check", methods=["GET"])
def check():

    # prep to store errors in different types
    errors = {
        "spell": [],
        "space": [],
        "overlap": [],
        "range": [],
        "bass": [],
        "doub": [],
        "parallel": [],
        "hidden": [],
        "leadt": [],
        "leap": [],
        "ttleap": [],
        "b7leap": [],
        "dissb5": []
    }

    invalid = False

    if request.method == "GET":

        # get the major scale of the key
        scale = generate_scale(data["key"])
        data["chords"] = []

        # formatting each chord
        for i in range(data["amount"]):
            temp = []
            temp.append(request.args.get(f"s{i}"))
            temp.append(request.args.get(f"a{i}"))
            temp.append(request.args.get(f"t{i}"))
            temp.append(request.args.get(f"b{i}"))
            for j in temp:
                if j[-1] == '8' and j[:-1] in ['A', 'A#', 'Bb', 'B', 'Cb', 'B#', 'C']:
                    continue
                elif j[:-1] not in scale or int(j[-1]) not in list(range(1, 8)):
                    invalid = True
            data["chords"].append(temp)

        if not invalid:

            # run through each chord by itself
            for i in range(data["amount"]):

                # cheking misspelling
                if not check_spell(data["chords"][i], data["fb"][i], scale):
                    errors["spell"].append(i)

                # checking for spacing or overlaping
                check_so = check_space_overlap(data["chords"][i])
                if check_so == 1:
                    errors["space"].append(i)
                elif check_so == 2:
                    errors["overlap"].append(i)

                # checking for range
                if not check_range(data["chords"][i]):
                    errors["range"].append(i)

                # checking for bass
                if not check_bass(data["chords"][i][3], data["fb"][i], scale):
                    errors["bass"].append(i)

                # cheking misspelling
                if not check_doub(data["chords"][i], data["fb"][i], scale):
                    errors["doub"].append(i)

            # run through each adjacents chords in pair
            for i in range(data["amount"] - 1):

                # checking for parallel
                if not check_parallel(data["chords"][i], data["chords"][i + 1], scale):
                    errors["parallel"].append(i)

                if not check_hidden(data["chords"][i], data["chords"][i + 1]):
                    errors["hidden"].append(i)

                if data["fb"][i]["num"] in ['V', 'viio'] and data["fb"][i + 1]["num"] in ['I', 'vi']:
                    if not check_leadt(data["chords"][i], data["chords"][i + 1], scale):
                        errors["leadt"].append(i)

                if data["fb"][i]["num"] in ['viio'] and data["fb"][i + 1]["num"] in ['I', 'iii', 'vi']:
                    if not check_dissb5(data["chords"][i], data["chords"][i + 1], scale):
                        errors["dissb5"].append(i)

                leap = check_leap(data["chords"][i][1:3], data["chords"][i + 1][1:3])
                if leap == 1:
                    errors["leap"].append(i)
                elif leap == 2:
                    errors["ttleap"].append(i)

                if not check_bass_leap(data["chords"][i][3], data["chords"][i + 1][3]):
                    errors["b7leap"].append(i)

        return render_template("check.html", key=data["key"], amount=data["amount"],
               fb=data["fb"], chords=data["chords"], invalid=invalid, errors=errors, data=data, scale=scale)
