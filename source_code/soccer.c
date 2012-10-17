/*

 * IRIX Soccer V1.1 Alpha
 * Created by Andrew Hazelden

 * email: andrewhazelden@gmail.com
 * web: www.andrewhazelden.com/blog

 * Created: Jan 29, 2012
 
 * Required Library: 
   SDL "Simple DirectMedia Layer"
   http://www.libsdl.org/

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <SDL/SDL.h>


#ifdef _WIN32
#include <windows.h>
#endif


// Let's add our own definition of itoa if this is compiled on
// either IRIX / LINUX / Mac OS X 
#ifndef _WIN32
void itoa(int n, char s[], int c);
void reverse(char s[]);
#endif

#include "setup.h"

//The screen surface
SDL_Surface *screen = NULL;
SDL_Rect screen_rect;


int main (int argc, char *argv[]){
	
	PrintVersion();  //Print game info
    InitGFX();       //Setup SDL
    LoadSprites();   //Load the game sprites
    ResetGame();     //Reset the game

    done = 0;
    while (!done){
        //Check for user input
        GetInput();

        //Draw the graphics
        RenderScreen();
    }
    
    //Free the game sprites
    FreeSprites();  

    return 0;
}




//Check for user input
void GetInput(){
    SDL_Event event;
    
    //-------------------
    //Check for events
    //-------------------
    
    while (SDL_PollEvent (&event))
    {
        switch (event.type)
        {
        case SDL_KEYDOWN:
             switch( event.key.keysym.sym ){
                case SDLK_LEFT:
                    yellow_player.direction_x = 1;
                    break;
                case SDLK_RIGHT:
                    yellow_player.direction_x = -1;
                    break;
                case SDLK_UP:
                    yellow_player.direction_y = 1;
                    break;
                case SDLK_DOWN:
                    yellow_player.direction_y = -1;
                    break;
                    
                case SDLK_a: //player 2 left
                     purple_player.direction_x = 1;
                    break;
                case SDLK_d: //player 2 right
                     purple_player.direction_x = -1;
                    break;
                case SDLK_w: //player 2 up
                     purple_player.direction_y = 1;
                    break;
                case SDLK_s: //player 2 down
                     purple_player.direction_y = -1;
                    break;
                
                 default:
                    break;
            }
         break;
         case SDL_KEYUP:
            switch( event.key.keysym.sym ){
                case SDLK_LEFT:
                    yellow_player.direction_x = 0;
                    break;
                case SDLK_RIGHT:
                    yellow_player.direction_x = 0;
                    break;
                case SDLK_UP:
                    yellow_player.direction_y = 0;
                    break;
                case SDLK_DOWN:
                    yellow_player.direction_y = 0;
                    break;
                              
                case SDLK_a: //player 2 left
                     purple_player.direction_x = 0;
                    break;
                case SDLK_d: //player 2 right
                     purple_player.direction_x = 0;
                    break;
                case SDLK_w: //player 2 up
                     purple_player.direction_y = 0;
                    break;
                case SDLK_s: //player 2 down
                     purple_player.direction_y = 0;
                    break;
                default:
                    break;
            }
         break;
        case SDL_QUIT:
            done = 1;
            break;
        default:
            break;
        }
    } 
}


//Game version info
void PrintVersion(){
	printf("Starting IRIX Soccer V1.1\n");
	printf("Created by Andrew Hazelden\n\n");
	
	printf("eMail: andrewhazelden@gmail.com\n");
	printf("Web: www.andrewhazelden.com/blog\n\n");
	
	#ifdef _WIN32
	printf("Running on Windows\n");
	#endif
	
	#ifdef __sgi
	printf("Running on IRIX\n");
	#endif
	
	#ifdef __APPLE__
	printf("Running on Mac OS X\n");
	#endif
	
	#ifdef __linux__
	printf("Running on Linux\n");
	#endif
	
}

///Setup SDL
void InitGFX(){
     
    char *msg;
    
    /* Initialize SDL */
    if (SDL_Init (SDL_INIT_VIDEO) < 0)
    {
        sprintf (msg, "Couldn't initialize SDL: %s\n", SDL_GetError ());
        //MessageBox (0, msg, "Error", MB_ICONHAND); 
        free (msg);
        exit (1);
    }
    atexit (SDL_Quit);

    /* Set 1024x512 16-bits video mode */
    screen = SDL_SetVideoMode (1024, 512, 16, SDL_SWSURFACE | SDL_DOUBLEBUF);
    if (screen == NULL)
    {
        sprintf (msg, "Couldn't set 1024x512x16 video mode: %s\n",
          SDL_GetError ());
        //MessageBox (0, msg, "Error", MB_ICONHAND); 
        free (msg);
        exit (2);
    }
    SDL_WM_SetCaption ("IRIX Soccer", NULL);


    /* Create green background color*/
    //grass_color = SDL_MapRGB(screen->format, 0, 126, 54);
	grass_color = SDL_MapRGB(screen->format, 0, 0, 0);
    debug_color = SDL_MapRGB(screen->format, 126, 126, 126);
    
	//Setup a rect for the full screen
    screen_rect.h = screen->h;
	screen_rect.w = screen->w;  
}





