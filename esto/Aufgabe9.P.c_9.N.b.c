/****************************************************************************************
 *
 * Traversierung von ungerichteten Graphen
 * =======================================
 *
 * = von einem Startknoten alle Knoten besuchen, die von ihm aus erreicht werden koennen!
 * Entweder durch Depth First Search = DFS = Tiefendurchlauf, Sohne vor Geschwister
 * Oder     durch Breath First Search = BFS = Breitendurchlauf, Geschwister vor Sohn
 */

#include <stdio.h>
#include <stdlib.h>
#define VERBUNDEN 1
#define UNVERBUNDEN -1 /* Kosten = unendlich */
#define MAX_ELEMENTE 100
#define TRUE 1
#define FALSE 0

/* DT Graph */
typedef struct {
  int adjMatrix[MAX_ELEMENTE][MAX_ELEMENTE]; /* samt Kosten */
  int anzKnoten;
} Graph;

int visited[MAX_ELEMENTE]; /* implizit mit 0 initialisiert */

/* Alle mit dem Bezugsknoten direkt verbundenen Knoten
   werden im Array alleNachbar[] gespeichert (call-by-ref).
   Rueckgabewert der Funktion = Anzahl der Knoten,
   die mit dem Bezugsknoten direkt verbunden sind. */
int getAlleNachbarnZu(int bezugsKnoten, Graph graph, int alleNachbarn[]);

/* Knoten wird bearbeitet - original aus Skript -
   hier implementiert als Ausgabe der Knotennummer. */
void process(int knoten);


/* WICHTIG !!!Zur Loesung der Aufgaben nicht relevante Funktionen!!!
*  Also erstmal voellig ignorieren!!!
*  Es handelt sich um Hilfsfunktionen zum Testen bzw. zur Implementierung der Queue
*/

/* alle Elemente von adjMatrix[][] werden auf UNVERBUNDEN initialisiert. */
void resetToUnverbunden(int adjMatrix[MAX_ELEMENTE][MAX_ELEMENTE]);

/* Adjazenzmatrix zum Graphen wird hier ausgegeben. */
void printMatrix(int matrix[MAX_ELEMENTE][MAX_ELEMENTE], int anz);

/* alle Knoten auf "Unvisited" oder auf "nicht besucht" zurückgesetzt. */
void resetVisited();

/* Hilfsfunktionen und -Datenstrukturen fuer die notwendige Queue:
  1-zu-1-Kopie aus dem Skript, allerdings wurde zur Vereinfachung
  T* durch int ersetzt, da die Queue sich die Graphknotennummern merken soll!
  Damit muss ueberall auch ->data durch .data ersetzt werden,
  da data nun keine Zeiger auf int (int*) ist, sondern direkt ein int!
  Damit wird die Equal-Funktion trivial, naemlich Vergleich zweier int-Zahlen,
  also beispielsweise np1.data == item statt Equal(np1.data,item)

  Betrachten Sie diese Hilfsfunktionen gar nicht,
  sondern nutzen Sie die Funktionen Get und Put einfach!!!
*/
typedef struct node {
 int data;
 struct node* next;
} Node, *nodeptr;

typedef struct list {
 nodeptr first, last;
} List, *listptr;


void Init(listptr L);
int IsEmpty(List L);
nodeptr newnode(int item);
void AppendLast(int item, listptr L);
void Delete(int item, listptr L);

/* eine Queue wird als Liste, genauer als List* implementiert */
typedef listptr Queue;


/* Zur Loesung von Aufgabe 9.P.c anwenden, aber nicht unbedingt verstehen! */

/* erzeugt eine leere Queue
  - notwendig, da eine Deklaration einer Queue-Variable noch nicht reicht! */
Queue erzeugeQueueInstanz();

/* Fuegt die uebergebene Knotennummer an die Warteschlange q an. */
void Put(int zuSpeicherndeKnotenNr, Queue q);

