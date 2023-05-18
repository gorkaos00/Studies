//////////////////////////////////////////////////////////////////////////////////////////
// Program demonstruje  skladanie transformacji przy modelowaniu zlozonych obiektow
// skladajacych sie z wielu elementow ruchomych (ramie robota). 

#include <GL/glut.h>

// Stale wyznaczajace predkosci katowe planety i ksiezyca (w stopniach/sek.)
#define PREDKOSC_KATOWA_PLANETY  1.0
#define PREDKOSC_KATOWA_KSIEZYCA -5.0

// Wskazniki do wykorzystywanych kwadryk
GLUquadricObj *podstawaSciany;
GLUquadricObj *podstawaDyskG;
GLUquadricObj *przegubSciany;
GLUquadricObj *przegubDyskG;
GLUquadricObj *przegubDyskD;
GLUquadricObj *glowicaSciany;
GLUquadricObj *glowicaDyskG;
GLUquadricObj *glowicaDyskD;
GLUquadricObj *orbita;
GLUquadricObj* cylinder;
GLUquadricObj* cylinder2;


GLfloat rotObsY     = 40.0;
GLfloat rotObsX     = 40.0;
GLfloat rotObsZ = 0.0;
GLfloat rotPodstawy = 0.0;
GLfloat rotRamienia1= 40.0;
GLfloat rotRamienia2= -40.0;
GLfloat rotGlowicy  = 20.0; 
GLfloat rozUchwytow = 0.5;

GLint odleglos = -20;

GLfloat p_slonca = 5;
GLfloat p_planety = 2;
GLfloat p_p2 = 3;
GLfloat p_p3 = 4;
GLfloat P_orb_p2 = 12;
GLfloat p_orb_p3 = 40;
GLfloat p_ksiezyca = 0.5;
GLfloat p_orb_pl = 20;
GLfloat p_orb_ks = 5;
GLfloat pred_planety = 1.0;
GLfloat pred_ksie = 0.5; 
GLfloat pred_p1 = 0.15;
GLfloat pred_p2 = 0.5;
GLfloat spin_planety = 1;

GLfloat obrot_wyrzutni = 0;
GLfloat obrot_rakiet = 0;






//////////////////////////////////////////////////////////////////////////////////////////
// Funkcja inicjujaca elementy skladowe ramienia robota zamodelowane jako kwadryki
// 
void InicjujRamieRobota(void)
{
  // Zainicjowanie scian bocznych walca bedacego podstawa ramienia
  podstawaSciany = gluNewQuadric();
  gluQuadricDrawStyle(podstawaSciany, GLU_LINE);

  // Zainicjowanie gornej podstawy walca 
  podstawaDyskG = gluNewQuadric();
  gluQuadricDrawStyle(podstawaDyskG, GLU_LINE);

  // Zainicjowanie scian bocznych cylindrycznego przegubu ramienia
  przegubSciany = gluNewQuadric();
  gluQuadricDrawStyle(przegubSciany, GLU_LINE);

  // Zainicjowanie gornej podstawy walca 
  przegubDyskG = gluNewQuadric();
  gluQuadricDrawStyle(przegubDyskG, GLU_LINE);
  
  // Zainicjowanie dolnej podstawy walca 
  przegubDyskD = gluNewQuadric();
  gluQuadricDrawStyle(przegubDyskD, GLU_LINE);
  
  // Zainicjowanie scian bocznych cylindra glowicy 
  glowicaSciany = gluNewQuadric();
  gluQuadricDrawStyle(glowicaSciany, GLU_LINE);

  // Zainicjowanie gornej podstawy walca 
  glowicaDyskG = gluNewQuadric();
  gluQuadricDrawStyle(glowicaDyskG, GLU_LINE);
  
  // Zainicjowanie dolnej podstawy walca 
  glowicaDyskD = gluNewQuadric();
  gluQuadricDrawStyle(glowicaDyskD, GLU_LINE);

  orbita = gluNewQuadric();
  gluQuadricDrawStyle(orbita, GLU_LINE);
  
  cylinder = gluNewQuadric();
  gluQuadricDrawStyle(cylinder, GLU_LINE);
  cylinder2 = gluNewQuadric();
  gluQuadricDrawStyle(cylinder2, GLU_LINE);
  
}


