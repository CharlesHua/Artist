/*****************************************************************************************
ģ�� ������ʷ�����(David Shrigley) ����Ʒ�������ҡ��Ļ滭ģʽ

�����������ƣ�����������ʵ��Ʒ�����������ȡ�


*****************************************************************************************/
#include <GL/glut.h>
#include <iostream>
#include <math.h>
#include "16807RNG.h"
#include "artist.h"
//using namespace std;

#define PI 3.1415926535897
#define WIDTH 601 //ͼ�ν������Ԫ����
#define REFRESH_TIME 1 //ѭ��ʱ����
#define GRID_NUMBER 600  //��ȥ���֮��ĸ��
#define DEBUG 0 //�Ƿ��ڵ���״̬

int center = GRID_NUMBER / 2;  //���ĵ�����

int t,step = 1;
int frequency = 20;

struct Color{
    short red,green,blue;
};
Color color[2]={0x00,0xCC,0x00, 0xFF,0xFF,0x00};
               /**     0               1        **/

RandomNumber_16807 rng(0x7FFFFFFF / 37);

Head painter = Head(20, 40, GRID_NUMBER / 2);

void display(){
    static int init = 0;
    if (init == 0){
        glClearColor (1.0, 1.0, 1.0, 0.0);
        glClear(GL_COLOR_BUFFER_BIT);
        init++;
    }

    glPointSize(1.5f);
    int j;
    double t;

    static P2d pos_old[2];
    static P2d pos_new[2];
    pos_new[0] = painter.get_pos(Head::PointName::LEFT);
    pos_new[1] = painter.get_pos(Head::PointName::RIGHT);
    while(step % frequency){
        t = rng.get_random_number();
        if (t < 0.4)
            for (int i=0; i<5; i++){
                pos_old[0] = pos_new[0];
                pos_old[1] = pos_new[1];
                painter.Turn(Head::RotationDirection::CLOCKWISE);
                pos_new[0] = painter.get_pos(Head::PointName::LEFT);
                pos_new[1] = painter.get_pos(Head::PointName::RIGHT);
                for(j=0; j<2; j++){
                    glColor3d(color[j].red, color[j].green, color[j].blue);
                    glBegin(GL_LINES);
                        glVertex2d((2.0 * pos_old[j].x / WIDTH),(2.0 * pos_old[j].y / WIDTH));
                        glVertex2d((2.0 * pos_new[j].x / WIDTH),(2.0 * pos_new[j].y / WIDTH));
                    glEnd();
                }
            }
        else if (t<0.8)
            for (int i=0; i<5; i++){
                pos_old[0] = pos_new[0];
                pos_old[1] = pos_new[1];
                painter.Turn(Head::RotationDirection::ANTICLOCKWISE);
                pos_new[0] = painter.get_pos(Head::PointName::LEFT);
                pos_new[1] = painter.get_pos(Head::PointName::RIGHT);
                for(j=0; j<2; j++){
                    glColor3d(color[j].red, color[j].green, color[j].blue);
                    glBegin(GL_LINES);
                        glVertex2d((2.0 * pos_old[j].x / WIDTH),(2.0 * pos_old[j].y / WIDTH));
                        glVertex2d((2.0 * pos_new[j].x / WIDTH),(2.0 * pos_new[j].y / WIDTH));
                    glEnd();
                }
            }
        else
            for (int i=0; i<7; i++){
                pos_old[0] = pos_new[0];
                pos_old[1] = pos_new[1];
                painter.Go_ahead();
                pos_new[0] = painter.get_pos(Head::PointName::LEFT);
                pos_new[1] = painter.get_pos(Head::PointName::RIGHT);
                for(j=0; j<2; j++){
                    glColor3d(color[j].red, color[j].green, color[j].blue);
                    glBegin(GL_LINES);
                        glVertex2d((2.0 * pos_old[j].x / WIDTH),(2.0 * pos_old[j].y / WIDTH));
                        glVertex2d((2.0 * pos_new[j].x / WIDTH),(2.0 * pos_new[j].y / WIDTH));
                    glEnd();
                }
            }

        step++;
        if (step%100 == 0)
            std::cout << "step=" << step << std::endl;
    }
    step++;
    glFlush();  //������ʾͼ��
}

void morepoint(int id){  //ѭ��
    glutPostRedisplay();
    glutTimerFunc(REFRESH_TIME, morepoint, 0);
}


int main(int argc, char *argv[])
{
    glutInit(&argc, argv);  //GLUT��ʼ��
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);  //������ʾ��ʽ
    glutInitWindowPosition(400, 100);  //���ô�������Ļ�е�λ��
    glutInitWindowSize(GRID_NUMBER, GRID_NUMBER);  //���ô��ڵĴ�С
    glutCreateWindow("Head Painter");  //���ô��ڱ���

    std::cout << "Input velocity, 1~1000 is advised\n";
    std::cin >> frequency;
    frequency += 1;

    // Ԥ����

    glutDisplayFunc(&display);  //���ƶ�̬ͼ
    glutTimerFunc(REFRESH_TIME, morepoint, 0);  //ѭ��

    glutMainLoop();  //��Ϣѭ��

    return 0;
}

