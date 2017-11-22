

#include <stdio.h>
#include <vector>
#include <limits.h>
#include <math.h>
#include <GL/glut.h>

using namespace std;

double WINDOW_WIDTH = 900;   // window screen width
double WINDOW_HEIGHT = 900;  // window screen height

class Point {
 public:
  double x;
  double y;
  double z;
  Point(){};
  Point(double X, double Y, double Z) {
    x = X;
    y = Y;
    z = Z;
  };
};

class DirectionUnitVector {
 public:
  double x;
  double y;
  double z;
  DirectionUnitVector(){};
  DirectionUnitVector(double X, double Y, double Z) {
    double mang = sqrt(X * X + Y * Y + Z * Z);
    x = X / mang;
    y = Y / mang;
    z = Z / mang;
  };
  DirectionUnitVector crossProductWith(double x2, double y2, double z2) {
    double nX = y * z2 - z * y2;
    double nY = -(x * z2 - z * x2);
    double nZ = (x * y2 - y * x2);
    double mang = sqrt(nX * nX + nY * nY + nZ * nZ);
    DirectionUnitVector dNew(nX / mang, nY / mang, nZ / mang);
    return dNew;
  }
  double dotProductWith(double x2, double y2, double z2) {
    return x * x2 + y * y2 + z * z2;
  }
};

int Ymin, Ymax, n;
double camera[3];

DirectionUnitVector viewingDir;

vector<Point> points;

int max(int a, int b) { return a >= b ? a : b; }

int min(int a, int b) { return a <= b ? a : b; }

void drawAxis() {
  // draw axis
  glColor3f(1.0, 0.0, 0.0);
  glBegin(GL_LINES);

  glVertex3f(-WINDOW_WIDTH / 2, 0, 0);
  glVertex3f(WINDOW_WIDTH / 2, 0, 0);

  glColor3f(0.0, 1.0, 0.0);
  glBegin(GL_LINES);

  glVertex3f(0, -WINDOW_WIDTH / 2, 0);
  glVertex3f(0, WINDOW_WIDTH / 2, 0);

  glColor3f(0.0, 0.0, 1.0);
  glBegin(GL_LINES);

  glVertex3f(0, 0, -WINDOW_WIDTH / 2);
  glVertex3f(0, 0, WINDOW_WIDTH / 2);

  glEnd();

  glFlush();
}

void drawLine(int x1, int y1, int x2, int y2) {
  glColor3f(1.0, 0.0, 0.0);
  glBegin(GL_LINES);

  glVertex2f(x1, y1);
  glVertex2f(x2, y2);

  glEnd();

  glFlush();
}

void Init() {
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glOrtho(-WINDOW_WIDTH / 2.0, WINDOW_WIDTH / 2.0, -WINDOW_HEIGHT / 2.0,
          WINDOW_WIDTH / 2.0, -WINDOW_HEIGHT / 2.0, WINDOW_WIDTH / 2.0);
  glEnable(GL_DEPTH_TEST);

  gluLookAt(camera[0], camera[1], camera[2], /* look from camera XYZ */
            0, 0, 0,                         /* look at the origin */
            0, 1, 0);                        /* positive Y up vector */
}

