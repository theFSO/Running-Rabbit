// Standard C++ library imports
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <typeinfo>
#include <vector>
#include <iostream>

#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif

// Import object classes
#include "src/Player.h"
#include "src/Lane.h"
#include "src/Obstacle.h"
//#include "src/lighting.h"
#include "src/utli.h"
#include "src/PPM.h"
#include "src/displays.cpp"

// Static global values for display dimensions
static int DISPLAY_WIDTH = 600;
static int DISPLAY_HEIGHT = 600;
static int DISPLAY_OFFSET_WIDTH;
static int DISPLAY_OFFSET_HEIGHT;

std::string player_model = "resource/cat.obj";

Player player = '\0';
Lane lane_left = '\0';
Lane lane_middle = '\0';
Lane lane_right = '\0';
game_state current_state;
// set light
float lightPos1[] = { player.positionX, player.positionY+25, player.positionZ + 15, 1 };
float lightAmb[] = { 0.35, 0.35, 0.35, 1 };
float lightDif[] = { 0.35, 0.35, 0.35, 1 };
float lightSpc[] = { 0.35, 0.35, 0.35, 1 };
int animate_counter = 0;
int animate_interval = 0;
// Player object always in the middle of the screen

static const float LANE_POS_INCREMENT = 9;

static int score;
static char scoreMessage[64] = { '\0' };
static char lifeMessage[64] = { '\0' };
bool animate = false;
float gravity_constant = 0.04;
bool is_jump;
bool first_persion_view = false;
bool enable_light = true;

/**
 * @brief Image Structure
 * @todo Try to move them into a header file
 */

//Image obstaclesTexture;
Image playerTexture;
Image laneTexture;
Image WallTexture;
//Image WaterTexture;
/**
 * @brief Initialization of lanes
 * 
 */

void initLanes(){
    lane_left = Lane(-6, 0, 0, 1);
    lane_middle = Lane(3, 0, 0, 1);
    lane_right = Lane(12, 0, 0, 1);
    lane_left.init(6, 100, 50, 100, 10000);
    lane_middle.init(6, 100, 50, 100, 10000);
    lane_right.init(6, 100, 50, 100, 10000);
}

/**
 * @brief Draw Lanes in display()1
 * 
 */
void drawLane()
{
    laneTexture.texture();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    lane_left.render(player.positionZ);
    lane_middle.render(player.positionZ);
    lane_right.render(player.positionZ);
}

/**
 * @brief Move a player. The player will move 1 unit per frame
 * 
 * @param val 
 */
void movePlayer(int val)
{
    if (animate && player.positionZ <= 10000 && current_state == in_game) {
        if (animate_interval >= 15){
            if (animate_counter == 4){
                animate_counter = 1;
            } else {
                animate_counter++;
            }
            animate_interval = 0;
        }else{
            animate_interval++;
        }
        player.move();
        if (is_jump) {
            player.jump();
            player.apply_grav(gravity_constant);
            score += 50;
        }
    }
    glutTimerFunc(1000 / 60, movePlayer, 0);
}

void restart_game(){
    score = 0;
    player.positionZ = 0;
    player.positionX = 0;
    initLanes();
    current_state = game_over;
    animate = true;
    glutPostRedisplay();
}

/**
 * @brief Check if the player is collided with the obstacles. If so, clear the scores and the line status.1
 * 
 */
void check_collision() {
    bool collided = false;
    if (player.positionX == -9) {
        if (lane_left.detect_collision(player.positionY, player.positionZ, player.color)) {
            collided = true;
        }
    }
    if (player.positionX == 0) {
        if (lane_middle.detect_collision(player.positionY, player.positionZ, player.color)) {
            collided = true;
        }
    }
    if (player.positionX == 9) {
        if (lane_right.detect_collision(player.positionY, player.positionZ, player.color)) {
            collided = true;
        }
    }
    if (collided){
        player.hp --;
        player.positionZ += 4;
        if (player.hp <= 0){
            current_state = game_over;
            player.hp = 3;
        } // game over
        
    }
}


/**
 * @brief Show the score of the player.
 * 
 */