//////////////////////////////////////////////////////////////////////////////////////////
// Funkcja rysujaca obraz sceny widzianej z biezacej pozycji obserwatora
// Zalozenie: Funkcja glutWireSpehere moze ryswac tylko sfere o promieniu 1  
void RysujRamieRobota(GLfloat obrotPodstawy, GLfloat obrotRamienia1, 
		      GLfloat obrotRamienia2, GLfloat obrotGlowicy, 
		      GLfloat rozstawUchwytow)
{
  // Pocztaek tworzenia ukladu wspolrzednych
  glBegin(GL_LINES);

  // Os X
  glColor3f(1.0, 0.0, 0.0);
  glVertex3f(-80.0, 0.0, 0.0);
  glVertex3f(80.0, 0.0, 0.0);

  // Os Y
  glColor3f(0.0,1.0,0.0);
  glVertex3f(0.0, -80.0, 0.0);
  glVertex3f(0.0, 80.0, 0.0);

  // Os Z
  glColor3f(0.0,0.0,1.0);
  glVertex3f(0.0, 0.0, -80.0);
  glVertex3f(0.0, 0.0, 80.0);

  // Koniec tworzenia ukladu wspolrzednych
  glEnd();

  glColor3f(1.0,1.0,1.0);




  // Przygotowanie stosu macierzy modelowania
  glPushMatrix();
  glTranslatef(-80, 0, 0);
  // Rysowanie podstawy ramienia (cylinder bez dolnej podstawy)
  glPushMatrix();
  // - sciany boczne
  glRotatef(-90.0, 1, 0, 0);
  gluCylinder(podstawaSciany, 3.0, 3.0, 1.0, 20, 4);
  
  // - gorna podstawa
  glTranslatef(0.0, 0.0, 1.0);
  gluDisk(podstawaDyskG, 0.0, 3.0, 20, 4);
  glPopMatrix();


  // Rysowanie dwoch wspornikow ramienia (prostopadlosciany)
  glPushMatrix();
  glScalef(3.0, 4.0, 1.0);
  glTranslatef(0.0, 3.0/4.0, 1.0);
  glutWireCube(1);
  glTranslatef(0.0, 0.0, -2.0);
  glutWireCube(1);  
  glPopMatrix();

  // Wyznaczenie osi obrotu ramienia w plaszczyznie pionowej
  glTranslatef(0.0, 4.0, 0.0);

  // Obrot ramienia w plaszczyznie pionowej
  glRotatef(obrotRamienia1, 0, 0, 1);

  // Modelowanie ramienia nr 1
  glPushMatrix();
  glScalef(8.0, 1.0, 1.0);
  glTranslatef(3.5/8.0, 0.0, 0.0);
  glutWireCube(1);
  glPopMatrix();
  
  // Wyznaczenie osi obrotu ramienia 2 w plaszczyznie pionowej
  glTranslatef(7.5, 0.0, 0.0);
  
  // Obrot ramienia 2 wzgledem ramienia 1
  glRotatef(obrotRamienia2, 0, 0, 1);

  // Modelowanie przegubu (walca z obiema podstawami)
  glPushMatrix();
  // - sciany boczne
  glTranslatef(0.0, 0.0, -0.5);
  gluCylinder(podstawaSciany, 1.0, 1.0, 1.0, 20, 4);
  
  // - gorna podstawa
  gluDisk(podstawaDyskG, 0.0, 1.0, 20, 4);

  // - dolna podstawa
  glTranslatef(0.0, 0.0, 1.0);
  gluDisk(podstawaDyskG, 0.0, 1.0, 20, 4);
  glPopMatrix();

  // Modelowanie ramienia nr 2
  glPushMatrix();
  glScalef(4.0, 1.0, 1.0);
  glTranslatef(2.0/4.0, 0.0, 0.0);
  glutWireCube(1);
  glPopMatrix();

  // Wyznaczenie osi obrotu glowicy
  glTranslatef(4.0, 0.0, 0.0);
  glRotatef(90, 0, 1, 0);
  glRotatef(obrotGlowicy, 0, 0, 1);

  // Modelowanie glowicy (walca z oboma podstawami)
  glPushMatrix();
  // - sciany boczne
  gluCylinder(podstawaSciany, 1.0, 1.0, 1.0, 20, 4);
  
  // - gorna podstawa
  gluDisk(podstawaDyskG, 0.0, 1.0, 20, 4);

  // - dolna podstawa
  glTranslatef(0.0, 0.0, 1.0);
  gluDisk(podstawaDyskG, 0.0, 1.0, 20, 4);
  glPopMatrix();

  // Modelowanie uchwytu (dwoch prostopadloscianow, ktore sie rozsuwaja i zsuwaja)
  glTranslatef(0.0, 0.0, 1.5);
  glScalef(0.5, 0.5, 2.0);
  glTranslatef(-rozstawUchwytow, 0.0, 0.25);
  glutWireCube(1);
  glTranslatef(rozstawUchwytow*2.0, 0.0, 0.0);
  glutWireCube(1);



  // Posprzatanie na stosie macierzy modelowania
  glPopMatrix();
  glPushMatrix();
  glTranslatef(80, 0, 0);
  glPushMatrix();
  
  glTranslatef(0, 6.5, 0);
  glColor3f(1.0, 0, 0);
  glScalef(4.23, 13, 4.23);
  glRotatef(45.0, 0, 1, 0);
  glutSolidCube(1);

  glPopMatrix();

  glPushMatrix();
  glTranslatef(0, 11.5, 0);
  glColor3f(0,1.0, 0);
  glScalef(8, 3, 8);
  glutSolidCube(1);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(3, 14, 3);
  glColor3f(0, 0, 1);
  glScalef(2, 2, 2);
  glutSolidCube(1);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(3, 14, -3);
  glColor3f(0, 0, 1);
  glScalef(2, 2, 2);
  glutSolidCube(1);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-3, 14, 3);
  glColor3f(0, 0, 1);
  glScalef(2, 2, 2);
  glutSolidCube(1);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-3, 14, -3);
  glColor3f(0, 0, 1);
  glScalef(2, 2, 2);
  glutSolidCube(1);
  glPopMatrix();


  glPopMatrix();
  //planety 
  glPushMatrix();
  glTranslatef(0, 100, 0);
  //slonce
  glPushMatrix();
  glScalef(p_slonca, p_slonca, p_slonca);
  glColor3f(1, 1, 0);
  glRotatef(90, 1, 0, 0);
  glutWireSphere(1.0,20,20);
  glPopMatrix();
 //orbity
  glPushMatrix();
  glRotatef(90, 1, 0, 0);
  glColor3f(0.7, 0.7, 0.7);
  gluDisk(orbita, P_orb_p2, P_orb_p2, 50, 50);
  glColor3f(0.23, 0.7, 0.6);
  gluDisk(orbita, p_orb_pl, p_orb_pl, 50, 50);
  glColor3f(0.3, 0.1, 0.4);
  gluDisk(orbita, p_orb_p3, p_orb_p3, 50, 50);
  glPopMatrix();
   
  //planeta 
  glPushMatrix();
  glRotatef(0.1*pred_planety,0,1,0);
  pred_planety=pred_planety-0.25;
  glTranslatef(p_orb_pl, 0, 0);
  glRotatef(90, 1, 0, 0);
  glColor3f(0.7, 0.3, 0.6);
  gluDisk(orbita, p_orb_ks, p_orb_ks, 50, 50);
  glScalef(p_planety, p_planety, p_planety);
  glColor3f(0.23, 0.7, 0.6);
  glRotatef(0.1*spin_planety, 0, 0, 1);
  spin_planety++;
  glutWireSphere(1.0, 20, 20);
  glPopMatrix();
  //ksiezyc
  glPushMatrix();
  glRotatef(0.1 * pred_planety, 0, 1, 0);
  glColor3f(0.7, 0.3, 0.6);
  glTranslatef(p_orb_pl, 0, 0);
  glRotatef(0.1 * pred_ksie, 0, 1, 0);
  pred_ksie=pred_ksie+0.5;
  glTranslatef(p_orb_ks, 0, 0);
  glRotatef(90, 1, 0, 0);
  glScalef(p_ksiezyca, p_ksiezyca, p_ksiezyca);
  glutWireSphere(1, 20, 20);
  glPopMatrix();

  //planeta 2
  glPushMatrix();
  glRotatef(0.1 * pred_p1, 0, 1, 0);
  pred_p1 = pred_p1 + 0.15;
  glTranslatef(P_orb_p2, 0, 0);
  glRotatef(90, 1, 0, 0);
  glRotatef(0.1 * spin_planety, 0, 0, 1);
  glScalef(p_p2, p_p2, p_p2);
  glColor3f(0.7, 0.7, 0.7);
  glutWireSphere(1.0, 20, 20); 
  glPopMatrix();

  glPushMatrix();
  glRotatef(0.1 * pred_p2, 0, 1, 0);
  pred_p2 = pred_p2 - 0.5;
  glTranslatef(p_orb_p3, 0, 0);
  glRotatef(90, 1, 0, 0);
  glRotatef(0.1 * spin_planety, 0, 0, 1);
  glScalef(p_p3, p_p3, p_p3);
  glColor3f(0.3, 0.1, 0.4);
  glutWireSphere(1.0, 20, 20);
  glPopMatrix();
  glPopMatrix();

  //wyrzutnia
  glPushMatrix();
  glColor3d(1, 1, 1);
  glRotatef(90, 1, 0, 0);
  glRotatef(180, 0, 1, 0);
  glRotatef(obrot_wyrzutni, 0, 0, 1);
  glPushMatrix();
  gluCylinder(cylinder, 2.5, 2.5, 1, 20, 4);
  glPopMatrix();
  
  glPushMatrix();
  glTranslatef(0, 0, 1);
  gluCylinder(cylinder, 0.75, 0.75, 3, 20, 4);
  glPopMatrix();
 
  glPushMatrix();
  
  glTranslatef(0, 0, 4.25);
  glRotatef(obrot_rakiet, 1, 0, 0);
  glutWireSphere(0.75, 20, 20);
  glTranslatef(0, 0, -0.25);
  glTranslatef(2, 1, -0.75);
  glRotatef(90, 1, 0, 0);
  gluCylinder(cylinder2,0.5, 0.5, 5, 20, 4);
  glRotatef(-90, 1, 0, 0);
  glTranslatef(-4, 0, 0);
  glRotatef(90, 1, 0, 0);
  gluCylinder(cylinder2, 0.5, 0.5, 5, 20, 4);
  glRotatef(-90, 1, 0,0);
  glTranslatef(2, -1, 0.75);
  glScalef(4, 1.25, 0.5);
  glutWireCube(1);
  glPopMatrix();

  glPopMatrix();

}




