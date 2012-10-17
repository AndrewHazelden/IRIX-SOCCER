//-----------------------
//Set up the defines
//-----------------------

#define TOTAL_SOCCER_BALL_FRAMES 15

#define TOTAL_IMAGE_PATH_LENGTH 150

//#define BALL_X_MIN_SPEED 6
#define BALL_X_MIN_SPEED 0
#define BALL_X_MAX_SPEED 12

//#define BALL_Y_MIN_SPEED 3
#define BALL_Y_MIN_SPEED 0
//#define BALL_Y_MAX_SPEED 4
#define BALL_Y_MAX_SPEED 8


//-----------------------
//Set up the functions
//-----------------------

void PrintVersion();
void InitGFX();
void GetInput();
void ResetGame();
void ResetLevel();
void LoadSprites();
void FreeSprites();
void DrawBall(int frame, int x, int y);
static void RenderScreen();
void AnimateFrame();
void SavePrevious();
char IsCollision (unsigned int Shape_X, unsigned int Shape_Y,  unsigned int                  Shape_Width, unsigned int Shape_Height,
                  unsigned int Player_Left, unsigned int Player_Top, unsigned int Player_Width, unsigned int Player_Height);



//-----------------------
//Set up the variables
//-----------------------

//SDL done flag
int done;

//Game sprites
SDL_Surface* grassField = NULL;
SDL_Surface* goalPost = NULL;

//goal scored text image
SDL_Surface* purple_goal = NULL; 
SDL_Surface* yellow_goal = NULL;


//Image object for animated soccer ball sprites
struct frame_object{
       SDL_Surface* image;                  //SDL image
       char name[TOTAL_IMAGE_PATH_LENGTH]; //image filename eg. image.bmp
       };
       
struct frame_object ball_frames[TOTAL_SOCCER_BALL_FRAMES];      


//Soccer ball object
struct ball_object {
        int x;
        int y;
        
 	int w;
        int h;

        int prev_x;
        int prev_y;
        
        int direction_x;   //negative=left  zero=stopped positive=right
        int direction_y;   //negative=up  zero=stopped positive=down
        
        int prev_direction_x;
        int prev_direction_y;
        
        int frame;   //Soccer ball sprite frame number
        
        int x_speed;   //ball x speed
        int y_speed;   //ball y speed
};


struct ball_object ball;


//Character objects

struct character_object {
        int x;
        int y;

	int w;
        int h;
        
        int prev_x;
        int prev_y;
        
        int direction_x;
        int direction_y;
        
        int frame;   //character frame number
		
	int speed;   //character speed
		
	int score;   //character score
		
	int prev_score;  
		
	SDL_Surface* image;  //sdl image for the player
};

struct character_object yellow_player;

struct character_object purple_player;


//player bounce areas
//Note: The player height is 67px

//int top_side = 17;   //the top quarter of a character (player height * 0.25)
//int lower_side = 50; //the lower quarter of a character (player height * 0.75)

int top_side = 23;   //the top 35% of a character (player height * 0.35)
int lower_side = 44; //the lower 35% of a character (player height * 0.65)


//Screen redraw flag
int screen_dirty = 0;

//Frame counter
int frame_counter = 0;

//Grass color variable
Uint32 grass_color = 0;

//Debug drawing color variable
Uint32 debug_color;


//Game object rects
SDL_Rect ball_clear_rect;
SDL_Rect left_goal_rect;
SDL_Rect right_goal_rect;

SDL_Rect purple_guy_rect;
SDL_Rect yellow_guy_rect;

SDL_Rect yellow_guy_clear_rect;
SDL_Rect purple_guy_clear_rect;
