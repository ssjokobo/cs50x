# Check4Part

#### Video Demo: https://youtu.be/El6Yfn0GmKw

#### Description:
Inspired by the function "check50" from CS50, Check4Part is a web app that help the user check their 4-part harmony writing in the style of 17th-18th century western European classical music. Check4Part will detect different errors and tell if there is any specific kinds of errors but will not tell exactly where those errors are. With that in mind, Check4Part can help music students make sure their work has no error before submitting their assignments but will not help students locate their mistakes. Teachers can also use this web app too by using Check4Part to see if students' assignments are accurate.

##### Features:
This version 1.0 support all 12 “major” keys from 7 sharps to 7 flats. Minor keys are not supported yet. All 7 triadic diatonic chord of major keys are supported including all the 3 inversions of triad: root position, 1st inversion, 2nd inversion.

Check4Part can detect the following errors:

1. Errors from the Roman numeral of chord progression:
- Retrogression

2. Errors from within the same chord:
- Chord Spelling
- Spacing
- Overlapping
- Range
- Bass & Figured Bass
- Doubling

3. Errors from the part movements between the adjacent chords:
- Parallel 5th & 8th
- Hidden Parallel 5th and 8th
- Leading Tone to Tonic
- Awkward leaping
- Resolution of b5.

##### How to use:
Users will need a web browser to open the web app and will follow instructions of the first 3 pages to see the result on the 4th page as the following steps:

1. Input the key and amount of chords. Only possible keys are from 7-flat to 7-sharp keys: "B#", "E#", "A#", "D#", "G#", "C#", "F#", "B", "E", "A", "D", "G", "C", "F", "Bb", "Eb", "Ab", "Db", "Gb", "Cb", and "Fb". Amount of chords are 1-12 chords.
2. Input the figured bass via Roman numeral and inversion number. Possible roman numerals are I, ii, iii, IV, V, vi, viio. And possible inversions are root position, 1st inversion, and 2nd inversion.
3. At this point, if there is any retrogression error from the figured bass, the web app will show them all now. The next step is to input the 4-part harmony following the indicated format: PitchOctave (Eb5, C4, D#3, G5). Check4Part will reject any wrong formatting input and any pitch outside of the major scale from the selected key. The possible range is according to 88 piano keys from A1 to C8. Any input beyond this list will be rejected.
4. See the result. If the web app found any specific types of errors, they will be shown wil ":( Found". If any specific types of errors are not found, the web app will show ":) None".

##### Technologies:
- Flask
- Bootstrap
- Python
- HTML
- CSS

##### Collaborators:
This is a solo project by Sopon Suwannakit.

##### License:
The project is still in development and is not ready for public use yet.

##### Project Status:
Version 1.0 Development