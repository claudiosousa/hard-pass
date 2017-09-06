#include "sound.h"
#include <Arduino.h>
#include <NewTone.h>
#include "settings/settings.h"

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

void sound_setup() {
}  // Nothing to setup, just start playing!

Melody* currentMelody = NULL;

int nextNotePos;
unsigned long nextNoteTime;

bool sound_isPlaying() {
    return currentMelody != NULL;
}

void sound_play(Melody* melody) {
    if (!settings_getSoundIsOn())
        return;
    currentMelody = melody;
    nextNoteTime = millis();
    nextNotePos = 0;
}

float touchNotes[] = {note_C4};
int touchDurations[] = {130};
Melody touchSound = {.length = sizeof(touchNotes) / sizeof(float), .notes = touchNotes, .durations = touchDurations};

float passwordRequestNotes[] = {note_B3, note_F4, note_F4, note_F4, note_E4,
                                note_D4, note_C4, note_E3, note_E3, note_C3};
int passwordRequestDurations[] = {162, 162, 162, 162, 217, 217, 217, 162, 162, 162, 162, 162, 5};
Melody passwordRequestSound = {.length = sizeof(passwordRequestNotes) / sizeof(float),
                               .notes = passwordRequestNotes,
                               .durations = passwordRequestDurations};

void sound_playTouch() {
    sound_play(&touchSound);
}

void sound_passwordRequest() {
    sound_play(&passwordRequestSound);
}

void sound_loop() {
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