/* Load the soccer images into SDL surfaces */
void LoadSprites(){
     
    int i = 0; 
     
    int current_frame = 0;
    
    
    //Variables for loading BMP image sequences
    char base_image_name[TOTAL_IMAGE_PATH_LENGTH-21] = "images/rollX";  //the name prefix
    char image_number[11] = "";                  //the frame number
    char image_extension[10] = ".bmp";           //the file extension
    
    char combined_file_name[TOTAL_IMAGE_PATH_LENGTH] = "";
    
    
	//Load the soccer ball sprites
    for(i=0;i<TOTAL_SOCCER_BALL_FRAMES;i++){

        //Build the filename string
        strcpy(combined_file_name, base_image_name);  //add the name prefix
	    itoa(current_frame+1, image_number, 10);        //Convert frame number to string
        strcat(combined_file_name, image_number);     //add the frame number
        //strcat(combined_file_name, "1");            //add the frame number
        strcat(combined_file_name, image_extension);  //add the file extension
        
        //Copy the filename string to the struct
        strcpy(ball_frames[current_frame].name, combined_file_name);
        //strcpy(ball_frames[current_frame].name, "images/rollX1.bmp");
        
        //printf("Image [%d] Name: %s\n",current_frame, ball_frames[current_frame].name);
        
        //Load the BMP image into the struct
        ball_frames[current_frame].image = SDL_LoadBMP(ball_frames[current_frame].name);
        
        //Make sure the image was loaded properly
        if(ball_frames[current_frame].image == NULL){
    		fprintf(stderr, "Unable to load image: %s\n", SDL_GetError());
            }
        
	SDL_SetColorKey( ball_frames[current_frame].image, SDL_SRCCOLORKEY, SDL_MapRGB(ball_frames[current_frame].image->format, 0, 126, 54) );

        //Increment the struct frame number    
        current_frame++;
       
    }
   
   
   //----------------------------------------


   grassField = SDL_LoadBMP("images/grass.bmp");
	if(grassField == NULL)
		fprintf(stderr, "Unable to load image: %s\n", SDL_GetError());
   

   goalPost = SDL_LoadBMP("images/goalpost.bmp");
	if(goalPost == NULL)
		fprintf(stderr, "Unable to load image: %s\n", SDL_GetError());
   
   
   yellow_player.image = SDL_LoadBMP("images/yellow_guy.bmp");
	if(yellow_player.image == NULL)
		fprintf(stderr, "Unable to load image: %s\n", SDL_GetError());
   
   purple_player.image = SDL_LoadBMP("images/purple_guy.bmp");
	if(purple_player.image == NULL)
		fprintf(stderr, "Unable to load image: %s\n", SDL_GetError());
   
   
   yellow_goal = SDL_LoadBMP("images/yellow_goal.bmp");
	if(yellow_goal == NULL)
		fprintf(stderr, "Unable to load image: %s\n", SDL_GetError());
   
   purple_goal = SDL_LoadBMP("images/purple_goal.bmp");
	if(yellow_goal == NULL)
		fprintf(stderr, "Unable to load image: %s\n", SDL_GetError());
   
   
   //set up player dimensions
   yellow_player.w = yellow_player.image->w;
   yellow_player.h = yellow_player.image->h;
   
   purple_player.w = purple_player.image->w;
   purple_player.h = purple_player.image->h;
   
   
	//key the green background from the player sprites
	SDL_SetColorKey( purple_player.image, SDL_SRCCOLORKEY, SDL_MapRGB(purple_player.image->format, 0, 126, 54) );
   
	SDL_SetColorKey( yellow_player.image, SDL_SRCCOLORKEY, SDL_MapRGB(yellow_player.image->format, 0, 126, 54) );

	
}



