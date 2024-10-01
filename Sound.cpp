#include "Header.h"
#include "Global.h"
#include "Sound.h"
#pragma comment(lib, "winmm.lib")
#define _CRT_SECURE_NO_WARNINGS
#define SOUND_HEADER
int CheckSound = 1;
void BackgroundSound() {
	PlaySoundW(TEXT("Audio//Snake_Intro.wav"), NULL, SND_LOOP | SND_ASYNC | SND_FILENAME | SND_NOSTOP); // playloop
}
void ButtonSound() {
	PlaySoundW(TEXT("Audio//buttonSound.wav"), NULL, SND_ASYNC | SND_FILENAME); // play oncebackground
}
void EnterBut() {
	PlaySoundW(TEXT("Audio//Snake_Enter.wav"), NULL, SND_FILENAME | SND_ASYNC);
}
void CountSound() {
	PlaySoundW(TEXT("Audio//Snake_Count.wav"), NULL, SND_FILENAME | SND_ASYNC);
}
void ErrorInput() {
	PlaySoundW(TEXT("Audio//Snake_Error.wav"), NULL, SND_FILENAME | SND_ASYNC);
}
void PassLevel() {
	PlaySoundW(TEXT("Audio//Snake_Pass_Level.wav"), NULL, SND_FILENAME | SND_ASYNC);
}
void gameOver() {
	PlaySoundW(TEXT("Audio//Snake_Lose.wav"), NULL, SND_FILENAME | SND_ASYNC);
}
void EatSound() {
	PlaySoundW(TEXT("Audio//eating.wav"), NULL, SND_FILENAME | SND_ASYNC);
}
void StopSound() {
	PlaySound(NULL, NULL, NULL);
}
void INtroSound() {
	PlaySoundW(TEXT("Audio//Snake_Intro_1.wav"), NULL, SND_ASYNC | SND_FILENAME);
}
void eatBfood() {
	PlaySoundW(TEXT("Audio//Snake_Eat.wav"), NULL, SND_ASYNC | SND_FILENAME);
}
void ExitSound() {
	PlaySoundW(TEXT("Audio//Snake_Credit.wav"), NULL, SND_ASYNC | SND_FILENAME);
}