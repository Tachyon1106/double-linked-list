#include <stdio.h>
#include <stdlib.h>

typedef struct list_element { //Jedes Element bekommt eine Menge von Strings und Zeiger auf das vorherige und nächste Element der Liste
	char string[15][50];

	struct list_element* next;
	struct list_element* prev;
};

struct list_element* create_first(struct list_element* prev, char n[15][50], int k) { //Erschaffung des ersten Elements (prev ist der Zeiger auf das erste Element, n ist das Feld, das die Kategorien enthält, k ist die Anzahl der Kategorien)
	struct list_element* new_node;
	new_node = malloc(sizeof(struct list_element));
	if (!new_node)		//prüfen, ob Speicher voll ist
		return NULL;

	for (int i = 0; i < k; i++) {
		printf("%s: ", n[i]);
		gets_s(new_node->string[i], 50); //Belegung des Elements in Abhängigkeit von n
		while (checkForString(new_node->string[i])) {
			printf("please enter something else!: ");
			gets_s(new_node->string[i], 50);
		}
	}

	new_node->prev = prev;
	new_node->next = NULL;
	return new_node;
}

void create_element(struct list_element* start, int i, char n[15][50], int k) { //Erschaffung und Belegung von beliebigen neuen Elementen (start ist ein Struct ohne String, welches nie verändert werden darf, i ist die Stelle in der Liste für das neue Element, n und k wie bei create_first)
	struct list_element* nextsafe;

	struct list_element* new_node;
	new_node = start; //Anlegen einer Kopie von start, da start nicht verändert werden darf
	while (i - 1) {
		if (new_node->next)
			new_node = new_node->next; //Bis zur Stelle in der Liste iterieren (if-Bedingung, damit man nicht auf NULL landet
		else {
			printf("Element doesn't exist!");
			system("pause");
			return;
		}
		i--;
	}

	nextsafe = new_node->next;
	new_node->next = malloc(sizeof(struct list_element));
	if (!new_node->next)
		return;

	new_node->next->prev = new_node; //Zeiger neu verknüpfen, um das Element "zwischen" zwei Elementen einzufügen
	new_node->next->next = nextsafe;
	if (nextsafe)
		if (nextsafe->next)
			nextsafe->prev = new_node->next;

	for (int i = 0; i < k; i++) {
		printf("%s: ", &n[i]);
		gets_s(new_node->next->string[i], 50);
		while (checkForString(new_node->next->string[i])) {
			printf("please enter something else!: ");
			gets_s(new_node->next->string[i], 50);
		}
	}
}

void print_element(struct list_element* start, int i, char n[15][50], int k) { //Ausgeben von einem Element (Übergabeparameter identisch zu create_element)
	struct list_element* new_node;
	new_node = start; //erneut start-Kopie
	while (i) {
		if (new_node->next)
			new_node = new_node->next; //selbiges wie create_element
		else {
			printf("Element doesnt exist!");
			system("pause");
			return;
		}
		i--;
	}
	if (new_node)
		for (int i = 0; i < k; i++)
			printf(" %s: %s \n", n[i], new_node->string[i]);
	else
		printf("List is empty!");
	system("pause");
}

void delete_element(struct list_element* start, int i) { //ähnlich wie create_element, nur das der Speicher freigegeben statt belegt wird (start und i wie create_element)
	struct list_element* nextsafe;

	struct list_element* new_node;
	new_node = start; //erneut start-Kopie
	while (i) {
		if (new_node->next) //iterieren bis zu Element i
			new_node = new_node->next;
		else {
			printf("Element doesn't exist!");
			system("pause");
			return;
		}
		i--;
	}

	new_node->prev->next = new_node->next;
	if (new_node->next)
		new_node->next->prev = new_node->prev;

	free(new_node);
	system("pause");
}