/* Liefert die vorderste Knotennummer aus der Warteschlage q. */
int Get(Queue q);

/* hier geht das eigentliche BFS-Verfahren los. */
void BFS(int v, Graph graph) /* v = zunaechst Startknoten der Breitensuche */
{
  int aktNachbarn[MAX_ELEMENTE], aktAnzNachbarn, aktNachbarKnoten, aktNachbarIndex;
  Queue Q = erzeugeQueueInstanz();

  /* TODO: Ihre Implementierung zur Aufgabe 9.P.c */

}


/* hier geht das eigentliche DFS-Verfahren los. */
void DFS(int bezugsKnoten, Graph graph) /* DFS beginnend bei bezugsKnoten */
{
  int aktNachbarn[MAX_ELEMENTE] = {0};
  int aktAnzNachbarn, aktNachbarIndex;
  int aktNachbarKnoten;

  /* TODO: Ihre Implementierung zur Aufgabe 9.N.b */

}


int main() {
  int aktKnoten;
  Graph testGraph;

  /* Init TestGraph - Werte wie in Aufgabe 9.P.a */
  testGraph.anzKnoten = 6;

  resetToUnverbunden(testGraph.adjMatrix);

  testGraph.adjMatrix[1][2] = VERBUNDEN;
  testGraph.adjMatrix[1][3] = VERBUNDEN;
  testGraph.adjMatrix[2][1] = VERBUNDEN;
  testGraph.adjMatrix[2][5] = VERBUNDEN;
  testGraph.adjMatrix[3][1] = VERBUNDEN;
  testGraph.adjMatrix[3][4] = VERBUNDEN;
  testGraph.adjMatrix[3][5] = VERBUNDEN;
  testGraph.adjMatrix[4][3] = VERBUNDEN;
  testGraph.adjMatrix[4][5] = VERBUNDEN;
  testGraph.adjMatrix[5][2] = VERBUNDEN;
  testGraph.adjMatrix[5][3] = VERBUNDEN;
  testGraph.adjMatrix[5][4] = VERBUNDEN;

  printMatrix(testGraph.adjMatrix, testGraph.anzKnoten);

  /* jeder Knoten wird einmal als Startknoten eingesetzt (DFS). */
  for (aktKnoten = 1; aktKnoten <= testGraph.anzKnoten; aktKnoten++) {
    resetVisited();
    printf("\nDFS beginnend bei Knoten %2d ergibt:\n", aktKnoten);
    DFS(aktKnoten, testGraph);
  }

/* jeder Knoten wird einmal als Startknoten eingesetzt (BFS). */
  for (aktKnoten = 1; aktKnoten <= testGraph.anzKnoten; aktKnoten++) {
    resetVisited();
    printf("\nBFS beginnend bei Knoten %2d ergibt:\n", aktKnoten);
    BFS(aktKnoten, testGraph);
  }

  return 0;
}

/* Alle mit dem Bezugsknoten direkt verbundenen Knoten
   werden im Array alleNachbar[] gespeichert (call-by-ref).
   Rueckgabewert der Funktion = Anzahl der Knoten,
   die mit dem Bezugsknoten direkt verbunden sind. */
int getAlleNachbarnZu(int bezugsKnoten, Graph graph, int alleNachbarn[]) {
  int anzNachbarn=0;
  int aktVglKnoten;
  for (aktVglKnoten = 0; aktVglKnoten <= graph.anzKnoten; aktVglKnoten++) {
    if (graph.adjMatrix[bezugsKnoten][aktVglKnoten] != UNVERBUNDEN)
      alleNachbarn[anzNachbarn++] = aktVglKnoten;
     /*kein direkter Nachbar => weiter suchen*/
  }
  return anzNachbarn;
}

