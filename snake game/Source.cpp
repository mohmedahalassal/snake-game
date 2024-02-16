    #define _CRT_SECURE_NO_WARNINGS
    #include <windows.h>
    #include <GL/glut.h>
    #include <stdbool.h>
    #include <stdio.h>
    #include <ctime>
    #include<math.h>

    #define col 30
    #define row 20
    #define snakeSpeed 9
    #define up -1
    #define down 1
    #define right -2
    #define left 2
    #define maxLength 18

    void drawGrid();
    void RenderScene();
    void ChangeSize();
    void timer(int);
    void pointer(int, int);
    void drawGrid();
    void keyboard(int, int, int);
    void defineTheSnake();
    void defineTheFood();

    void random(int&, int&);
    int gX, gY;

    int position_x[20] = { 10,10 }, position_y[30] = { 10,10,10 };
    short dir = right;
    bool gameover = false;

    int snake_length = 3;

    bool food = true;
    int foodX, foodY;
    int score = 0;

    void initgrid(int x, int y) {
        gX = x;
        gY = y;
    }

    void drawGrid() {
        for (int x = 0; x < gX; x++)
        {
            for (int y = 0; y < gY; y++)
            {
           
                pointer(x, y);
            }
        }
    }

    void initialGrid() {
        glClearColor(0.0, 0.0, 0.0, 1.0);
        initgrid(col, row);
    }


    void pointer(int x, int y) {
        if (x == 0 || y == 0 || x == gX - 1 || y == gY - 1) {
            glLineWidth(4.0);
            glColor3d(1.0, 0.0, 0.0);

        }
        else {
            glLineWidth(0.9);
            glColor3d(0.0, 0.0, 1.0);
        }

        glBegin(GL_LINE_LOOP);
        glVertex2f(x, y);
        glVertex2f(x + 1, y);
        glVertex2f(x + 1, y + 1);
        glVertex2f(x, y + 1);
        glEnd();

    }

    void defineTheFood() {
  
        if (food)
            random(foodX, foodY);
        food = false;
        glColor3f(1.0, 0.0, 1.0);
   
        glRectf(foodX, foodY, foodX + 1, foodY + 1);
    }


    void random(int& x, int& y) {
        int maxLengthX = gX - 2;
        int maxLengthY = gY - 2;
        int min = 1;
 
        srand(time(NULL));
        x = min + rand() % (maxLengthX - min);
        y = min + rand() % (maxLengthY - min);
    }


    void defineTheSnake() {

        for (int i = snake_length - 1; i > 0; i--)
        {
            position_x[i] = position_x[i - 1];
            position_y[i] = position_y[i - 1];
        }

        if (dir == up) position_y[0]++;
        else if (dir == down) position_y[0]--;
        else if (dir == right) position_x[0]++;
        else if (dir == left) position_x[0]--;
        for (int i = 0; i < snake_length; i++)
        {

            if (i == 0) {
                glColor3f(0.0, 1.0, 0.0);
            }
            else
            {
                glColor3f(1.0, 1.0, 0.0);
            }
            glRectd(position_x[i], position_y[i], position_x[i] + 1, position_y[i] + 1);
        }

        if (position_x[0] == 0 || position_x[0] == gX - 1 || position_y[0] == 0 || position_y[0] == gY - 1) { gameover = true; }
   
        else  if (position_x[0] == foodX && position_y[0] == foodY) {
            score++;
            snake_length++;
            if (snake_length > maxLength)
                snake_length = maxLength;
            food = true;
        }
    }

    void timer(int) {
        glutPostRedisplay();
        glutTimerFunc(1000 / snakeSpeed, timer, 0);
    }

    void keyboard(int key, int, int) {
        if (key == GLUT_KEY_UP) {
        
            if (dir != down) dir = up;
        }
        else if (key == GLUT_KEY_DOWN) {
            if (dir != up) dir = down;
        }
        else if (key == GLUT_KEY_RIGHT) {
            if (dir != left) dir = right;
        }
        else if (key == GLUT_KEY_LEFT) {
            if (dir != right) dir = left;
        }
    }


    void RenderScene(void)
    {
        glClear(GL_COLOR_BUFFER_BIT);
        drawGrid();
        defineTheSnake();
        defineTheFood();
        glFlush();
        if (gameover) {
            printf("Score: %d", score);
            MessageBoxA(NULL, "You hit the wall! Game over!", "Game Over", MB_ICONEXCLAMATION | MB_OK);
            exit(0);
        }
    }

    void ChangeSize(int w, int h) {
        glViewport(0, 0, (GLsizei)w, (GLsizei)h);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, col, 0, row, -1, 1);
        glMatrixMode(GL_MODELVIEW);
    }


    int main(int argc, char* argv[]) {
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
        glutInitWindowSize(500, 500);
        glutCreateWindow("snake");
        glutDisplayFunc(RenderScene);
        glutTimerFunc(0, timer, 0);
        initialGrid();
        glutReshapeFunc(ChangeSize);
        glutSpecialFunc(keyboard);

        glutMainLoop();
        return 0;
    }