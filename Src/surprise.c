#include "surprise.h"
#include "motors.h"
#include "stm32f4xx_hal.h"

typedef struct note {
	float duration;
	float frequency;
} note;

// Guess the song from the frequencies ;)
note song[] = {

		{1.0/4        ,    195.998},
		{1.0/4        ,    195.998},
		{1.0/4        ,    195.998},
		{3.0/16       ,    155.563},
		{1.0/16       ,    233.082},

		{1.0/4        ,    195.998},
		{3.0/16       ,    155.563},
		{1.0/16       ,    233.082},
		{1.0/2        ,    195.998},

		{1.0/4        ,    293.665},
		{1.0/4        ,    293.665},
		{1.0/4        ,    293.665},
		{3.0/16       ,    311.127},
		{1.0/16       ,    233.082},

		{1.0/4        ,    184.997},
		{3.0/16       ,    155.563},
		{1.0/16       ,    233.082},
		{1.0/2        ,    195.998},

		{1.0/4        ,    391.995},
		{3.0/16       ,    195.998},
		{1.0/16       ,    195.998},
		{1.0/4        ,    391.995},
		{3.0/16       ,    369.994},
		{1.0/16       ,    349.228},

		{1.0/16       ,    329.628},
		{1.0/16       ,    311.127},
		{1.0/8        ,    329.628},
		{1.0/8        ,    150000 },
		{1.0/8        ,    207.652},
		{1.0/4        ,    277.183},
		{3.0/16       ,    261.626},
		{1.0/16       ,    246.942},

		{1.0/16       ,    261.626},
		{1.0/16       ,    246.942},
		{1.0/8        ,    261.626},
		{1.0/8        ,    150000 },
		{1.0/8        ,    155.563},
		{1.0/4        ,    195.998},
		{3.0/16       ,    155.563},
		{1.0/16       ,    195.998},

		{1.0/4        ,    233.082},
		{3.0/16       ,    195.998},
		{1.0/16       ,    233.082},
		{1.0/2        ,    293.665},

		{1.0/4        ,    391.995},
		{3.0/16       ,    195.998},
		{1.0/16       ,    195.998},
		{1.0/4        ,    391.995},
		{3.0/16       ,    369.994},
		{1.0/16       ,    249.228},

		{1.0/16       ,    329.628},
		{1.0/16       ,    311.127},
		{1.0/8        ,    329.628},
		{1.0/8        ,    150000 },
		{1.0/8        ,    207.652},
		{1.0/4        ,    277.183},
		{3.0/16       ,    261.626},
		{1.0/16       ,    246.942},

		{1.0/16       ,    261.626},
		{1.0/16       ,    246.942},
		{1.0/8        ,    261.626},
		{1.0/8        ,    150000 },
		{1.0/8        ,    155.563},
		{1.0/4        ,    195.998},
		{3.0/16       ,    155.563},
		{1.0/16       ,    195.998},

		{1.0/4        ,    233.082},
		{3.0/16       ,    155.563},
		{1.0/16       ,    233.082},
		{1.0/2        ,    195.998},

		{0			,	0}			// End of song indicator

};

uint8_t active = 0;
float tempo = 3;
uint32_t lastTick;
note* currentNote;
float currentNoteDuration;

void initSurprise() {
	active = 1;
	currentNote = song;
	currentNoteDuration = currentNote->duration * tempo * 1000;
	lastTick = HAL_GetTick();

	PWM_SetFrequency(currentNote->frequency);
}

void advanceNote() {
	if (!active) return;
	if ((HAL_GetTick() - lastTick) < currentNoteDuration) return;

	// Advance the note and wrap to beginning if necessary
	currentNote ++;
	if (currentNote->duration == 0 && currentNote->frequency == 0)
		currentNote = song;

	currentNoteDuration = currentNote->duration * tempo * 1000;
	lastTick = HAL_GetTick();
	PWM_SetFrequency(currentNote->frequency);
}