void hiddenSurfaceRemovalAlgo(void) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  drawAxis();

  // surface 1 (1, 2, 3, 4)
  DirectionUnitVector v12(points[2].x - points[1].x, points[2].y - points[1].y,
                          points[2].z - points[1].z);
  DirectionUnitVector v14(points[4].x - points[1].x, points[4].y - points[1].y,
                          points[4].z - points[1].z);
  DirectionUnitVector v14x12 = v14.crossProductWith(v12.x, v12.y, v12.z);

  if (v14x12.dotProductWith(viewingDir.x, viewingDir.y, viewingDir.z) > 0) {
    glColor3f(0.5f, 0.5f, 0);
    glBegin(GL_QUADS);
    glVertex3f(points[1].x, points[1].y, points[1].z);
    glVertex3f(points[2].x, points[2].y, points[2].z);
    glVertex3f(points[3].x, points[3].y, points[3].z);
    glVertex3f(points[4].x, points[4].y, points[4].z);
    glEnd();
  }

  // surface 2 (5, 6, 7, 8)
  DirectionUnitVector v56(points[6].x - points[5].x, points[6].y - points[5].y,
                          points[6].z - points[5].z);
  DirectionUnitVector v58(points[8].x - points[5].x, points[8].y - points[5].y,
                          points[8].z - points[5].z);
  DirectionUnitVector v56x58 = v56.crossProductWith(v58.x, v58.y, v58.z);

  if (v56x58.dotProductWith(viewingDir.x, viewingDir.y, viewingDir.z) > 0) {
    glColor3f(1.0f, 1.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex3f(points[5].x, points[5].y, points[5].z);
    glVertex3f(points[6].x, points[6].y, points[6].z);
    glVertex3f(points[7].x, points[7].y, points[7].z);
    glVertex3f(points[8].x, points[8].y, points[8].z);
    glEnd();
  }

  // surface 3 (2, 6, 7, 3)
  DirectionUnitVector v23(points[3].x - points[2].x, points[3].y - points[2].y,
                          points[3].z - points[2].z);
  DirectionUnitVector v26(points[6].x - points[2].x, points[6].y - points[2].y,
                          points[6].z - points[2].z);
  DirectionUnitVector v23x26 = v23.crossProductWith(v26.x, v26.y, v26.z);

  if (v23x26.dotProductWith(viewingDir.x, viewingDir.y, viewingDir.z) > 0) {
    glColor3f(0.5f, 0, 0.5f);
    glBegin(GL_QUADS);
    glVertex3f(points[2].x, points[2].y, points[2].z);
    glVertex3f(points[6].x, points[6].y, points[6].z);
    glVertex3f(points[7].x, points[7].y, points[7].z);
    glVertex3f(points[3].x, points[3].y, points[3].z);
    glEnd();
  }

  // surface 4 (5, 6, 2, 1)
  DirectionUnitVector v51(points[1].x - points[5].x, points[1].y - points[5].y,
                          points[1].z - points[5].z);
  DirectionUnitVector v51x56 = v51.crossProductWith(v56.x, v56.y, v56.z);

  if (v51x56.dotProductWith(viewingDir.x, viewingDir.y, viewingDir.z) > 0) {
    glColor3f(0, 0.5f, 0.5f);
    glBegin(GL_QUADS);
    glVertex3f(points[5].x, points[5].y, points[5].z);
    glVertex3f(points[6].x, points[6].y, points[6].z);
    glVertex3f(points[2].x, points[2].y, points[2].z);
    glVertex3f(points[1].x, points[1].y, points[1].z);
    glEnd();
  }

  // surface 5 (4, 8, 7, 3)
  DirectionUnitVector v87(points[7].x - points[8].x, points[7].y - points[8].y,
                          points[7].z - points[8].z);
  DirectionUnitVector v84(points[4].x - points[8].x, points[4].y - points[8].y,
                          points[4].z - points[8].z);
  DirectionUnitVector v87x84 = v87.crossProductWith(v84.x, v84.y, v84.z);

  if (v87x84.dotProductWith(viewingDir.x, viewingDir.y, viewingDir.z) > 0) {
    glColor3f(0, 1, 1);
    glBegin(GL_QUADS);
    glVertex3f(points[4].x, points[4].y, points[4].z);
    glVertex3f(points[8].x, points[8].y, points[8].z);
    glVertex3f(points[7].x, points[7].y, points[7].z);
    glVertex3f(points[3].x, points[3].y, points[3].z);
    glEnd();
  }

  // surface 6 (1, 5, 8, 4)
  DirectionUnitVector v58x51 = v58.crossProductWith(v51.x, v51.y, v51.z);

  if (v58x51.dotProductWith(viewingDir.x, viewingDir.y, viewingDir.z) > 0) {
    glColor3f(1, 0, 1);
    glBegin(GL_QUADS);
    glVertex3f(points[1].x, points[1].y, points[1].z);
    glVertex3f(points[5].x, points[5].y, points[5].z);
    glVertex3f(points[8].x, points[8].y, points[8].z);
    glVertex3f(points[4].x, points[4].y, points[4].z);
    glEnd();
  }
  glFlush();
}

int main(int argc, char** argv) {
  n = 8;
  int i = 0;
  double x, y, z;
  camera[0] = 20;
  camera[1] = 20;
  camera[2] = -20;
  Point tmp(0, 0, 0);
  points.push_back(tmp);  // tmp data to start counting vector from 1

  printf("Note: Enter points of the cube in continuous clockwise order.\n");
  for (i = 0; i < n; i++) {
    printf("Enter X, Y, Z of the point: \n");
    scanf("%lf %lf %lf", &x, &y, &z);
    Point point(x, y, z);
    points.push_back(point);
  }

  printf("Enter the viewing direction Xi, Yj, Zk: \n");
  scanf("%lf %lf %lf", &x, &y, &z);
  viewingDir.x = x, viewingDir.y = y, viewingDir.z = z;
  printf("Note: looking from camera X: %lf , Y: %lf, Z: %lf towards origin.\n",
         camera[0], camera[1], camera[2]);

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
  glutCreateWindow("Hidden Surface Removal algorithm");
  Init();
  glutDisplayFunc(hiddenSurfaceRemovalAlgo);
  glutMainLoop();

  return 0;
}
