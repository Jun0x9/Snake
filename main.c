#include <raylib.h> 
#define ROWS 32 
#define COLS 32 
#define SIZE 16 
#define BODY_MAX 100
Color BackGround = {140, 204, 63, 255} ; 
Color ForeGround = { 41, 74, 1, 255} ;
const int WIDTH = ROWS * SIZE; 
const int HEIGHT = COLS * SIZE ; 

typedef struct {  int x , y ; } point; 

point GetRandomPos( ){ 
	return (point){GetRandomValue( 0, COLS - 1) * SIZE , GetRandomValue( 0, ROWS - 1) * SIZE }; 
}

int main( void ) {
	InitWindow( WIDTH, HEIGHT, "SnakeGame") ; 
	SetTargetFPS( 30 ) ; 
	point head = { 16 * SIZE, 16 * SIZE }; 
	point vel = { .x = 0 , .y=0 };
	point segments[ BODY_MAX ] ; 

	unsigned int score = 0; 	
	point fruit = GetRandomPos() ; 
	int  ticks = 0;

	while(!WindowShouldClose()){ 
		 	ticks ++; 
			if( IsKeyDown( KEY_RIGHT ) && vel.x != -1 ){
				vel.x = 1; 
				vel.y = 0;
			}
			if( IsKeyDown( KEY_LEFT) && vel.x != 1){ 
				vel.x = -1;
				vel.y =  0; 
			}

			if( IsKeyDown( KEY_UP) && vel.y != 1) { 
				vel.y = -1 ; 
				vel.x = 0 ; 
			}
			if( IsKeyDown( KEY_DOWN) && vel.y != -1){ 
				vel.y = 1 ; 
				vel.x = 0 ;
			}
			if( ticks >= 5){ 
				for(int i = score; i > 0 ; i--) 
					segments[ i ] = ( point ) (segments [ i  - 1 ]) ;
				segments[ 0 ] = ( point ) head;  
				head.x += vel.x  * SIZE ; 
				head.y += vel.y  * SIZE ; 	
				if ( head.x == fruit.x && head.y == fruit.y ){
					fruit = (point) { GetRandomValue(0, COLS - 1) * SIZE, GetRandomValue(0, ROWS - 1) * SIZE}; 
					score++; 
				}
				ticks = 0; 
			}	
			BeginDrawing() ; 
				ClearBackground( BackGround ) ;
				for (int i = 0; i <= score; i++)
					DrawRectangle( segments[i].x, segments[i].y, SIZE, SIZE, ForeGround); 	

				DrawRectangle( fruit.x, fruit.y, SIZE, SIZE, RED);
			EndDrawing(); 
	}
	CloseWindow() ; 
	return 0;
}