//------------------------
//Reset the current level
//------------------------
void ResetLevel(){
    SDL_Rect  score_rect;

    
    //------------------------ 
    //Set up the soccer ball   
    //------------------------ 
    ball.x = screen->w/2;
    ball.y = screen->h/2;
    ball.prev_x = 0;
    ball.prev_y = 0;
    ball.direction_x = 1;
    ball.direction_y = -1;
    
    ball.w = ball_frames[0].image->w;
    ball.h = ball_frames[0].image->h;
    
    //ball.direction_y = 0;
    ball.frame = 0;
    
    //stopped ball
    //ball.x_speed = BALL_X_MIN_SPEED;
    //ball.y_speed = BALL_Y_MIN_SPEED;

    //animated ball
    ball.x_speed = 8;
    ball.y_speed = 3;
     
     
     
     
    //------------------------  
    //Set up the characters
    //------------------------ 
    
    //purple player
    //Player at the goal posts
    //purple_player.x = 40;
    
    //Player at 25% mark
    purple_player.x = (float)(screen->w)*0.25f;
    purple_player.y = screen->h/2;
    
    
    //yellow player
    //Player at the goal posts
    //yellow_player.x = (screen->w)-30-(yellow_player.w);
    
    //Player at 75% mark
    yellow_player.x = (float)(screen->w)*0.75f; 
    yellow_player.y = screen->h/2;


    //---------------------------
    //Check if a goal was scored
    //---------------------------
    
    if( (yellow_player.score != yellow_player.prev_score) ||
        (purple_player.score != purple_player.prev_score)    ){

        //-------------------------------------------
        //Wait for a second to let the goal sink in
        SDL_Delay(600);  
        //-------------------------------------------
        

 
    //-------------------------------
    //Fill the screen with the grass
    //-------------------------------
    SDL_FillRect(screen, NULL, grass_color);
    
    
    //--------------------------
    //Draw the goal scored text
    //--------------------------
    score_rect.w = yellow_goal->w;
    score_rect.h = yellow_goal->h;
    score_rect.x = (screen->w/2)-(yellow_goal->w/2);
    score_rect.y = (screen->h/2)-(yellow_goal->h/2);
    
    
    if(yellow_player.score != yellow_player.prev_score){
         SDL_BlitSurface(yellow_goal, NULL, screen, &score_rect);
    }
    else if(purple_player.score != purple_player.prev_score){
         SDL_BlitSurface(purple_goal, NULL, screen, &score_rect);
    }  
    
    
    /* Make sure everything is displayed on screen */
    SDL_Flip(screen);
    
    
    
    //Play the vuvuzela sound effect
    
    //------------------------------------------------
    //wait for a few seconds if a goal has been scored
    //------------------------------------------------
    SDL_Delay(3000);    

    
    }
           
    //Set the screen redraw flag     
    screen_dirty = 1; 
}


//Reset the game
void ResetGame(){
    
    //Reset the frame counter 
    frame_counter = 0;
    
    //Reset the score
    yellow_player.score = 0;
    purple_player.score = 0;
    
    yellow_player.prev_score = 0;
    purple_player.prev_score = 0;
    
    //-------------------------
    //Init sprite positions
    //-------------------------
      
    //Reset the ball position  
    ResetLevel();
    
}


// Free the soccer images
void FreeSprites(){
    int i = 0;
    
    //Clear soccer ball frames
    for(i=0;i<TOTAL_SOCCER_BALL_FRAMES;i++){
       SDL_FreeSurface(ball_frames[i].image);
    }
    
    SDL_FreeSurface(goalPost);
    
    SDL_FreeSurface(purple_player.image);
    SDL_FreeSurface(yellow_player.image);
}



