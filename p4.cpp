//COSC-332		Wed. 9-5-14		Homework-1   (scale was added)
//////////////////////////////////////////

#include <iostream>
using namespace std;
#include <gl/glut.h>
#include <ctime>




#define windowx 900
#define windowy 900






int mousex,mousey,i,j,player=0, jogada=0, winner=99, draw = 0;
GLfloat x=0.,y=0.,z=0., spin=0., translation_move = 0.666666667;
int matrix[3][3];


int space = (windowx*translation_move)/2;


GLfloat mat_ambient[]={.8,.8,.8, 1.0};
GLfloat mat_diffuse[]={0.5,.5,0.5,1};
GLfloat mat_diffuse_red[]={0.7,0,0,1};//(R,G,B, transparency)
GLfloat mat_diffuse_green[]={0,.7,0,1};
GLfloat mat_diffuse_blue[]={0,0,0.7,1};
GLfloat mat_specular[]={0.8,0.8,0.8, 1.0}; //IDK
GLfloat mat_shininess[]={128.};	//this needs specular (work together)
GLfloat light0_position[]={1., 1., -5., .0};


void xis (GLfloat x, GLfloat y){
    glPushMatrix();
    glLightfv(GL_LIGHT0,GL_DIFFUSE,mat_diffuse_red);
    glColor3f(0, 0, 0.7);
    glTranslatef(x, y, -1);
    glutSolidCube(.46);
    glPopMatrix();
}

void circle (GLfloat x, GLfloat y){
    glPushMatrix();
    glLightfv(GL_LIGHT0,GL_DIFFUSE,mat_diffuse_blue);
    glColor3f(0.7, 0, 0);
    glTranslatef(x, y, -1);
    glutSolidTorus(.01, .23, 20, 20);
    glPopMatrix();
}


bool check_win(){
    int i,j;
    int check_row = 0, check_column=0, check_diagonal1 = 0,check_diagonal2 = 0, draw = 0;
    
    for(i=0;i<=2;i++){
        
        for(j=0;j<=2;j++){
            draw+=matrix[i][j];
            check_row+=matrix[i][j];
            check_column+=matrix[j][i];
            if(i==j){
                check_diagonal1+=matrix[i][j];
            }
            if((i+j)==2){
                check_diagonal2+=matrix[i][j];
            }
            if (check_row==3 | check_column ==3 | check_diagonal1 ==3 | check_diagonal2 ==3){
                winner = 0;
                printf("Blue WINS\n");
                return true;
            }
            if (check_row==30 | check_column ==30 | check_diagonal1 ==30| check_diagonal2 ==30){
                winner = 1;
                printf("Red WINS\n");
                return true;
            }
            if (draw == 45){
                draw=1;
                printf("DRAW!\n");
                return true;
            }
        }
        
        
        check_row = 0;
        check_column = 0;
    }
    return false;
}



void init(void)
{	glClearColor(1,1,1,1);	//background

    draw=0;
	glShadeModel(GL_FLAT);	//default: SMOOT
    
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
    glLightfv(GL_LIGHT0,GL_POSITION,light0_position);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,mat_diffuse_red);
    glLightfv(GL_LIGHT0,GL_SPECULAR,mat_ambient);
    
    //glEnable(GL_LIGHTING);
    //glEnable(GL_LIGHT0);
    
    glEnable(GL_DEPTH_TEST);
    
    
    //GERNERATE MATRIX WITH 0's
    for(i=0;i<=2;i++){
        for(j=0;j<=2;j++){
            matrix[i][j]=0;
        }
    }


}









void display(void)
{ glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 
        int i,j;
    
    glPushMatrix();
    glColor3f(.0, .0, .0);
    glTranslatef(0, 0, .7);
    glutSolidCube(2);
    glPopMatrix();
    
    for(i=0;i<=2;i++){
        for(j=0;j<=2;j++){
            glPushMatrix();
            glColor3f(1, 1, 1);
            glTranslatef((GLfloat)(translation_move*(j-1)), (GLfloat)(translation_move*((i-1))*-1),-1);
            glutSolidCube(.65);
            glPopMatrix();
            
        }
    }
    
 

    for(i=0;i<=2;i++){
        for(j=0;j<=2;j++){
            if(matrix[i][j]==1){
                xis((GLfloat)(translation_move*(j-1)), (GLfloat)(translation_move*((i-1))*-1));
            }
            if(matrix[i][j]==10){
                circle((GLfloat)(translation_move*(j-1)), (GLfloat)(translation_move*((i-1))*-1));
            }
        }
    }

    if(check_win()==true) {
        glPushMatrix();
        glTranslatef(0, 0, -1.5);
        if (winner == 0){
            glColor3f(0, 0, .7);
            glutSolidCube(1);
            init();
            
        }
        if (winner == 1) {
            glColor3f(.7, 0, 0);
            glutSolidCube(1);
            init();
        }
        if (draw==1) {
            glColor3f(0, 0.7, 0);
            glutSolidCube(1);
            init();
        }
        glPopMatrix();
    }

    
    
  glutSwapBuffers(); 
}



void spinDisplay()
{	spin+=1.; if(spin>360.)spin=0.;
	glutPostRedisplay();
}





void keyboard(unsigned char key, int xx, int yy)
{	switch(key)
	{
	case 'r'	:	init(); break;
	} 
	glutPostRedisplay();
}


void mouse(int button, int state, int xx, int yy)
{
    player = jogada%2;
    //printf("%d, %d\n", xx,yy);
    int i,j;
    
    for(i=0;i<=2;i++){
        for(j=0;j<=2;j++){
            if (xx > space*j & xx< space*(j+1) & yy > space*i & yy < space*(i+1)){
                if(player==0){
                    if(matrix[i][j]==0){
                        matrix[i][j] = 1;
                        jogada++;
                    }
                }else{
                    if(matrix[i][j]==0){
                    matrix[i][j] = 10;
                    jogada++;
                    }
                }
            }
        
        }
    
    }
    

    
    
    for(i=0;i<=2;i++){
        printf("%d %d %d\n", matrix[i][0],matrix[i][1],matrix[i][2]);
    }
    printf("\n");

    glutPostRedisplay();
    
    
    
}

void reshape(int w, int h)
{
    glViewport(0.,0.,windowx,windowy);
    glMatrixMode(GL_PROJECTION);
    
    glLoadIdentity();

    //glOrtho(1,1,0,1,-1,4);
    gluPerspective(80., (GLfloat) w/(GLfloat) h, -.1, 190.);

    glMatrixMode(GL_MODELVIEW);
	
    glLoadIdentity();
    
    
}

int main(int argc, char **argv)
{ glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize (windowx, windowy); glutInitWindowPosition(0,0);
  glutCreateWindow("Janelinha");
    
    
  init(); 
  glutDisplayFunc(display);
  glutMouseFunc(mouse);
  glutKeyboardFunc(keyboard);
  glutReshapeFunc(reshape);
  glutMainLoop(); 
}