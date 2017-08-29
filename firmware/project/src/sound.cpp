#include "sound.h"
#include <Arduino.h>
#include <NewTone.h>

float gameOverSoundNotes[] = {note_B3, note_F4, note_F4, note_F4, note_E4, note_D4, note_C4, note_E3, note_E3, note_C3};
int gameOverSoundDurations[] = {162, 162, 162, 162, 217, 217, 217, 162, 162, 162, 162, 162, 5};
Melody gameOverSound = {.length = sizeof(gameOverSoundNotes) / sizeof(float),
                        .notes = gameOverSoundNotes,
                        .durations = gameOverSoundDurations};

float submitMoveSoundNotes[] = {300, 435, 631, 915, 1326, 1923};
int submitMoveSoundDurations[] = {60, 60, 60, 60, 60, 60, 0};
Melody submitMoveSound = {.length = sizeof(submitMoveSoundNotes) / sizeof(float),
                          .notes = submitMoveSoundNotes,
                          .durations = submitMoveSoundDurations};

float startSoundNotes[] = {note_E5, note_G5, note_E6, note_C6, note_D6, note_G6};
int startSoundDurations[] = {130, 130, 130, 130, 130, 130};
Melody startSound = {
    .length = sizeof(startSoundNotes) / sizeof(float), .notes = startSoundNotes, .durations = startSoundDurations};

float winSoundNotes[] = {note_G2, note_C3,  note_E3,  note_G3, note_C4,  note_E4,  note_G4,  note_E4,  note_Ab2,
                         note_C3, note_Eb3, note_Ab3, note_C4, note_Eb4, note_Ab4, note_Eb4, note_Bb2, note_D3,
                         note_F3, note_Bb3, note_D4,  note_F4, note_Bb4, note_B4,  note_B4,  note_B4,  note_C5};
int winSoundDurations[] = {130, 130, 130, 130, 130, 130, 433, 433, 130, 130, 130, 130, 130, 130,
                           433, 433, 130, 130, 130, 130, 130, 130, 433, 130, 130, 130, 650};
Melody winSound = {
    .length = sizeof(winSoundNotes) / sizeof(float), .notes = winSoundNotes, .durations = winSoundDurations};

void sound_setup() {
}  // Nothing to setup, just start playing!

Melody* currentMelody = NULL;

int nextNotePos;
unsigned long nextNoteTime;

bool sound_isPlaying() {
    return currentMelody != NULL;
}

void sound_play(Melody* melody) {
    currentMelody = melody;
    nextNoteTime = millis();
    nextNotePos = 0;
}

int i = 0;

void playNextDemoSound() {
    if (!sound_isPlaying()) {
        switch (i) {
            case 1:
                sound_play(&startSound);
                break;
            case 3:
                sound_play(&gameOverSound);
                break;
            case 2:
                sound_play(&winSound);
                break;
            case 0:
                sound_play(&submitMoveSound);
                break;
        }
        i++;
        if (i == 4)
            i = 0;
    }
}

void sound_loop() {
    //playNextDemoSound();

    if (!currentMelody)
        return;

    if (nextNoteTime > millis())
        return;

    if (nextNotePos >= currentMelody->length) {
        noNewTone();
        currentMelody = NULL;
        return;
    }

    int duration = currentMelody->durations[nextNotePos];
    NewTone(TONE_PIN, currentMelody->notes[nextNotePos], duration);
    nextNoteTime = millis() + duration + 10;
    nextNotePos++;
}