//update the character and ball motions
void AnimateFrame(){
     
     
    //------------------------- 
    //animate the purple player
    //-------------------------
    purple_player.x -= purple_player.direction_x * 5;
    purple_player.y -= purple_player.direction_y * 5;

    //limit the purple player to the edge of the left goal post
    if(purple_player.x < 40){
         purple_player.x = 40;               
    }
    //limit the purple player to the edge of the right goal post
    if(purple_player.x > ( (screen->w)-40-30)  ){
         purple_player.x = (screen->w)-40-30;               
    }
    
    //Keep the purple player off the top of the screen
    if(purple_player.y < 0  ){
         purple_player.y = 0;               
    }
    
    //Keep the purple player off the bottom of the screen
    if(purple_player.y > ( screen->h - purple_player.h)  ){
         purple_player.y =  screen->h - purple_player.h;               
    }
    
    
    
    
    
    //-------------------------
    //animate the yellow player
    //-------------------------
    
    yellow_player.x -= yellow_player.direction_x * 5;
    yellow_player.y -= yellow_player.direction_y * 5;

    //limit the yellow player to the edge of the left goal post
    if(yellow_player.x < (40+20)){
         yellow_player.x = (40+20);               
    }

    //limit the yellow player to the edge of the right goal post
    if(yellow_player.x > ( (screen->w)-30-(yellow_player.w) )  ){
         yellow_player.x =  (screen->w)-30-(yellow_player.w);               
    }
    //Keep the yellow player off the top of the screen
    if(yellow_player.y < 0  ){
         yellow_player.y = 0;               
    }
    
    //Keep the yellow player off the bottom of the screen
    if(yellow_player.y > ( screen->h - yellow_player.h)  ){
         yellow_player.y =  screen->h - yellow_player.h;               
    }
    
    
    //--------------------------------------
    //Check for player to player collisions
    //--------------------------------------
    
    
    //Check if the players have collided
	if(IsCollision(purple_player.x, purple_player.y,
			    purple_player.w, purple_player.h,
                yellow_player.x, yellow_player.y,
			    yellow_player.w, yellow_player.h) ){
                    
             //reset the players to their previous positions if they collide                           
             yellow_player.x = yellow_player.prev_x;  
             yellow_player.y = yellow_player.prev_y; 
             
             purple_player.x = purple_player.prev_x;  
             purple_player.y = purple_player.prev_y;                           
    }





     
    //-------------------------
    //Animate the ball
    //-------------------------
    
    //The ball hit the left side of the screen
    if(ball.x < 5){
    ball.direction_x = -1;
    ~ball.direction_y;
    }
    //The ball hit the right side of the screen
    else if(ball.x > ((screen->w)-ball.w) ){
    ball.direction_x = 1;
    ~ball.direction_y;
    }
    
    
    //The ball hit the top of the screen
    if(ball.y < 5){
    ball.direction_y = -1;
    ~ball.direction_x;
    }
    //The ball hit the bottom of the screen
    else if(ball.y > ((screen->h)-ball.h) ){
    ball.direction_y = 1;
    ~ball.direction_x;
    }
    
    
    //Reset the ball speed on a wall bounce
    if( (ball.prev_direction_x != ball.direction_x) ||
        (ball.prev_direction_y != ball.direction_y) ){
        //ball.x_speed = BALL_X_MAX_SPEED;
        //ball.y_speed = BALL_Y_MAX_SPEED;
        }
    
    //Slow the ball sprite down over time
    if((frame_counter % 8) == 1){
        //Check if the ball is going the min x speed
        if(ball.x_speed > BALL_X_MIN_SPEED){
        ball.x_speed--;       
        }
        
        //Check if the ball is going the min y speed
        if(ball.y_speed > BALL_Y_MIN_SPEED){
        ball.y_speed--;       
        }             
    }
    
    
    //keep the ball X speed above the minimum
    if(ball.x_speed < BALL_X_MIN_SPEED){
    ball.x_speed = BALL_X_MIN_SPEED;               
    } 
    
    //keep the ball Y speed above the minimum
    if(ball.y_speed < BALL_Y_MIN_SPEED){
    ball.y_speed = BALL_Y_MIN_SPEED;               
    }  

    //------------------------------------
    //Check for goals
    //------------------------------------


    //Check if the ball is by left goalpost
    if((ball.x-(ball.w/2)+(ball.w/2)) < left_goal_rect.x){     
        //Check if the ball is inside the goalpost section
        if( (ball.y > left_goal_rect.y+1) && ((ball.y+ball.h) < (left_goal_rect.y+left_goal_rect.h)) ){
        //The purple player scored a goal   
        yellow_player.score++;  
        
        //Reset the ball position 
        ResetLevel(); 
              
        }                                         
    }
    
    
    //Check if the ball is by right goalpost
    if((ball.x+(ball.w)-(ball.w/2)) > right_goal_rect.x){     
        //Check if the ball is inside the goalpost section
        if( (ball.y > (right_goal_rect.y+1) ) && ((ball.y+ball.h) < (right_goal_rect.y+right_goal_rect.h)) ){
        //The purple player scored a goal   
        purple_player.score++; 
        
        //Reset the ball position
        ResetLevel();         
        }                                         
    }
    
    
    
    //------------------------------------
    //Check for player to ball collisions
    //------------------------------------
    	
	//Check if the ball hit the yellow player
	if(IsCollision(ball.x,ball.y,
                ball.w, ball.h,
                yellow_player.x, yellow_player.y,
			    yellow_player.w, yellow_player.h) ){
				
				ball.direction_x = 1;
				
				//Bounce ball back
				//~ball.direction_y;
				
				
				//Check if the ball hit the left shoulder of the player
				if( (yellow_player.y+top_side) > (ball.y+(ball.h/2))  ){
                ball.direction_y = 1;  
                }
                //Check if the ball hit the right shoulder of the player
                else if( (yellow_player.y+lower_side) < (ball.y+(ball.h/2)) ){
				ball.direction_y = -1; 
                }
                //The ball hit the player staight on
                else{
                ball.direction_y = 0;
                }
            
				//printf("Yellow Player Bounce\n");
				//printf("ball_x: %d, ball_y: %d\n", ball.x,ball.y);
				//printf("player x: %d, player y: %d\n", yellow_player.x, yellow_player.y);
				
				ball.x_speed = BALL_X_MAX_SPEED;
                ball.y_speed = BALL_Y_MAX_SPEED;
				
				}
				
				
	//Check if the ball hit the purple player
	if(IsCollision(ball.x,ball.y,
                ball.w, ball.h,
                purple_player.x, purple_player.y,
			    purple_player.w, purple_player.h) ){
				
				ball.direction_x = -1;
				//~ball.direction_y;
				
				
                //Check if the ball hit the left shoulder of the player
				if( (purple_player.y+top_side) > (ball.y+(ball.h/2))  ){
                ball.direction_y = 1;  
                }
                //Check if the ball hit the right shoulder of the player
                else if( (purple_player.y+lower_side) < (ball.y+(ball.h/2)) ){
				ball.direction_y = -1; 
                }
                //The ball hit the player staight on
                else{
                ball.direction_y = 0;
                }
				
				
				//printf("Purple Player Bounce\n");
				//printf("ball_x: %d, ball_y: %d\n", ball.x,ball.y);
				//printf("player x: %d, player y: %d\n", purple_player.x,purple_player.y);
				
				ball.x_speed = BALL_X_MAX_SPEED;
                ball.y_speed = BALL_Y_MAX_SPEED;
				
                
                }
    
    
    ball.x -= ball.direction_x * ball.x_speed;
    ball.y -= ball.direction_y * ball.y_speed;

    
    //Sprite low bounds check
    if(ball.x < 0){
       ball.x= 0;   
       screen_dirty = 1;      
    } 
    
    if(ball.y < 0){
       ball.y= 0;   
       screen_dirty = 1;      
    }


    //Sprite high bounds check
    if(ball.x > screen->w){
       ball.x = screen->w;   
       screen_dirty = 1;     
    } 
    
    if(ball.y > screen->h){
      ball.y = screen->h;  
      screen_dirty = 1;      
    }
     
    //-------------------------
    //Animate the ball spin rate
    //-------------------------
    
    if(ball.direction_x == -1){
        //Medium-High Speed ball animation
        if(ball.x_speed > 6){
          ball.frame--;
          }
        else if( (ball.x_speed > 3)  && ( (frame_counter % 2) == 0 )){
          ball.frame--;
        }
        else if( (ball.x_speed > 1) && ( (frame_counter % 4) == 0 )){
          ball.frame--;
        }
        
        //do nothing if the ball x speed is zero        
        //printf("Current Frame: %d, ball frame%d\n", frame_counter, ball.frame);
        //
    }
    else{
    //Medium-High Speed ball animation
        if(ball.x_speed > 6){
          ball.frame++;
          }
        else if( (ball.x_speed > 3)  && ( (frame_counter % 2) == 0 )){
          ball.frame++;
        }
        else if( (ball.x_speed > 1) && ( (frame_counter % 4) == 0 )){
          ball.frame++;
        }
        
        //do nothing if the ball x speed is zero        
        //printf("Current Frame: %d, ball frame%d\n", frame_counter, ball.frame);  
    }

    //Set the frame limits 
    if(ball.frame < 0){
    ball.frame=TOTAL_SOCCER_BALL_FRAMES-1; 
    }
    
    if(ball.frame >= TOTAL_SOCCER_BALL_FRAMES){
    ball.frame=0; 
    }
 
 
 
 
    //-------------------------
    //Update the game object rects
    //-------------------------
    
    yellow_guy_rect.w = yellow_player.w;
    yellow_guy_rect.h = yellow_player.h;
    yellow_guy_rect.x = yellow_player.x;
    yellow_guy_rect.y = yellow_player.y;
    
    purple_guy_rect.w = purple_player.w;
    purple_guy_rect.h = purple_player.h;
    purple_guy_rect.x = purple_player.x;
    purple_guy_rect.y = purple_player.y;
    
    
    yellow_guy_clear_rect.w = yellow_player.w;
    yellow_guy_clear_rect.h = yellow_player.h;
    yellow_guy_clear_rect.x = yellow_player.prev_x;
    yellow_guy_clear_rect.y = yellow_player.prev_y;
    
    purple_guy_clear_rect.w = purple_player.w;
    purple_guy_clear_rect.h = purple_player.h;
    purple_guy_clear_rect.x = purple_player.prev_x;
    purple_guy_clear_rect.y = purple_player.prev_y;

    ball_clear_rect.w = ball.w;
    ball_clear_rect.h = ball.h;
    ball_clear_rect.x = ball.prev_x;
    ball_clear_rect.y = ball.prev_y;
    
    
    //Left Goal post drawing rect
    left_goal_rect.w = goalPost->w;
    left_goal_rect.h = goalPost->h;
    left_goal_rect.x = 22;
    left_goal_rect.y = (screen->h/2)-(goalPost->h/2);
    
    //Right Goal post drawing rect
    right_goal_rect.w = goalPost->w;
    right_goal_rect.h = goalPost->h;
    right_goal_rect.x = screen->w-22;
    right_goal_rect.y = (screen->h/2)-(goalPost->h/2);
     
}