void print_all(struct list_element* start, char n[15][50], int k) { // Ausgabe aller Elemente und speichern in einer Datei (start, n und k wie print_element)
	errno_t err; //Spezieller Fehler für Öffnen einer Datei mit fopen_s
	struct list_element* new_node;
	new_node = start;
	FILE* datei;
	err = fopen_s(&datei, "list.txt", "w+"); //Datei öffnen
	if (err)
		printf("File couldnt be opened for saving the list!");
	else {
		if (new_node)
			while (new_node->next) { //Beschreiben der Datei mit dem Inhalt der einzelnen Elemente durch Iterieren über die Liste
				new_node = new_node->next;
				if (datei != NULL)
					fprintf(datei, "/@$\n"); //Ende des Elements (relevant bei Auslesen [nicht implementiert])
				for (int i = 0; i < k; i++) {
					printf(" %s: %s \n", n[i], new_node->string[i]);
					if (datei != NULL)
						fprintf(datei, " %s: %s \n", n[i], new_node->string[i]);
				}
				fprintf(datei, "/$@"); //Ende der Liste (relevant bei Auslesen [nicht implementiert])
			}
		else
			printf("list is empty!");
	}
	fclose(datei); //Datei schließen
	system("pause");
}

void search_element(struct list_element* start, char n[15][50], int k) { //Suche eines Elements anhand einer Kategorie (start, n und k as ususal)
	char search[50];
	int scan = 1, z, i = 0;
	struct list_element* new_node;
	new_node = start;

	printf("Which number has the component you want to search for?"); //Hier den Kategorienamen zu verlangen ist nicht nur ungleich komplizierter, es ist auch Userunfreundlicher (z.B. vertippen)
	scanf_s(" %d", &z);
	while (getchar() == "\n");

	printf("what are you looking for?");
	gets_s(search, 50);
	while (checkForString(search)) {
		printf("please enter something else!: ");
		gets_s(search, 50);
	}
	if (new_node)
		while (new_node->next) { //Iteration über die Liste, um jedes Element zu prüfen
			new_node = new_node->next;
			i = 0;
			scan = 1;
			while (i < 50 && search[i] != '\0' && scan) { //Man nimmt an, die Strings sind identisch, bis das Gegenteil festgestellt wurde (läuft nur für die Länge von search, sodass man auch z.B. nur nach Anfangszeichen suchen kann)
				if (search[i] == new_node->string[z - 1][i]);
				else
					scan = 0;
				i++;
			}
			if (scan) //Ausgabe, wenn nicht festgestellt wurde, das die Strings nicht identisch sind
				for (int i = 0; i < k; i++)
					printf(" %s: %s \n", n[i], new_node->string[i]);
		}
	system("pause");
}

int checkForString(char n[50]) { //Die Zeichenkombination /@$ , die beim Speichern angibt, wo ein Element zu ende ist, darf nie vom User in die Liste eingebracht werden
	for (int i = 0; i < 48; i++) {
		if (n[i] == '/' && n[i + 1] == '@' && n[i + 2] == '$')
			return 1;
	}
	return 0;
}

void sort(struct list_element* start, int elementtosort, char n[15][50], int k) { //(start, n und k wie immer, elementtosort ist die Kategorie nach der sortiert werden soll)
	char safe[50][50];
	int count[50], swap, load2 = 0, nr = 0;
	struct list_element* new_node;
	new_node = start; //Kopie von start

	while (new_node->next) {
		new_node = new_node->next;
		nr++; //nr zählt, wieviele Elemente tatsächlich in der Liste sind
		for (int load3 = 0; load3 < 50; load3++)
			safe[load2][load3] = new_node->string[elementtosort-1][load3]; //safe enthält am ende der While-Schleife alle Strings der entsprechenden Kategorie aus den ELementen, versehen mit der Nummer des einlesens
		load2++;
	}

	if(nr<=50){
	for (int load = 0; load < nr; load++) //count wird mit so vielen Zahlen belegt, wie Elemente eingelesen wurden
		count[load] = load;

	for (int j = 0; j < nr - 1; j++)
		for (int i = 0; i < nr - 1; i++)
			if (safe[count[i]][0] >= safe[count[i + 1]][0]) { //Immer wenn das vorherige Element größer gleich dem Folgenden Ist, wird in count die reihenfolge der Zahlen geändert (Am ende enthält count die reihenfolge, in der die Elemente ausgegeben werden müssen, um sortiert zu sein)
				swap = count[i];
				count[i] = count[i + 1];
				count[i + 1] = swap;
			}

	for (int j = 0; j < nr; j++) { //Ausgabe der Elemente
		new_node = start; //Zurücksetzen, um zum folgenden Element gehen zu können
		for (int i = 0; i <= count[j]; i++) //Sprung auf der Liste bis zum Element, das in dem durchlauf ausgegeben werden soll
			new_node = new_node->next;
		for (int c = 0; c < k; c++) //Ausgabe von Kategorie und String
			printf(" %s : %s \n", n[c], new_node->string[c]);
	}
	}
	else
		printf("The list is too big!");
	system("pause");
}

