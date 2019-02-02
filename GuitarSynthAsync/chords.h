// -----------------------------------------------------------------------------
// Guitar chords from the Teensy audio lib tutorial
//
// according to http://www.guitar-chords.org.uk/
// and http://www.8notes.com/guitar_chord_chart/c.asp
// The equation for note to frequency is:
// float freq = 440.0f * exp2f((float)(note - 69) * 0.0833333f);
//
// Extended by 7th chords. Dominant 7th chords are named "V7" to avoid name clashes

#define NOTE_E2   82.41
#define NOTE_F2   87.31
#define NOTE_Fs2  92.50
#define NOTE_G2   98.00
#define NOTE_Gs2 103.82
#define NOTE_A2  110.00
#define NOTE_As2 116.54
#define NOTE_B2  123.47
#define NOTE_C3  130.81
#define NOTE_Cs3 138.59
#define NOTE_D3  146.83
#define NOTE_Ds3 155.56
#define NOTE_E3  164.81
#define NOTE_F3  174.61
#define NOTE_Fs3 185.00
#define NOTE_G3  196.00
#define NOTE_Gs3 207.65
#define NOTE_A3  220.00
#define NOTE_As3 233.08
#define NOTE_B3  246.94
#define NOTE_C4  261.63
#define NOTE_Cs4 277.18
#define NOTE_D4  293.66
#define NOTE_Ds4 311.13
#define NOTE_E4  329.63
#define NOTE_F4  349.23
#define NOTE_Fs4 369.99
#define NOTE_G4  392.00
#define NOTE_Gs4 415.30
#define NOTE_A4  440.00
#define NOTE_As4 466.16
#define NOTE_B4  493.88


               // open =   NOTE_E2  NOTE_A2  NOTE_D3  NOTE_G3  NOTE_B3  NOTE_E4

const float CMaj[6]    = {       0, NOTE_C3, NOTE_E3, NOTE_G3, NOTE_C4, NOTE_E4 };
const float CMaj7[6]   = {       0, NOTE_C3, NOTE_E3, NOTE_G3, NOTE_B3, NOTE_E4 };
const float CV7[6]     = {       0, NOTE_C3, NOTE_E3, NOTE_As3,NOTE_C4, NOTE_E4 };
const float Cm[6]      = {       0, NOTE_C3, NOTE_G3, NOTE_C4, NOTE_Ds4,NOTE_G4 };
const float Cm7[6]     = {       0,       0, NOTE_Ds3,NOTE_As3,NOTE_C4, NOTE_G4 };
const float Cm9[6]     = {       0, NOTE_C3, NOTE_D3, NOTE_As3,NOTE_Ds4,NOTE_G4 };
const float CMaj13[6]  = {       0, NOTE_C3, NOTE_F3, NOTE_A3, NOTE_B3, NOTE_E4 };
const float Cm7b5[6]   = {       0, NOTE_C3, NOTE_Fs3,NOTE_As3,NOTE_Ds4,      0 };

const float DbMaj[6]   = {       0,       0, NOTE_F3, NOTE_Gs3,NOTE_Cs4,NOTE_F4 };
const float DbMaj7[6]  = { NOTE_F2, NOTE_Cs3,NOTE_F3, NOTE_Gs3,NOTE_C4, NOTE_F4 };
const float DbV7[6]    = {       0, NOTE_Cs3,NOTE_F3, NOTE_B3, NOTE_Cs4,      0 };
const float Dbm[6]     = {       0,       0, NOTE_E3, NOTE_Gs3,NOTE_Cs4,NOTE_E4 };
const float Dbm7[6]    = {       0, NOTE_Cs3,NOTE_E3, NOTE_B3, NOTE_E4,       0 };
const float Dbm9[6]    = {       0, NOTE_Cs3,NOTE_Ds3,NOTE_Gs3,NOTE_B3, NOTE_E4 };
const float DbMaj13[6] = { NOTE_F2, NOTE_Cs3,NOTE_Fs3,NOTE_As3,NOTE_C4, NOTE_F4 };
const float Dbm7b5[6]  = {       0, NOTE_B3, NOTE_E3, NOTE_G3, NOTE_Cs4,NOTE_E4 };