//////////////////////////////////////////////////////////////////////////////////////////
// Funkcja generujaca pojedyncza klatke animacji
void WyswietlObraz(void)
{
  // Wyczyszczenie bufora ramki i bufora glebokosci
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  
  // Powielenie macierzy na wierzcholku stosu 
  glPushMatrix();

  // Wyznaczenie polozenia obserwatora (przeksztalcenie uladu wspolrzednych 
  // sceny do ukladu wspolrzednych obserwatora). 
  glTranslatef(0, 0, odleglos);
  glRotatef(rotObsX, 1, 0, 0);
  glRotatef(rotObsY,0,1,0);
  glRotatef(rotObsZ, 0, 0, 1);


  // Generacja obrazu sceny w niewidocznym buforze ramki
  RysujRamieRobota(rotPodstawy, rotRamienia1, rotRamienia2, rotGlowicy, rozUchwytow);

  // Usuniecie macierzy lezacej na  wierzcholku stosu (powrot do stanu
  // sprzed wywolania funkcji)
  glPopMatrix();

  // Przelaczenie buforow ramki
  glutSwapBuffers();

 
}

//////////////////////////////////////////////////////////////////////////////////////////
// Funkcja ustawiajaca parametry rzutu perspektywicznego i rozmiary viewportu
void UstawParametryWidoku(int szerokosc, int wysokosc)
{
  // Ustawienie parametrow viewportu
  glViewport(0, 0, szerokosc, wysokosc);

  // Przejscie w tryb modyfikacji macierzy rzutowania
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(40.0, (float)szerokosc/(float)wysokosc, 1.0, 1000.0);

  // Przejscie w tryb modyfikacji macierzy przeksztalcen geometrycznych
  glMatrixMode(GL_MODELVIEW);

  // Zmiana macierzy znajdujacej sie na wierzcholku stosu na macierz jednostkowa 
  glLoadIdentity();
}