int main(void) {
	int nr = 0, check = 1, kom = 0;
	char menue = 0;
	char names[15][50];
	char t;
	struct list_element* start; //Erschaffen von Start, welches keinen String und zwei pointer auf NULL enthält (next wird später mit dem ersten Element belegt) Start bleibt immer erhalten, als feste Referenz von der man beginnen kann
	start = malloc(sizeof(struct list_element));
	if (!start)
		return NULL;
	printf("How many different components do you want to have? (max 15) \n");
	scanf_s(" %d", &kom); //Anzahl der Kategorien wird in kom gespeichert
	while (getchar() == "\n");

	for (int i = 0; i < kom; i++) { //Belegung von names, welches die Kategorien enthält, die der User sich hier aussucht
		printf("Name of the %d. component:", i + 1);
		gets_s(names[i], 50);
		while (checkForString(names[i])) {
			printf("please select another name: ");
			gets_s(names[i], 50);
		}
	}
	start->next = create_first(start, names, kom); //Erschaffung des ersten Elements und Belegung vom next-Zeiger von Start mit diesem

	do { //Schleife, die solange läuft, bis check 0 (also false) wird
		system("cls"); //Befehl zur Bereinigung der Konsole, was die ganze Sache etwas übersichtlicher macht
		printf("Press '1' to add a new Element \nPress '2' to print an Element \nPress '3' to delete an Element \nPress '4' to print all Elements and save them into a text document\nPress '5' to search for Elements \nPress '6' to see the sorted List (max 50 Elements) \nAny other key ends the program \n");
		menue = getchar(); //Der Print-Befehl gibt das Gesamte Menü aus, menue ist die switch-Variable
		switch (menue) {
		case '1':
			printf("which place for the new element?");
			scanf_s(" %d", &nr); //nr wird immer dann neu belegt, wenn eine Funktion eine bestimmte Nummer benötigt (z.B. Hier: Stelle in der Liste)
			while (getchar() == "\n"); //"Buffer clear", damit keine Funktion eingaben von vorherigen Funktionen, die noch im Buffer sind, einliest (wird öfter im ganzen Programm benutzt)
			create_element(start, nr, names, kom);
			break;
		case '2':
			printf("which one should I print?");
			scanf_s(" %d", &nr);
			while (getchar() == "\n");
			print_element(start, nr, names, kom);
			break;
		case '3':
			printf("which one should i delete?");
			scanf_s(" %d", &nr);
			while (getchar() == "\n");
			delete_element(start, nr);
			break;
		case '4':
			while (getchar() == "\n"); //Wird aufgerufen, weil print_all keine Eingabe mehr tätigt und somit nirgends sonst der Buffer geleert wird
			print_all(start, names, kom);
			break;
		case '5':
			search_element(start, names, kom); //Benötigte Variablen nimmt die Funktion intern vom User auf
			break;
		case '6':
			printf("Which number has the criteria you want to sort after?");
			scanf_s(" %d", &nr);
			while (getchar() == "\n");
			sort(start, nr, names, kom);
			break;
		default:
			printf("do you really want to exit? (j/n) \n"); //Programm wird nur bei 'j' beendet, alles andere führt zurück ins Menü
			scanf_s(" %c", &t, 1);
			while (getchar() == "\n");
			if (t == 'j')
				check = 0;
			break;
		}
	} while (check);
	system("pause");
}