const float DMaj[6]    = {       0,       0, NOTE_D3, NOTE_A3, NOTE_D4, NOTE_Fs4};
const float DMaj7[6]   = {       0, NOTE_D3, NOTE_Fs3,NOTE_A3, NOTE_Cs4,NOTE_Fs4};
const float DV7[6]     = {       0,       0, NOTE_D3, NOTE_A3, NOTE_C4, NOTE_Fs4};
const float Dm[6]      = {       0,       0, NOTE_D3, NOTE_A3, NOTE_D4, NOTE_F4 };
const float Dm7[6]     = {       0,       0, NOTE_D3, NOTE_A3, NOTE_C4, NOTE_F4 };
const float Dm9[6]     = {       0, NOTE_D3, NOTE_F3, NOTE_A3, NOTE_C4, NOTE_E4 };
const float DMaj13[6]  = {       0, NOTE_D3, NOTE_Fs3,NOTE_Cs4,NOTE_B3, NOTE_G4 };
const float Dm7b5[6]   = {       0,       0, NOTE_D3, NOTE_Gs3,NOTE_C4, NOTE_F4 };

const float EbMaj[6]   = {       0,       0, NOTE_G3, NOTE_As3,NOTE_Ds4,NOTE_G4 };
const float EbMaj7[6]  = {       0,       0, NOTE_Ds3,NOTE_As3,NOTE_D4, NOTE_G4 };
const float EbV7[6]    = {       0, NOTE_As2,NOTE_Ds3,NOTE_As3,NOTE_Cs4,NOTE_G4 };
const float Ebm[6]     = {       0,       0, NOTE_Fs3,NOTE_As3,NOTE_Ds4,NOTE_Fs4};
const float Ebm7[6]    = {       0,       0, NOTE_Ds3,NOTE_As3,NOTE_Cs4,NOTE_Fs4};
const float Ebm9[6]    = { NOTE_F2, NOTE_As2,NOTE_Ds3,NOTE_As3,NOTE_Cs4,NOTE_Fs4};
const float EbMaj13[6] = { NOTE_G2, NOTE_C3, NOTE_D3, NOTE_G3, NOTE_Ds4,NOTE_Gs4};
const float Ebm7b5[6]  = {       0,       0, NOTE_Ds3,NOTE_A3, NOTE_Cs4,NOTE_Fs4};

const float EMaj[6]    = { NOTE_E2, NOTE_B2, NOTE_E3, NOTE_Gs3,NOTE_B3, NOTE_E4 };
const float EMaj7[6]   = { NOTE_E2, NOTE_B2, NOTE_Ds3,NOTE_Gs3,NOTE_B3, NOTE_E4 };
const float EV7[6]     = { NOTE_E2, NOTE_B2, NOTE_D3, NOTE_Gs3,NOTE_B3, NOTE_E4 };
const float Em[6]      = { NOTE_E2, NOTE_B2, NOTE_E3, NOTE_G3, NOTE_B3, NOTE_E4 };
const float Em7[6]     = { NOTE_E2, NOTE_B2, NOTE_E3, NOTE_G3, NOTE_D4, NOTE_E4 };
const float Em9[6]     = { NOTE_E2, NOTE_D3, NOTE_Fs3,NOTE_G3, NOTE_B3, NOTE_E4 };
const float EMaj11[6]  = { NOTE_E2, NOTE_A2, NOTE_E3, NOTE_Gs3,NOTE_D4, NOTE_Fs4};
const float EMaj13[6]  = { NOTE_E2, NOTE_A2, NOTE_Ds3,NOTE_Gs3,NOTE_Cs4,NOTE_E4 };
const float Em7b5[6]   = {       0,       0, NOTE_E3, NOTE_As3,NOTE_D4, NOTE_G4 };
//const float E11[6]     = { NOTE_Gs2,NOTE_Cs3,NOTE_Gs3,NOTE_B3, NOTE_E4, NOTE_A4 };

const float FMaj[6]    = {       0, NOTE_A2, NOTE_F3, NOTE_A3, NOTE_C4, NOTE_F4 };
const float FMaj7[6]   = {       0, NOTE_A2, NOTE_F3, NOTE_A3, NOTE_C4, NOTE_E4 };
const float FV7[6]     = { NOTE_F2, NOTE_A2, NOTE_Ds3,NOTE_A3, NOTE_C4,       0 };
const float Fm[6]      = { NOTE_F2, NOTE_C3, NOTE_F3, NOTE_Gs3,NOTE_C4, NOTE_F4 };
const float Fm7[6]     = { NOTE_F2, NOTE_C3, NOTE_Ds3,NOTE_Gs3,NOTE_C4, NOTE_F4 };
const float Fm9[6]     = { NOTE_F2, NOTE_C3, NOTE_Ds3,NOTE_Gs3,NOTE_C4, NOTE_G4 };
const float FMaj13[6]  = { NOTE_F2, NOTE_A2, NOTE_D3, NOTE_As3,NOTE_D4, NOTE_E4 };
const float Fm7b5[6]   = {       0,       0, NOTE_F3, NOTE_B3, NOTE_Ds4,NOTE_Gs4};

