//
// Created by WILL on 2021/12/11.
//
#include <cstdio>
#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif

/**
 * @brief The enumerate type game_state, showing the state of the game.
 * 
 */
enum game_state {main_menu = 0, in_game = 1, game_over = 2, game_pause = 3};

/**
 * @brief The Image struct. Used to load a certian image file.
 * 
 */
struct Image { //from tut6
    int mWidth;
    int mHeight;
    GLubyte * mImage;

    /**
     * @brief Load an image file
     * 
     * @param filename the name of the file to be loaded
     */
    void load(char * filename) {

        mImage = LoadPPM(filename, &mWidth, &mHeight);
    }

    /**
     * @brief Draw the image on the screen
     * 
     */
    void draw(unsigned int x, unsigned int y, GLfloat zoom_x, GLfloat zoom_y) {
        glRasterPos2i(x + mWidth * zoom_x, y);
        glPixelZoom(-1*zoom_x, 1*zoom_y);
        glDrawPixels(mWidth, mHeight, GL_RGB, GL_UNSIGNED_BYTE, mImage);
    }

    /**
     * @brief Use the image as a texture.
     * 
     */
    void texture() {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, mWidth , mHeight ,0, GL_RGB, GL_UNSIGNED_BYTE, mImage);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    }
    void texture2(){
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, mWidth , mHeight ,0, GL_RGB, GL_UNSIGNED_BYTE, mImage);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    }
};

/**
 * @brief Draw some texts on the screen
 * 
 */
void draw_text(char *buf, const float *color,
               float width, float height){
    // Set to given color
    glPushMatrix();
    glColor3fv(color);
    glRasterPos2f(width,height);
    // Populate raster image to display text
    for (int i = 0; (unsigned)i < strlen(buf); i++){
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, buf[i]);
    }
    glPopMatrix();
}

/**
 * @brief The handeller structure
 * 
 */
struct Handler {
    unsigned int mLeft, mRight, mTop, mBottom;
    game_state * state;
    void (*mHandlerFunc)(game_state *);
    char name[50];


    bool isInBounds(unsigned int x, unsigned int y) {
        return mLeft <= x && x <= mRight && mBottom <= y && y <= mTop;
    }

    void handleClickAt(unsigned int x, unsigned int y) {
        if (isInBounds(x, y)) {
            mHandlerFunc(state);
        }
    }

    void drawBoxVertices() {
        glVertex3f(mLeft, mTop, 1);
        glVertex3f(mLeft, mBottom, 1);
        glVertex3f(mRight, mTop, 1);
        glVertex3f(mRight, mBottom, 1);
        glVertex3f(mLeft, mTop, 1);
        glVertex3f(mRight, mTop, 1);
        glVertex3f(mLeft, mBottom, 1);
        glVertex3f(mRight, mBottom, 1);
    }
};

struct InteractionHandler {
    std::vector<Handler *> mHandlers;

    void leftClickDown(int x, int y) {
        for (Handler *handler : mHandlers) {
            handler->handleClickAt(x, y);
        }
    }

    void drawHandlers() {
        glDisable(GL_DEPTH_TEST);
        glColor3f(1.0, 0.5, 0.0);
        glLineWidth(3);
        glBegin(GL_LINES);
        for (Handler *handler : mHandlers) {
            handler->drawBoxVertices();
        }
        glEnd();
        float red[3] = {0.2f,0.1f,0.1f};
        for (Handler *handler : mHandlers) {
            draw_text(handler->name, red, handler->mLeft + 50.0f,handler->mBottom + 10.0f);
//            glRasterPos2f(100,100);
//            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'C');
        }
        glEnable(GL_DEPTH_TEST);
    }

    /**
     * @brief Add a handeller onto the handeller set.
     * 
     * @param handler 
     */
    void addHandler(Handler *handler) {
        mHandlers.push_back(handler);
    }
};

InteractionHandler MainScHandler;
InteractionHandler GameOverHandler;

Image start_screen;
Image over_screen;

void setOrthographicProjection(int weight, int height) {
//    //set defualt look at value
//    gluLookAt(0,0,-1,0,0,0,0,1,0);
    glViewport(0, 0, weight, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, weight, 0, height);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void setPerspectiveProjection(int weight, int height) {
    glViewport(0, 0, weight, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, weight/height, 1, 1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}



void dis_menu(int win_height, int win_weigh){
    glDisable(GL_DEPTH_TEST);
    setOrthographicProjection(win_weigh, win_height);
    start_screen.draw(0,0,(GLfloat)win_weigh/600.0f,(GLfloat)win_height/600.0f);
    glEnable(GL_DEPTH_TEST);
}

void dis_gameover(int win_height, int win_weigh, int score){
    glDisable(GL_DEPTH_TEST);
    setOrthographicProjection(win_weigh, win_height);
    char text[50];
    sprintf(text, "Your Score: %d", score);
    float red[3] = {0.2f,0.1f,0.1f};
    over_screen.draw(0,0,(GLfloat)win_weigh/600.0f,(GLfloat)win_height/600.0f);
    draw_text(text, red, win_height / 2 - 100.0f, win_height / 2);
    glEnable(GL_DEPTH_TEST);
}
