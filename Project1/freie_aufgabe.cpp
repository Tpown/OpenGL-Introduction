// GD-Praktikum:   teil_1.cpp  (Teil 1: Start-Programm)
// Hergenroether / Groch    Last Update: 05.07.2014

#include <iostream> 
#include <GL/freeglut.h>         //lädt alles für OpenGL
#include "Wuerfel.h"

float fRotation = 0.0; // globale Variable :-(
float fBewegung = 0.0;

void Init()	
{
   // Hier finden jene Aktionen statt, die zum Programmstart einmalig 
   // durchgeführt werden müssen

	glEnable(GL_DEPTH_TEST);
	glClearDepth(1.0);
}

void RenderScene() //Zeichenfunktion
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   // Hier befindet sich der Code der in jedem Frame ausgefuehrt werden muss
   glLoadIdentity ();   // Aktuelle Model-/View-Transformations-Matrix zuruecksetzen

   gluLookAt(0., 2., 4., 0., 0., 0., 0., 1., 0.); 

   // Bodenplatte
   glPushMatrix(); //Matrix wird auf den Stack gesichert
   glTranslatef(0, -0.1, 0);
   glScalef(15, 0.2, 15);
   WuerfelGrau(0.2);
   glPopMatrix(); //Matrix wird vom Stack geholt und gesetzt

   // Fortbewegung des Busses
   glRotatef(fRotation, 0, 1, 0);
   glTranslatef(0.75, 0, fBewegung);

   // Frontscheibe
   glPushMatrix(); //Matrix wird auf den Stack gesichert
   glTranslatef(0, 0.15, 0.8);
   glScalef(0.8, 0.5, 0.1);
   WuerfelRad(0.2);
   glPopMatrix(); //Matrix wird vom Stack geholt und gesetzt

   // Ruecklichter
   glPushMatrix(); //Matrix wird auf den Stack gesichert
   glTranslatef(-0.08, 0.15, 1.20);
   glScalef(0.4, 0.2, 0.2);
   Ruecklicht(0.1);
   glPopMatrix(); //Matrix wird vom Stack geholt und gesetzt

   glPushMatrix(); //Matrix wird auf den Stack gesichert
   glTranslatef(0.08, 0.15, 1.20);
   glScalef(0.4, 0.2, 0.2);
   Ruecklicht(0.1);
   glPopMatrix(); //Matrix wird vom Stack geholt und gesetzt

   // Raeder links
   glPushMatrix(); //Matrix wird auf den Stack gesichert
   glTranslatef(-0.12, 0.05, 1.15);
   glScalef(0.2, 0.4, 0.4);
   WuerfelRad(0.2);
   glPopMatrix(); //Matrix wird vom Stack geholt und gesetzt

   glPushMatrix(); //Matrix wird auf den Stack gesichert
   glTranslatef(-0.12, 0.05, 0.85);
   glScalef(0.2, 0.4, 0.4);
   WuerfelRad(0.2);
   glPopMatrix(); //Matrix wird vom Stack geholt und gesetzt

   // Raeder rechts
   glPushMatrix(); //Matrix wird auf den Stack gesichert
   glTranslatef(0.12, 0.05, 1.15);
   glScalef(0.2, 0.4, 0.4);
   WuerfelRad(0.2);
   glPopMatrix(); //Matrix wird vom Stack geholt und gesetzt

   glPushMatrix(); //Matrix wird auf den Stack gesichert
   glTranslatef(0.12, 0.05, 0.85);
   glScalef(0.2, 0.4, 0.4);
   WuerfelRad(0.2);
   glPopMatrix(); //Matrix wird vom Stack geholt und gesetzt

   // Bus
   glPushMatrix(); //Matrix wird auf den Stack gesichert
   glTranslatef(0.0, 0.12, 1);
   glScalef(1, 1, 2);
   Wuerfel(0.2);
   glPopMatrix(); //Matrix wird vom Stack geholt und gesetzt



   glutSwapBuffers();
}

void Reshape(int width,int height)
{
   // Hier finden die Reaktionen auf eine Veränderung der Größe des 
   // Graphikfensters statt
	// Matrix für Transformation: Frustum->viewport
	glMatrixMode(GL_PROJECTION);
	// Aktuelle Transformations-Matrix zuruecksetzen
	glLoadIdentity();
	// Viewport definieren
	glViewport(0, 0, width, height);
	// Frustum definieren (siehe unten)
	// glOrtho(-1., 1., -1., 1., 0.0, 2.0);
	// gluPerspective(senkr. Oeffnungsw., Seitenverh., zNear, zFar);
	gluPerspective(45., 1., 0.1, 10.0);
	// Matrix für Modellierung/Viewing
	glMatrixMode(GL_MODELVIEW);
}

void Animate(int value)
{
	// Hier werden Berechnungen durchgeführt, die zu einer Animation der Szene  
	// erforderlich sind. Dieser Prozess läuft im Hintergrund und wird alle 
	// 1000 msec aufgerufen. Der Parameter "value" wird einfach nur um eins 
	// inkrementiert und dem Callback wieder uebergeben. 
	std::cout << "value=" << value << std::endl;
	
	if (fBewegung >= -0.8) {
	fBewegung = fBewegung - 0.005;
	}
	else {
		if (fRotation <= 90.0) {
		fRotation = fRotation + 1.0;
		fBewegung = fBewegung - 0.0005;
		}
		else {
			if (fBewegung >= -1.5) {
			fBewegung = fBewegung - 0.005;
			}
			else {
				if (fRotation <= 180.0) {
					fRotation = fRotation + 0.5;
					fBewegung = fBewegung - 0.0005;
				}
				else {
					if (fBewegung >= -2.0) {
						fBewegung = fBewegung - 0.005;
					}
				}
			}
		}
	}

   // RenderScene aufrufen
   glutPostRedisplay();
   // Timer wieder registrieren - Animate wird so nach 10 msec mit value+=1 aufgerufen.
   int wait_msec = 10;
   glutTimerFunc(wait_msec, Animate, ++value);
}

int main(int argc, char **argv)
{
   glutInit( &argc, argv );                // GLUT initialisieren
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize( 600, 600 );         // Fenster-Konfiguration
   glutCreateWindow( "Phong; Puya" );   // Fenster-Erzeugung
   glutDisplayFunc( RenderScene );         // Zeichenfunktion bekannt machen
   glutReshapeFunc( Reshape );
   // TimerCallback registrieren; wird nach 10 msec aufgerufen mit Parameter 0  
   glutTimerFunc( 10, Animate, 0);
   Init();
   glutMainLoop();
   return 0;
}
