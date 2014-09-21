/*
 * Sierra College Computer Engineering Club
 * Staircase Piano Project
 * author: James Smith
 *
 * This is the Raspberry Pi portion of the piano project, it treats the
 * Arduino as a slave device over I2C and polls the device for its current
 * key state. Each bit of the key state represents one key in the piano.
 * If more keys need to be added we will need to send multiple bytes, so
 * some modifications will need to be made
 *
 * Required libraries: SDL, SDL_mixer, i2c-dev
 */
#include <linux/i2c-dev.h>
#include <stdio.h>
#include <errno.h>
#include <signal.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>

#include "SDL.h"
#include "SDL_mixer.h"

// defs for SDL Mixer
static const int FREQ = 44100;
static const int FORMAT = MIX_DEFAULT_FORMAT;
static const int CHANNELS = 2;
static const int BUFFER = 2048;

// defs for I2C
#define I2C_ADDRESS 0x04
static const char* DEVICE_NAME = "/dev/i2c-1";
// in micro seconds:
static const int i2c_poll_delay = 10000;

#define SOUNDS 8
Mix_Chunk* sounds[SOUNDS];

bool runProgram = true;

bool initSDL();
void quitSDL();

void handleSigInt( int signum )
{
	// We are only registering SIGINT, so that means close the program
	// with control-c
	runProgram = false;
}

void playSound( int index )
{
	int channel = Mix_PlayChannel( index, sounds[index], 0 );
	if( channel == -1 )
	{
		printf( "Error playing sound: %s\n", Mix_GetError() );
	}
}

int main( int argc, char* args[] )
{
	printf( "Starting sccec_stair_piano...\n" );
	// Initialization
	signal( SIGINT, handleSigInt );

	printf( "I2C: Connecting\n" );
	int i2c;
	if( (i2c = open( DEVICE_NAME, O_RDWR )) < 0 )
	{
		printf( "I2C: Failed to access %d\n", DEVICE_NAME );
		exit(1);
	}
	printf("I2C: acquiring buss to 0x%x\n", I2C_ADDRESS);
	if( ioctl( i2c, I2C_SLAVE, I2C_ADDRESS ) < 0 )
	{
		printf( "I2C: Failed to acquire bus access/talk to slave 0x%x\n", I2C_ADDRESS );
		exit(1);
	}
	if( !initSDL() )
	{
		exit(1);
	}

	// Load sound files
	sounds[0] = Mix_LoadWAV( "/home/pi/Projects/stair_piano/sounds/a.wav" );
	sounds[1] = Mix_LoadWAV( "/home/pi/Projects/stair_piano/sounds/b.wav" );

	for( int i = 0; i < SOUNDS; ++i )
	{
		if( !sounds[i] )
		{
			printf( "Error loading sound file %d: %s\n", i, Mix_GetError() );
		}
	}

	// Play a sound to signal that the program has started
	// mostly useful when running this program on boot
	playSound( 0 );

	// Holds the data we read from the arduino over I2C
	unsigned char data[1];

	// Loop until we recieve a SIGINT
	while( runProgram )
	{
		if( read( i2c, data, 1 ) == 1 )
		{
			if( data[0] >= 1 && data[0] <= 8 )
			{
				//printf( "Received %u\n", data[0] );
				playSound( data[0]-1 );
			}
		}
		usleep( i2c_poll_delay );
	}

	// Cleanup time
	close( i2c );
	for( int i = 0; i < SOUNDS; ++i )
	{
		if( sounds[i] )
		{
			Mix_FreeChunk( sounds[i] );
		}
	}

	quitSDL();
	return 0;
}

bool initSDL()
{
        if( SDL_Init( SDL_INIT_AUDIO ) == -1 )
        {
                printf( "Init Error: %s\n", SDL_GetError() );
                return false;
        }
        int initFlags = MIX_INIT_MP3;
        int flags = Mix_Init( initFlags );
        if( initFlags & flags != flags )
        {
                printf( "Error initializing file types: %s\n", Mix_GetError() );
        }

        if( Mix_OpenAudio( FREQ, FORMAT, CHANNELS, BUFFER ) == -1 )
        {
                printf( "Init Audio Error: %s\n", Mix_GetError() );
                return false;
        }
        Mix_AllocateChannels( 16 );
	return true;
}

void quitSDL()
{
	Mix_CloseAudio();
	Mix_Quit();
	SDL_Quit();
}