/* alle Elemente von adjMatrix[][] werden auf Unverbunden initialisiert. */
void resetToUnverbunden(int adjMatrix[MAX_ELEMENTE][MAX_ELEMENTE]) {
  int zeile, spalte;
  for (zeile = 0; zeile < MAX_ELEMENTE; zeile++)
    for (spalte = 0; spalte < MAX_ELEMENTE; spalte++)
      adjMatrix[zeile][spalte] = UNVERBUNDEN;
}

/* Adjazenzmatrix zum Graphen wird hier ausgegeben. */
void printMatrix(int matrix[MAX_ELEMENTE][MAX_ELEMENTE], int anz) {
  int zeile, spalte;
  printf("Matrix:\n");
  printf("   ");
  for (spalte = 1; spalte <= anz; spalte++)
    printf("%3d", spalte);
  printf("\n");
  for (zeile = 1; zeile <= anz; zeile++) {
    printf("%3d", zeile);
    for (spalte = 1; spalte <= anz; spalte++)
      if (matrix[zeile][spalte] == UNVERBUNDEN)
        printf("  +");
      else
        printf("%3d", matrix[zeile][spalte]);
    printf("\n");
  }
  printf("Anmerkung: das Zeichen \"+\" in der Tabelle bedeutet, keine Verbindung zwischen den beiden Knoten existiert.\n");
}

/* alle Knoten auf "Unvisited" oder auf "nicht besucht" zurückgesetzt. */
void resetVisited() {
  int knoten;
  for (knoten = 0; knoten < MAX_ELEMENTE; knoten++)
    visited[knoten] = FALSE;
}

/* Knoten wird bearbeitet. */
void process(int knoten) {
  printf("Knoten %2d besucht.\n", knoten);
  return;
}

/* Hilfsfunktionen und -Datenstrukturen fuer die notwendige Queue:
  1-zu-1-Kopie aus dem Skript, allerdings wurde zur Vereinfachung
  T* durch int ersetzt, da die Queue sich die Graphknotennummern merken soll!
  Damit wird die Equal-Funktion trivial, naemlich Vergleich zweier int-Zahlen,
  also beispielsweise np1->data == item statt Equal(np1->data,item)

  Betrachten Sie diese Hilfsfunktionen gar nicht,
  sondern nutzen Sie die Funktionen Get und Put einfach!!!
*/
void Init(listptr L){
  L->first = NULL; L->last = NULL;
}

int IsEmpty(List L) {
  return (L.first == NULL && L.last == NULL);
}

nodeptr newnode(int item) {
  nodeptr np;
  np = (nodeptr)malloc(sizeof(Node));
  np->data = item;
  np->next = NULL;
  return np;
}

void AppendLast(int item, listptr L) {
  nodeptr np = newnode(item);
  if (IsEmpty(*L)) {
    L->first = np;
    L->last = np;
  }
  else {
    L->last->next = np;
    L->last = np;
  }
}

void Delete(int item, listptr L) {
  nodeptr np1,np2;
  if (IsEmpty(*L)) return;
  np1 = L->first;
  if (np1->data == item /*Equal(np1->data,item)*/) {
    L->first = np1->next;
    if (L->first == NULL)
      L->last = NULL;
    free(np1);
    return;
  }
  np2 = np1->next;
  while (np2 != NULL) {
    if (np2->data == item /*Equal(np2->data,item)*/) {
      np1->next = np2->next;
      if (np2 == L->last)
        L->last = np1;
      free(np2);
      break;
    }
    np1 = np2;
    np2 = np2->next;
  }
}


Queue erzeugeQueueInstanz() {
  Queue Q = malloc(sizeof(List)); /* List-Objekt als konkrete Implementierung der Queue auf Heap erstellt */
  Init(Q); /* notwendige Initialisierung der Queue */
  return Q;
}

void Put(int item, listptr L) {
  AppendLast(item, L);
}

int Get(listptr L) {
  int item;
  if (IsEmpty(*L)) return -1; /* -1 ist keine gueltige KnotenNr und gibt den Fehler lesen aus leerer Listen wieder! */
  item = L->first->data;
  Delete(item, L);
  return item;
}