//////////////////////////////////////////////////////////////////////////////////////////
// Funkcja klawiszy specjalnych
void ObslugaKlawiszySpecjalnych(int klawisz, int x, int y)
{
  switch(klawisz)
    {
    case GLUT_KEY_UP:
        rotObsX = rotObsX + 1.0;
      break;

    case GLUT_KEY_DOWN:
        rotObsX = rotObsX - 1.0;
      break;

    case GLUT_KEY_LEFT:
        rotObsY =  rotObsY - 1.0;
      break;

    case GLUT_KEY_RIGHT:
        rotObsY = rotObsY + 1.0;
      break;
    }
}
//////////////////////////////////////////////////////////////////////////////////////////
// Funkcja obslugi klawiatury
void ObslugaKlawiatury(unsigned char klawisz, int x, int y)
{

  switch(klawisz)
    {
    case '2':
      rotRamienia1 = (rotRamienia1 < 90.0) ? rotRamienia1 + 1.0 : rotRamienia1;
      break;

    case '@':
      rotRamienia1 = (rotRamienia1 > 0.0) ? rotRamienia1 - 1.0 : rotRamienia1;
      break;

    case '3':
      rotRamienia2 = (rotRamienia2 < 0.0) ? rotRamienia2 + 1.0 : rotRamienia2;
      break;

    case '#':
      rotRamienia2 = (rotRamienia2 > -90.0) ? rotRamienia2 - 1.0 : rotRamienia2;
      break;

    case '4':
      rotGlowicy = (rotGlowicy < 360.0) ? rotGlowicy + 1.0 : rotGlowicy;
      break;

    case '$':
      rotGlowicy = (rotGlowicy > 0.0) ? rotGlowicy - 1.0 : rotGlowicy;
      break;

    case '5':
      rozUchwytow = (rozUchwytow < 1.5) ? rozUchwytow + 0.1 : rozUchwytow;
      break;

    case '%':
      rozUchwytow = (rozUchwytow > 0.5) ? rozUchwytow - 0.1 : rozUchwytow;
      break;
    case '[':
        rotObsZ =  rotObsZ + 1.0;
        break;
    case ']':
        rotObsZ =  rotObsZ - 1.0;
        break;
    case '=':
        odleglos = (odleglos < -20) ? odleglos + 1 : odleglos;
        break;
    case '-':
        odleglos = (odleglos > -300) ? odleglos - 1 : odleglos;
        break;
    case 'a':
        obrot_wyrzutni = obrot_wyrzutni - 1.0;
        break;
    case 'd':
        obrot_wyrzutni = obrot_wyrzutni + 1.0;
        break;
    case 'w':
        obrot_rakiet = obrot_rakiet + 1.0;
        break;
    case 's':
        obrot_rakiet = obrot_rakiet - 1.0;
        break;

  }

  
  if(klawisz == 27)
      exit(0);      
}