void showScore()
{
    // Calculate score
    score = (int)floor(player.positionZ / 3);
    glColor3fv(utli::get_color(player.color));
    // Position raster text below above the player
    glRasterPos3f(player.positionX + 15, player.positionY + 20, player.positionZ);

    // Populate score display message
    memset(scoreMessage, '\0', sizeof(scoreMessage));
    
    snprintf(scoreMessage, sizeof(scoreMessage),
        "Score: %d", score);
    
    // Populate raster image to display text
    for (int i = 0; (unsigned)i < strlen(scoreMessage); i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,
            scoreMessage[i]);

    glRasterPos3f(player.positionX + 15.18, player.positionY + 18, player.positionZ);
    memset(lifeMessage, '\0', sizeof(lifeMessage));
    snprintf(lifeMessage, sizeof(lifeMessage),
        "Health Point: %d", player.hp);
    for (int i = 0; (unsigned)i < strlen(lifeMessage); i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,
            lifeMessage[i]);
    glColor3f(1.0f,1.0f,1.0f);
}
void drawBack(float pos){
    glDisable(GL_CULL_FACE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBegin(GL_POLYGON);
    glTexCoord2f(0,0);
    glVertex3f(30.0,-10.0,500.0 + pos);
    glTexCoord2f(0,1);
    glVertex3f(30.0,100.0,500.0 + pos);
    glTexCoord2f(1,1);
    glVertex3f(30.0,100.0,-100.0 + pos);
    glTexCoord2f(1,0);
    glVertex3f(30.0,-10.0,-100.0 + pos);
    glEnd();


    glBegin(GL_POLYGON);
    glTexCoord2f(0,0);
    glVertex3f(-30.0,-10.0,500.0 + pos);
    glTexCoord2f(0,1);
    glVertex3f(-30.0,100.0,500.0 + pos);
    glTexCoord2f(1,1);
    glVertex3f(-30.0,100.0,-100.0 + pos);
    glTexCoord2f(1,0);
    glVertex3f(-30.0,-10.0,-100.0 + pos);
    glEnd();


    glEnable(GL_CULL_FACE);
}
/**
 * @brief The display function1
 * 
 */

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    switch (current_state) {
        case main_menu:
            glDisable(GL_LIGHTING);
            glDisable(GL_NORMALIZE);
            glDisable(GL_LIGHT0);
            dis_menu(DISPLAY_HEIGHT,DISPLAY_WIDTH);
            MainScHandler.drawHandlers();
            break;
        case game_pause:
        case in_game:
            glEnable(GL_LIGHTING);
            glEnable(GL_LIGHT0);
            glEnable(GL_NORMALIZE);
            setPerspectiveProjection(DISPLAY_WIDTH,DISPLAY_HEIGHT);
            glLoadIdentity();
            if (!first_persion_view) {
                gluLookAt(
                        player.positionX, player.positionY + 20, player.positionZ - 60,
                        player.positionX, player.positionY, player.positionZ + 20,
                        0, 1, 0
                );
            }
            else {
                gluLookAt(
                        player.positionX, player.positionY + 8, player.positionZ,
                        player.positionX, player.positionY, player.positionZ + 20,
                        0, 1, 0
                );
            }
            //obstaclesTexture.texture();

            glPushMatrix();

            lightPos1[0] = player.positionX;
            lightPos1[1] = player.positionY+10;
            lightPos1[2] = player.positionZ+5;
            glLightfv(GL_LIGHT0, GL_POSITION, lightPos1);
            glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDif);
            glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb);
            glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpc);
            //glDisable(GL_LIGHTING);
            //glDisable(GL_LIGHT0);
            drawLane();
//  player.render()1
            playerTexture.texture();
            player.obj_render(animate_counter);
            glBindTexture(GL_TEXTURE_2D,0);
            glDisable(GL_LIGHTING);
            glDisable(GL_NORMALIZE);
            glDisable(GL_LIGHT0);
            showScore();
            check_collision();
            glPopMatrix();
            WallTexture.texture();
            drawBack(player.positionZ);
            break;
        case game_over:
            glDisable(GL_LIGHTING);
            glDisable(GL_NORMALIZE);
            glDisable(GL_LIGHT0);
            glDisable(GL_TEXTURE_2D);
            dis_gameover(DISPLAY_HEIGHT,DISPLAY_WIDTH,score);
            GameOverHandler.drawHandlers();
            break;
    }
    glFlush();
    glutSwapBuffers();
}

/**
 * We have input handellers here
 * ---------------------------------------------------------------------------------------------------------------------
 *
 */

/**
 * @brief Keyboard input handeller
 * 
 * @param key the key input
 * @param x the cursor location
 * @param y the cursor location
 */