const float GbMaj[6]   = { NOTE_Fs2,NOTE_Cs3,NOTE_Fs3,NOTE_As3,NOTE_Cs4,NOTE_Fs4};
const float GbMaj7[6]  = {       0,       0, NOTE_Fs3,NOTE_As3,NOTE_Cs4,NOTE_F4 };
const float GbV7[6]    = {       0,       0, NOTE_Fs3,NOTE_As3,NOTE_Cs4,NOTE_E4 };
const float Gbm[6]     = { NOTE_Fs2,NOTE_Cs3,NOTE_Fs3,NOTE_A3, NOTE_Cs4,NOTE_Fs4};
const float Gbm7[6]    = { NOTE_Fs2,NOTE_Cs3,NOTE_E3, NOTE_A3, NOTE_Cs4,NOTE_Fs4};
const float Gbm9[6]    = { NOTE_Fs2,NOTE_A2, NOTE_E3, NOTE_Gs3,NOTE_Cs4,      0 };
const float GbMaj13[6] = { NOTE_Fs2,NOTE_As2,NOTE_Ds3,NOTE_B3, NOTE_Ds4,NOTE_F4 };
const float Gbm7b5[6]  = {       0,       0, NOTE_E3, NOTE_A3, NOTE_C4, NOTE_Fs4};

const float GMaj[6]    = { NOTE_G2, NOTE_B2, NOTE_D3, NOTE_G3, NOTE_B3, NOTE_G4 };
const float GMaj7[6]   = { NOTE_G2, NOTE_B2, NOTE_D3, NOTE_G3, NOTE_B3, NOTE_Fs4};
const float GV7[6]     = { NOTE_G2, NOTE_B2, NOTE_D3, NOTE_G3, NOTE_B3, NOTE_F4 };
const float Gm[6]      = { NOTE_G2, NOTE_D3, NOTE_G3, NOTE_As3,NOTE_D3, NOTE_G4 };
const float Gm7[6]     = { NOTE_F2, NOTE_As2,NOTE_D3, NOTE_G3, NOTE_D4,       0 };
const float Gm9[6]     = { NOTE_G2, NOTE_A2, NOTE_D3, NOTE_As3,NOTE_D4, NOTE_F4 };
const float GMaj13[6]  = { NOTE_G2, NOTE_C3, NOTE_Fs3,NOTE_G3, NOTE_B3, NOTE_E4 };
const float Gm7b5[6]   = {       0,       0, NOTE_G3, NOTE_Cs4,NOTE_F4, NOTE_As4};

const float AbMaj[6]   = { NOTE_Gs2,NOTE_Ds3,NOTE_Gs3,NOTE_C4, NOTE_Ds4,NOTE_Gs4};
const float AbMaj7[6]  = {       0,       0, NOTE_Ds3,NOTE_Gs3,NOTE_C4, NOTE_G4 };
const float AbV7[6]    = {       0,       0, NOTE_Ds3,NOTE_Gs3,NOTE_C4, NOTE_Fs4};
const float Abm[6]     = { NOTE_Gs2,NOTE_Ds3,NOTE_Gs3,NOTE_B3, NOTE_Ds4,NOTE_Gs4};
const float Abm7[6]    = {       0,       0, NOTE_Ds3,NOTE_Gs3,NOTE_B3, NOTE_Fs4};
const float Abm9[6]    = { NOTE_Gs2,NOTE_Ds3,NOTE_Fs3,NOTE_B3, NOTE_B3, NOTE_As4};
const float AbMaj13[6] = { NOTE_Gs2,NOTE_C3, NOTE_F3, NOTE_Cs4,NOTE_F4, NOTE_G4 };
const float Abm7b5[6]  = {       0,       0, NOTE_Gs3,NOTE_D4, NOTE_Fs4,NOTE_B4 };

const float AMaj[6]    = {       0, NOTE_A2, NOTE_E3, NOTE_A3, NOTE_Cs4,NOTE_E4 };
const float AMaj7[6]   = {       0, NOTE_A2, NOTE_E3, NOTE_Gs3,NOTE_Cs4,NOTE_E4 };
const float AV7[6]     = {       0, NOTE_A2, NOTE_E3, NOTE_G3, NOTE_Cs4,NOTE_E4 };
const float Am[6]      = {       0, NOTE_A2, NOTE_E3, NOTE_A3, NOTE_C4, NOTE_E4 };
const float Am7[6]     = {       0, NOTE_A2, NOTE_E3, NOTE_G3, NOTE_C4, NOTE_E4 };
const float Am9[6]     = { NOTE_A2, NOTE_C3, NOTE_G3, NOTE_G3, NOTE_B3, NOTE_E4 };
const float AMaj13[6]  = {       0, NOTE_A2, NOTE_D3, NOTE_Gs3,NOTE_Cs4,NOTE_Fs4};
const float Am7b5[6]   = {       0,       0, NOTE_Ds3,NOTE_A3, NOTE_C4, NOTE_G4 };

