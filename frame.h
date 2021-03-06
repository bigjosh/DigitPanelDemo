#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include <sys/timerfd.h>
#include <ctype.h>

#include <unistd.h>
#include <string.h>
#include <sys/types.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <arpa/inet.h>

// Command line utility to send a frame of UDP OPC data to a a ledscape listener

#define FRAME_SIZE_X 59
#define FRAME_SIZE_Y 26

#define PIN_COUNT 6

#define ASPECT_RATIO (16.0/23.0)        // Width/heigh (these are the imperical measurements in mm)

typedef struct {
	unsigned char r[FRAME_SIZE_X][FRAME_SIZE_Y];     // Buffer of RGB values
	unsigned char g[FRAME_SIZE_X][FRAME_SIZE_Y];     // Buffer of RGB values
	unsigned char b[FRAME_SIZE_X][FRAME_SIZE_Y];     // Buffer of RGB values
} FRAME;

void sendFrame( OPCSOCKET FRAME *frame ,  )



int main( int argc, char **argv) {
	
	printf("LEDs (c)2016 josh levine [josh.com]\r\n");
    
    if (argc!=7) {
            fprintf(stderr,"Usage  : leds dest_ip  rgb left right top bot \r\n");
            fprintf(stderr,"         RGB color format XXXXXX (FFFFFF=white)\r\n");
            
            fprintf(stderr,"Example: leds 192.168.174.2 0000FF 0 %d  0 %d  = Full panel to blue\r\n", FRAME_SIZE_X , FRAME_SIZE_Y );
            
            return(1);        
    }
	
	printf("dest ip : %s\r\n", argv[1]);
	
    opensocket( argv[1] );
    
	if (sockfd < 0) {
		fprintf( stderr , "ERROR opening socket");    
		return(1);
	}	
    
	printf("Socket established.\r\n");
	
	const char *colorString = argv[2];
	
    unsigned char r1 = parsehexdigits(colorString);
    unsigned char g1 = parsehexdigits(colorString+2);
    unsigned char b1 = parsehexdigits(colorString+4);	
    
    printf( "Color={%X,%X,%X}\r\n" , r1, g1, b1);
    
	unsigned char left 		= atoi( argv[3] );	
	unsigned char right 	= atoi( argv[4] );	
	unsigned char top 		= atoi( argv[5] );	
	unsigned char bottom 	= atoi( argv[6] );	
        
    printf("l=%d r=%d t=%d b=%d\r\n",left,right,top,bottom);
		
   for( int x=left; x< MIN(FRAME_SIZE_X , right)  ; x++) {
        
        for(int y=top;y<= MIN(FRAME_SIZE_Y, bottom) ;y++) {
            
            r[x][y] = r1;
            g[x][y] = g1;
            b[x][y] = b1;
            
            
        }
    }
    
    sendOPCPixels();

	printf("Sent.\r\n");
        
    return(0);
    
}