// This function draws to the screen
static void RenderScreen(){

    AnimateFrame();  //animate the objects in the frame

    
    if( (screen_dirty) || (frame_counter<1) ){ 
        //Full background rect clearing
        //SDL_FillRect(screen, NULL, grass_color);
		SDL_BlitSurface(grassField, &screen_rect, screen, &screen_rect);

        
        //draw the goal posts
        SDL_BlitSurface(goalPost, NULL, screen, &right_goal_rect);
        SDL_BlitSurface(goalPost, NULL, screen, &left_goal_rect);
        
        //Reset screen dirty flag
        screen_dirty = 0;     
    }
    else{    
        //Debug ball clear rect
        //SDL_FillRect(screen, &ball_clear_rect, debug_color);
        
        //clear old ball rect
        //SDL_FillRect(screen, &ball_clear_rect, grass_color);
        SDL_BlitSurface(grassField, &ball_clear_rect, screen, &ball_clear_rect);

        //draw the goal posts
        SDL_BlitSurface(goalPost, NULL, screen, &right_goal_rect);
        SDL_BlitSurface(goalPost, NULL, screen, &left_goal_rect);
        
        //Clear old character rect

        //SDL_FillRect(screen, &yellow_guy_clear_rect, grass_color);
		SDL_BlitSurface(grassField, &yellow_guy_clear_rect, screen, &yellow_guy_clear_rect);

        //SDL_FillRect(screen, &purple_guy_clear_rect, grass_color);
		SDL_BlitSurface(grassField, &purple_guy_clear_rect, screen, &purple_guy_clear_rect);
        


        //debug the character clear rects
        //SDL_FillRect(screen, &yellow_guy_clear_rect, debug_color);
        //SDL_FillRect(screen, &purple_guy_clear_rect, debug_color);
    }
	 
    //----------------------
    //Draw the soccer ball
    //----------------------
    DrawBall(ball.frame, ball.x, ball.y);


    //----------------------
    //Draw the goal posts
    //----------------------

    //Redraw the left goal post when the ball is near by
    //if(ball.x < 22 ){
    SDL_BlitSurface(goalPost, NULL, screen, &left_goal_rect);
    //}
    
    //Redraw the right goal post when the ball is near by
    //if((ball.x+ball.w) > (screen->w-22) ){
    SDL_BlitSurface(goalPost, NULL, screen, &right_goal_rect);
    //}
    
    
    //----------------------
    //Draw the characters
    //----------------------
    SDL_BlitSurface(purple_player.image, NULL, screen, &purple_guy_rect);
    SDL_BlitSurface(yellow_player.image, NULL, screen, &yellow_guy_rect);



    //-------------------------
    //Update the screen
    //-------------------------
    
    /* Make sure everything is displayed on screen */
    SDL_Flip(screen);
    
    /* Don't run too fast */
    #ifdef _WIN32
    SDL_Delay(15);
    #endif

    #ifdef __sgi
    SDL_Delay(1);
    #endif
    
    SDL_Delay(1);
    
    
    //increment the current frame number
    frame_counter++;
    
    //Save the settings from the previous frame
    SavePrevious(); 
}