//////////////////////////////////////////////////////////////////////////////////////////
// Glowna funkcja programu
int  main(int argc, char **argv)
{
  // Zainicjowanie biblioteki GLUT
  glutInit(&argc, argv);

  // Ustawienie trybu wyswietlania
  glutInitDisplayMode (GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);

  // Ustawienie polozenia dolenego lewego rogu okna
  glutInitWindowPosition(100, 100);

  // Ustawienie rozmiarow okna
  glutInitWindowSize(400, 400);

  // Utworzenie okna
  glutCreateWindow("Robot");

  // Odblokowanie bufora glebokosci
  glEnable(GL_DEPTH_TEST);

  // Ustawienie funkcji wykonywanej na danych w buforze glebokosci
  glDepthFunc(GL_LEQUAL);

  // Ustawienie wartosci czyszczacej zawartosc bufora glebokosci
  glClearDepth(1000.0);

  // Ustawienie koloru czyszczenia bufora ramki
  glClearColor (0.0, 0.3, 0.0, 0.0);
 
  // Zarejestrowanie funkcji (callback) wyswietlajacej
  glutDisplayFunc(WyswietlObraz);

  // Zarejestrowanie funkcji (callback) wywolywanej za kazdym razem kiedy
  // zmieniane sa rozmiary okna
  glutReshapeFunc(UstawParametryWidoku);

  // Zarejestrowanie funkcji wykonywanej gdy okno nie obsluguje
  // zadnych zadan
  glutIdleFunc(WyswietlObraz);

  // Zarejestrowanie funkcji obslugi klawiatury
  glutKeyboardFunc(ObslugaKlawiatury);

  // Zarejestrowanie funkcji obslugi klawiszy specjalnych
  glutSpecialFunc(ObslugaKlawiszySpecjalnych);


  // Zainicjowanie kwadryk tworzacych ramie robota
  InicjujRamieRobota();


  // Obsluga glownej petli programu (wywolywanie zarejestrowanych callbackow
  // w odpowiedzi na odbierane zdarzenia lub obsluga stanu bezczynnosci)
  glutMainLoop();

  return 0;
}