const float BbMaj[6]   = {       0, NOTE_As2,NOTE_F3, NOTE_As3,NOTE_D4, NOTE_F4 };
const float BbMaj7[6]  = {       0, NOTE_As2,NOTE_F3, NOTE_A3, NOTE_D4, NOTE_F4 };
const float BbV7[6]    = {       0, NOTE_As2,NOTE_F3, NOTE_Gs3,NOTE_D4, NOTE_F4 };
const float Bbm[6]     = {       0, NOTE_As2,NOTE_F3, NOTE_As3,NOTE_Cs4,NOTE_F4 };
const float Bbm7[6]    = {       0, NOTE_As2,NOTE_F3, NOTE_Gs3,NOTE_Cs4,NOTE_F4 };
const float Bbm9[6]    = { NOTE_As2,NOTE_F3, NOTE_Gs3,NOTE_Cs4,NOTE_F4,       0 };
const float BbMaj13[6] = {       0, NOTE_As2,NOTE_D3, NOTE_Gs3,NOTE_Ds4,NOTE_G4 };
const float Bbm7b5[6]  = { NOTE_As2,NOTE_E3, NOTE_Gs3,NOTE_Cs4,NOTE_Gs4,NOTE_As4};

const float BMaj[6]    = {       0, NOTE_B2, NOTE_Fs3,NOTE_B3, NOTE_Ds4,NOTE_Fs4};
const float BMaj7[6]   = {       0, NOTE_B2, NOTE_Fs3,NOTE_As3,NOTE_Ds4,NOTE_Fs4};
const float BV7[6]     = {       0, NOTE_B2, NOTE_Ds3,NOTE_A3, NOTE_B3, NOTE_Fs4};
const float Bm[6]      = {       0, NOTE_B2, NOTE_Fs3,NOTE_B3, NOTE_D4, NOTE_Fs4};
const float Bm7[6]     = {       0, NOTE_B2, NOTE_Fs3,NOTE_A3, NOTE_D4, NOTE_Fs4};
const float Bm9[6]     = {       0, NOTE_B2, NOTE_D3, NOTE_A3, NOTE_Cs4,NOTE_Fs4};
const float BMaj13[6]  = {       0, NOTE_B2, NOTE_Gs3,NOTE_As3,NOTE_Ds4,NOTE_E4 };
const float Bm7b5[6]   = { NOTE_F2, NOTE_B2, NOTE_F3, NOTE_A3, NOTE_D4, NOTE_F4 };


const float* chordMap[12][7] = {
/*  0: E  */  { Dbm7,   Ebm7b5, EMaj,   Gbm7,   AbV7,   AMaj7,  BV7    },
/*  1: A  */  { DbV7,   DMaj7,  EV7,    Gbm7,   Abm7b5, AMaj7,  Bm7    },
/*  2: D  */  { Dbm7b5, DMaj7,  Em7,    GbV7,   GMaj7,  AV7,    Bm7    },
/*  3: G  */  { CMaj7,  DV7,    Em7,    Gbm7b5, GMaj7,  Am7,    BV7    },
/*  4: C  */  { CMaj7,  Dm7,    EV7,    FMaj7,  GV7,    Am7,    Bm7b5  },
/*  5: F  */  { CV7,    Dm7,    Em7b5,  FMaj7,  Gm7,    AV7,    BbMaj7 },
/*  6: Bb */  { Cm7,    DV7,    EbMaj7, FV7,    Gm7,    Am7b5,  BbMaj7 },
/*  7: Eb */  { Cm7,    Dm7b5,  EbMaj7, Fm7,    GV7,    AbMaj7, BbV7   },
/*  8: Ab */  { CV7,    DbMaj7, EbV7,   Fm7,    Gm7b5,  AbMaj7, Bbm7   },
/*  9: Db */  { Cm7b5,  DbMaj7, Ebm7,   FV7,    GbMaj7, AbV7,   Bbm7   },
/* 10: F# */  { BMaj7,  DbV7,   Ebm7,   Fm7b5,  GbMaj7, Abm7,   BbV7   },
/* 11: B  */  { BMaj7,  Dbm7,   EbV7,   EMaj7,  GbV7,   Abm7,   Bbm7b5 }
};


//                   E2, F2, F2#, G2, G2#, A2, A2#, B2
// C3, C3#, D3, D3#, E3, F3, F3#, G3, G3#, A3, A3#, B3
// C4, C4#, D4, D4#, E4, F4, F4#, G4, G4#, A4, A4#, B4