//Save the settings from the previous frame
void SavePrevious(){
         
    //Save the old ball position
    ball.prev_x = ball.x;
    ball.prev_y = ball.y;
    
    //Save the old ball direction
    ball.prev_direction_x = ball.direction_x;
    ball.prev_direction_y = ball.direction_y;

    //Save the old character positions
    yellow_player.prev_x = yellow_player.x;
    yellow_player.prev_y = yellow_player.y;
    
    purple_player.prev_x = purple_player.x;
    purple_player.prev_y = purple_player.y;
     
    //Save the previous player score
    yellow_player.prev_score = yellow_player.score;
    purple_player.prev_score = purple_player.score;
     
}


//Draw the soccer ball over the background
void DrawBall(int frame, int x, int y){
    SDL_Rect ball_rect;
    
    ball_rect.w = ball.w;
    ball_rect.h = ball.h;
    ball_rect.x = x;
    ball_rect.y = y;
     
    //Set the frame limits 
    if(frame < 0){
    frame=TOTAL_SOCCER_BALL_FRAMES-1; 
    }
    
    if(frame > TOTAL_SOCCER_BALL_FRAMES){
    frame=0; 
    }
     
    //Draw the animated soccer ball 
    SDL_BlitSurface(ball_frames[frame].image, NULL, screen, &ball_rect);
   
}  







