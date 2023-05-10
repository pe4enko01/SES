#include <iostream>
#include <cstdlib>
#include <cmath>
#include <GL/glut.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define BALL_COUNT 10
#define BOUNDARY 5.0f
#define BALL_RADIUS 1.0f
#define CAM_X 0.0f
#define CAM_Y 0.0f
#define CAM_Z 10.0f

float ball_x[BALL_COUNT];
float ball_y[BALL_COUNT];
float ball_z[BALL_COUNT];
float ball_intensity[BALL_COUNT];

// Функция для вычисления интенсивности метабола в точке (x, y)
float calculate_intensity(float x, float y)
{
    float intensity = 0.0f;
    for (int i = 0; i < BALL_COUNT; i++) {
        float dx = x - ball_x[i];
        float dy = y - ball_y[i];
        float distance = sqrt(dx * dx + dy * dy);
        if (distance < BALL_RADIUS) {
            intensity += (BALL_RADIUS - distance) / BALL_RADIUS * ball_intensity[i];
        }
    }
    return intensity;
}

// Функция для обновления позиций метаболов
void update_balls()
{
    for (int i = 0; i < BALL_COUNT; i++) {
        ball_x[i] += (float)(rand() % 200 - 100) / 100.0f * 0.1f;
        ball_y[i] += (float)(rand() % 200 - 100) / 100.0f * 0.1f;
        if (ball_x[i] > BOUNDARY) {
            ball_x[i] = BOUNDARY;
        }
        if (ball_x[i] < -BOUNDARY) {
            ball_x[i] = -BOUNDARY;
        }
        if (ball_y[i] > BOUNDARY) {
            ball_y[i] = BOUNDARY;
        }
        if (ball_y[i] < -BOUNDARY) {
            ball_y[i] = -BOUNDARY;
        }
        ball_intensity[i] = (float)(rand() % 100) / 100.0f;
    }
}

// Функция для отрисовки метаболов
void draw_balls()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPointSize(2.0f);
    glBegin(GL_POINTS);
    for (float y = -BOUNDARY; y <= BOUNDARY; y += 0.1f) {
        for (float x = -BOUNDARY; x <= BOUNDARY; x += 0.1f) {
            float intensity = calculate_intensity(x, y);
            glColor3f(intensity, intensity, intensity);
            glVertex3f(x, y, ball_z[0]);
        }
    }
    glEnd();
}

// Функция для обработки клавиш клавиатуры
void handle_keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 'q':
    case 'Q':
    case 27:  // ESC key
        exit(0);
        break;
    }
}

// Функция инициализации OpenGL
void init()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
}

int main(int argc, char** argv)
{
    // Инициализация GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("Metaballs");

    // Регистрация функций обратного вызова
    glutDisplayFunc(draw_balls);
    glutKeyboardFunc(handle_keyboard);
    glutIdleFunc(update_balls);

    // Инициализация OpenGL
    init();

    // Инициализация позиций метаболов
    for (int i = 0; i < BALL_COUNT; i++) {
        ball_x[i] = (float)(rand() % (int)(BOUNDARY * 200)) / 100.0f - BOUNDARY;
        ball_y[i] = (float)(rand() % (int)(BOUNDARY * 200)) / 100.0f - BOUNDARY;
        ball_z[i] = 0.0f;
        ball_intensity[i] = (float)(rand() % 100) / 100.0f;
    }

    // Запуск главного цикла
    while (1) {
        glutMainLoopEvent();
        glutPostRedisplay();
    }

    return 0;
}