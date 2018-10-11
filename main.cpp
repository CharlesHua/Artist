/*****************************************************************************************
模拟 大卫·史瑞格里(David Shrigley) 的作品《艺术家》的绘画模式

由于像素限制，难以做到真实作品那样的清晰度。


*****************************************************************************************/
#include <GL/glut.h>
#include <iostream>
#include <math.h>
#include "16807RNG.h"
#include "artist.h"
//using namespace std;

#define PI 3.1415926535897
#define WIDTH 601 //图形界面横向元素数
#define REFRESH_TIME 1 //循环时间间隔
#define GRID_NUMBER 600  //除去外框之后的格点
#define DEBUG 0 //是否处于调试状态

int center = GRID_NUMBER / 2;  //中心点坐标

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
    glFlush();  //立刻显示图像
}

void morepoint(int id){  //循环
    glutPostRedisplay();
    glutTimerFunc(REFRESH_TIME, morepoint, 0);
}


int main(int argc, char *argv[])
{
    glutInit(&argc, argv);  //GLUT初始化
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);  //设置显示方式
    glutInitWindowPosition(400, 100);  //设置窗口在屏幕中的位置
    glutInitWindowSize(GRID_NUMBER, GRID_NUMBER);  //设置窗口的大小
    glutCreateWindow("Head Painter");  //设置窗口标题

    std::cout << "Input velocity, 1~1000 is advised\n";
    std::cin >> frequency;
    frequency += 1;

    // 预处理

    glutDisplayFunc(&display);  //绘制动态图
    glutTimerFunc(REFRESH_TIME, morepoint, 0);  //循环

    glutMainLoop();  //消息循环

    return 0;
}

