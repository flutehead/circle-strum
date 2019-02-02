# circle-strum
A Teensy-based strum synthesizer

Chords can be strummed "down" and "up", and muted with the "stop" button.

Chords are selected with the keyboard buttons. The middle row has the following chords:

I Maj7 - ii m7 - III 7 - IV Maj7 - V 7 - vi m7 - vii m7b5

The keyboard provides the "current" root together with the "previous" one in the circle of fiths (= #) and the "next" one (= b).

|    | I | II | III | IV | V | VI | VII |
|----|----|----|----|----|----|----|----|
|prev|    | 7  | m7 | #m7b5 | Maj7 |  | 7 |
|curr| Maj7 | m7 | 7 | Maj7 | 7 | m7 | m7b5 |
|next| 7 |    | m7b5 |   | m7 | 7 | bMaj7 |

The current root is initially C, and can be adapted with the "fifth up" and "fifth down" buttons. E.g. C --("fifth down")--> G.


