cycle = ["B#", "E#", "A#", "D#", "G#", "C#", "F#", "B", "E", "A", "D", "G", "C", "F", "Bb", "Eb", "Ab", "Db", "Gb", "Cb", "Fb"]

avail_fb = {
    'I': [0, 2, 4],
    'ii': [1, 3, 5],
    'iii': [2, 4, 6],
    'IV': [3, 5, 0],
    'V': [4, 6, 1],
    'vi': [5, 0, 2],
    'viio': [6, 1, 3]
}

inversions = ['', '6', '64']

def generate_scale(key):
    idx = cycle.index(key)
    scale = []
    # get the first 3 notes of major scale
    for i in range(3):
        scale.append(cycle[idx - (i * 2)])
    # get the last 4 notes of major scale
    for i in range(4):
        scale.append(cycle[idx + 1 - (i * 2)])
    return scale


def get_score(pitch):
    c_scale = ['C', 'D', 'E', 'F', 'G', 'A', 'B']
    c_score = [3, 5, 7, 8, 10, 12, 14]

    # get score - without accidental
    score = c_score[c_scale.index(pitch[0])] + (int(pitch[-1]) - 1) * 12

    # adjust score per accidental
    if pitch[1] == "b":
        score -= 1
    elif pitch[1] == "#":
        score += 1

    return score


def check_progression(fb):
    statement = []
    subdom = ['ii', 'IV']
    dom = ['V', 'viio']
    for i in range(len(fb) - 1):
        if (fb[i]["num"] in dom or (fb[i]["num"] == 'I' and fb[i]["inv"] == '64')) and fb[i + 1]["num"] in subdom:
            statement.append(f":( Chord #{(i + 1)} ({fb[i]['num']}{fb[i]['inv']}) to Chord #{(i + 2)} ({fb[i + 1]['num']}{fb[i + 1]['inv']}) is Retrogression")
    return statement


def check_spell(chord, fb, scale):
    for pitch in chord:
        idx = scale.index(pitch[:-1])
        if idx not in avail_fb[fb["num"]]:
            return False
    return True


def check_space_overlap(chord):
    for i in range(len(chord) - 1):

        # get score
        score1 = get_score(chord[i])
        score2 = get_score(chord[i + 1])

        # get distance
        distance = score1 - score2

        # if overlap
        if distance < 0:
            return 2

        # if spacing
        elif i != 2 and distance > 12:
            return 1

    return 0


def check_range(chord):
    for i in range(len(chord)):

        # get score
        score = get_score(chord[i])

        # Soprano
        if i == 0 and (score < 39 or score > 58):
            return False

        # Alto
        elif i == 1 and (score < 34 or score > 53):
                return False

        # tenor
        elif i == 2 and (score < 27 or score > 44):
                return False

        # bass
        elif i == 3 and (score < 19 or score > 39):
                return False

    return True


def check_bass(bass, fb, scale):
    if bass[:-1] == scale[avail_fb[fb["num"]][inversions.index(fb["inv"])]]:
        return True
    else:
        return False

def check_doub(chord, fb, scale):

    chord_idx = []

    for pitch in chord:
        chord_idx.append(scale.index(pitch[:-1]))

    # adjust to base form
    for i in range(len(chord_idx)):
        chord_idx[i] = (chord_idx[i] + 7 - avail_fb[fb["num"]][0]) % 7

    chord_idx.sort()

    if fb["num"] == 'viio' and chord_idx != [0, 2, 2, 4]:
        return False

    elif fb["num"] == 'V' and chord_idx == [0, 2, 2 ,4]:
        return False

    elif fb["inv"] == '64' and chord_idx != [0, 2, 4, 4]:
        return False

    elif chord_idx in [[0, 0, 0, 2], [0, 0, 2, 4], [0, 2, 2, 4], [0, 2, 4, 4]]:
        return True


def check_parallel(chord1, chord2, scale):

    # check if pairs in chord2 are P5 or P8
    for i in range(len(chord1) - 1):
        for j in range(len(chord1) - i - 1):
            if chord1[i] != chord2[i] and chord1[j + i + 1] != chord2[j + i + 1]:
                idx1h = scale.index(chord1[i][:-1])
                idx1l = scale.index(chord1[j + i + 1][:-1])
                dist1 = idx1h - idx1l
                if dist1 in [0, 4, -3] and idx1l != 6:
                    idx2h = scale.index(chord2[i][:-1])
                    idx2l = scale.index(chord2[j + i + 1][:-1])
                    dist2 = idx2h - idx2l
                    if dist1 == dist2:
                        return False

    return True


def check_hidden(chord1, chord2):

    score_s1 = get_score(chord1[0])
    score_s2 = get_score(chord2[0])
    score_b1 = get_score(chord1[3])
    score_b2 = get_score(chord2[3])

    # check interval of chord2
    if (score_s2 - score_b2) % 12 in [0, 7]:
        dist_s = score_s1 - score_s2
        dist_b = score_b1 - score_b2
        if dist_s > 0 and dist_b > 0:
            return False
        elif dist_s < 0 and dist_b < 0:
            return False

    return True


def check_leadt(chord1, chord2, scale):
    for i in range(len(chord1)):
        idx1 = scale.index(chord1[i][:-1])
        if idx1 == 6:
            score1 = get_score(chord1[i])
            score2 = get_score(chord2[i])
            if score2 - score1 != 1:
                return False

    return True


def check_leap(chord1, chord2):
    for i in range(len(chord1)):
        score1 = get_score(chord1[i])
        score2 = get_score(chord2[i])
        dist = abs(score1 - score2)
        if dist > 7:
            return 1
        elif dist == 6:
            return 2

    return 0

def check_bass_leap(bass1, bass2):
    score1 = get_score(bass1)
    score2 = get_score(bass2)
    dist = abs(score1 - score2)
    if dist == 11 or dist == 10:
        return False

    return True

def check_dissb5(chord1, chord2, scale):
    for i in range(len(chord1)):
        if scale.index(chord1[i][:-1]) == 3:
            score1 = get_score(chord1[i])
            score2 = get_score(chord2[i])
            if score1 - score2 != 1:
                return False

    return True