void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 'd': case 'D':
            if (current_state != in_game){
                break;
            }
            if (player.positionX > -1 * LANE_POS_INCREMENT)
                player.positionX -= LANE_POS_INCREMENT;
            break;
        case 'a': case 'A':
            if (current_state != in_game){
                break;
            }
            if (player.positionX < LANE_POS_INCREMENT)
                player.positionX += LANE_POS_INCREMENT;
            break;
        case 'q':
        case 'Q':
        case 27:
            exit(0);
            break;
        case 'p':
        case 'P':
            if (current_state == in_game){
                animate = false;
                current_state = game_pause;
            }else if(current_state == game_pause){
                animate = true;
                current_state = in_game;
            }
            break;
        case ' ':
            if (player.positionY < 1) {
                is_jump = true;
                player.reset();
            }
            break;
        case '1':
            player.set_color(7);
            break;
        case '2':
            player.set_color(8);
            break;
        case '3':
            player.set_color(9);
            break;
        case 'r':
        case 'R':
            score = 0;
            player.positionZ = 0;
            initLanes();
            break;
        case 'n':
        case 'N':
            first_persion_view = !first_persion_view;
            break;
        default:
            break;
    }
}

/**
 * @brief Window reshape handeller1
 * 
 *
 */
void reshape(int w, int h) {
    DISPLAY_WIDTH = w;
    DISPLAY_HEIGHT = h;
    glutPostRedisplay();
}

/**
 * @brief Special key handeller
 * 
 *
 */
void special(int key, int x, int y)
{
    switch (key)
    {
        case GLUT_KEY_RIGHT:
            if (current_state != in_game){
                break;
            }
            if (player.positionX > -1 * LANE_POS_INCREMENT)
                player.positionX -= LANE_POS_INCREMENT;
            break;
        case GLUT_KEY_LEFT:
            if (current_state != in_game){
                break;
            }
            if (player.positionX < LANE_POS_INCREMENT)
                player.positionX += LANE_POS_INCREMENT;
            break;
    }
}

/**
 * @brief The idle func111
 * 
 */
void idle(){
    glutPostRedisplay();
}

void handleMouse(int button, int state, int x, int y) {
    /**
     * YOUR CODE HERE
     *
     * Check for GLUT_LEFT_BUTTON and GLUT_DOWN and then call
     * mouseHandler.leftClickDown, remember viewportHeight - y.
     */
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        switch (current_state) {
            case main_menu:
                MainScHandler.leftClickDown(x, DISPLAY_HEIGHT - y);
                break;
            case in_game:
                break;
            case game_over:
                GameOverHandler.leftClickDown(x, DISPLAY_HEIGHT - y);
                break;
            case game_pause:
                break;
        }
}

/**
 * We have initializers here
 * ------------------------------------------------------------------------------------------------------------------------
 * First is handler for buttons1
 */

void StartGame(game_state* st){
    *st = in_game;
    animate = true;
}

Handler StartGameBtn = {
        200,
        400,
        120,
        70,
        &current_state,
        StartGame,
        "Start Game"
};

void RestartGame(game_state* st){
    restart_game();
    *st = in_game;
}

Handler RestartGameBtn = {
        200,
        400,
        250,
        200,
        &current_state,
        RestartGame,
        "Restart Game"
};
/**
 * @brief The initiallization functions1
 * 
 */
void init() {
    //GLUT init
    DISPLAY_OFFSET_WIDTH =
        ((glutGet(GLUT_SCREEN_WIDTH) - DISPLAY_WIDTH) / 2);
    DISPLAY_OFFSET_HEIGHT =
        ((glutGet(GLUT_SCREEN_HEIGHT) - DISPLAY_HEIGHT) / 2);

    glutInitWindowSize(DISPLAY_WIDTH, DISPLAY_HEIGHT);
    glutInitWindowPosition(DISPLAY_OFFSET_WIDTH,
        DISPLAY_OFFSET_HEIGHT);

    glutCreateWindow("Final Project");
    current_state = main_menu;
    utli::init();
    // class init
    printf("Begin to load models and textures, this may take some time");
    player = Player(0, 0, 0, 0);

    player.load_obj("resource/cat1.obj",1);
    player.load_obj("resource/cat2.obj",2);
    player.load_obj("resource/cat3.obj",3);

    laneTexture.load((char*)"resource/grass.ppm");
    playerTexture.load((char*)"resource/cat.ppm");
    start_screen.load((char*)"resource/startScreen.ppm");
    over_screen.load((char*)"resource/overScreen.ppm");
    WallTexture.load((char*)"resource/stat2.ppm");

    // load handlers
    MainScHandler.addHandler(&StartGameBtn);
    GameOverHandler.addHandler(&RestartGameBtn);

    initLanes();

    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glEnable(GL_TEXTURE_2D);
}

/**
 * We have the main function here
 * ---------------------------------------------------------------------------------------------------------------------------
 * 
 */

/**
 * @brief The main func
 * 
 */
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(handleMouse);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(idle);
    glutSpecialFunc(special);
    glutTimerFunc(1000 / 60, movePlayer, 0);
    glutMainLoop();

    return 0;
}