// Example:
// IsCollision(ball.x,ball.y,
            // ball.w, ball.h,
             // yellow_player.x, yellow_player.y,
			 // yellow_player.w, yellow_player.h);


//Check for a sprite to Player collision
char IsCollision (unsigned int Shape_X, unsigned int Shape_Y,  unsigned int Shape_Width, unsigned int Shape_Height,
                                  unsigned int Player_Left, unsigned int Player_Top, unsigned int Player_Width, unsigned int Player_Height) {
        
        //Check for Player collisions
        //The right side of Shape is greater than left side of Player     and        left side of Shape is smaller than right side of Player
        if( ((Shape_X + Shape_Width) >= Player_Left )               &&              ((Shape_X) <= (Player_Left + Player_Width-1)) &&
           
           
           //Check for Player top and bottom collisions 
           //The bottom side of Shape is greater than top of Player         and            top of Shape is smaller then bottom of Player
           ((Shape_Y + Shape_Height) >= Player_Top )                   &&               ((Shape_Y) <= (Player_Top + Player_Height-1))  ) {
                
                
                //Debug printing
                //printf("Collision detected\n");
                
                //A collision has been detected
                return 1;
        }
        else
        {
                //Default return value
                //No collisions have been detected
                return 0;
        }
        
}



// Let's add our own definition of itoa if this is compiled on
// either IRIX / LINUX / Mac OS X 

#ifndef _WIN32
/* itoa:  convert n to characters in s */
void itoa(int n, char s[], int c)
 {
     int i, sign;
 
     if ((sign = n) < 0)  /* record sign */
         n = -n;          /* make n positive */
     i = 0;
     do {       /* generate digits in reverse order */
         s[i++] = n % 10 + '0';   /* get next digit */
     } while ((n /= 10) > 0);     /* delete it */
     if (sign < 0)
         s[i++] = '-';
     s[i] = '\0';
     reverse(s);
 }
 
 
 /* reverse:  reverse string s in place */
 void reverse(char s[])
 {
     int i, j;
     char c;
 
     for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
         c = s[i];
         s[i] = s[j];
         s[j] = c;
     }
 }
#endif
