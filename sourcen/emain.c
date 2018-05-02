#include "simuc.h"

///////////////////////////////////////////////////////////////////////////////////////
// Bedingte Compilierung zur Bestimmung welches "Beispiel" compiliert werden soll  ///
//
// Es darf immer nur ein "define" aktive, d.h. nicht auskommentiert, sein.
//
//#define V1_Aufgabe_1
#define V1_Aufgabe_2
//#define V1_Aufgabe_3
//
///////////////////////////////////////////////////////////////////////////////////////


#ifdef V1_Aufgabe_1

void emain(void* arg) 
{
    unsigned short int zahl1;
    unsigned short int zahl2;
    unsigned short int ergebnis;
    int i;
	char string_1[100];
	char string_2[100];
    int schleife=1;
    int laenge;

	
	INIT_BM_WITHOUT_REGISTER_UI;
	
    do{
	putstring("Bitte 1. Zahl eingeben:\n");
	getstring(string_1);
    if(strlen(string_1)<5){

        for(i=0;i<strlen(string_1);i++){

            if((string_1[i]>=0x30)&&(string_1[i]<=0x39)){schleife=0;}
            else{
                putstring("Sie haben Keine Zahl eingegeben!\n");
                schleife=1;
                break;
            }
        }

    }
    else{
        putstring("Sie haben die Maximale Anzahl von Dezimalstellen ueberschritten!\n");
    }
    }
    while(schleife==1);
    laenge=strlen(string_1);
    switch(laenge){
    case 1:
        zahl1=string_1[0]-48;
        break;
    case 2:
        zahl1=10*(string_1[0]-48)+string_1[1]-48;
        break;
    case 3:
        zahl1=100*(string_1[0]-48)+10*(string_1[1]-48)+string_1[2]-48;
        break;
    case 4:
        zahl1=1000*(string_1[0]-48)+100*(string_1[1]-48)+10*(string_1[2]-48)+string_1[3]-48;
    }
    //zahl1=stringtoi(string_1);
schleife=1;
    do{
    putstring("Bitte 2. Zahl eingeben:\n");
    getstring(string_1);
    if(strlen(string_1)<5){

        for(i=0;i<strlen(string_1);i++){

            if((string_1[i]>=0x30)&&(string_1[i]<=0x39)){schleife=0;}
            else{
                putstring("Sie haben Keine Zahl eingegeben!\n");
                schleife=1;
                break;
            }
        }

    }
    else{
        putstring("Sie haben die Maximale Anzahl von Dezimalstellen ueberschritten!\n");
    }
    }
    while(schleife==1);

    laenge=strlen(string_1);
    switch(laenge){
    case 1:
        zahl2=string_1[0]-48;
        break;
    case 2:
        zahl2=10*(string_1[0]-48)+string_1[1]-48;
        break;
    case 3:
        zahl2=100*(string_1[0]-48)+10*(string_1[1]-48)+string_1[2]-48;
        break;
    case 4:
        zahl2=1000*(string_1[0]-48)+100*(string_1[1]-48)+10*(string_1[2]-48)+string_1[3]-48;
    }
    //zahl2=stringtoi(string_1);

    ergebnis= zahl1 + zahl2;

    if(ergebnis<10){
        string_1[0]=ergebnis+48;
    }
    if((ergebnis<100)&&(ergebnis>=10)){
        string_1[0]=ergebnis/10+48;
        string_1[1]=ergebnis%10+48;
    }
    if(ergebnis<1000&&ergebnis>=100){
        string_1[0]=ergebnis/100+48;
        string_1[1]=(ergebnis/10)%10+48;
        string_1[2]=ergebnis%10+48;
    }
    if(ergebnis<10000&&ergebnis>=1000){
        string_1[0]=ergebnis/1000+48;
        string_1[1]=(ergebnis/100)%10+48;
        string_1[2]=(ergebnis/10)%10+48;
        string_1[3]=ergebnis%10+48;
    }

    //itostring(ergebnis, string_1);

	copystring("Produkt beider Zahlen ist:\n",string_2);
	appendstring(string_1, string_2);
	putstring (string_2); 

	END;
}
#endif // V1_Aufgabe_1



#ifdef V1_Aufgabe_2

void emain(void* arg) 
{
	unsigned short int T1, T2;
	unsigned short int temp, help;

	// Mit den folgenden beiden Defines kann bestimmt werden welche Simulations-Tools verwendet werden.
	// Diese MUESSEN dann auch gestartet werden.
	// ######### IN DIESEM VERSUCH MUESSEN SIE OHNE DAS BANDMODELL ARBEITEN,             ##############
	// ######### da dieses sonst die Eingabe ueber das User-Interface "ueberschreibt".   ##############
	//INIT_BM_WITH_REGISTER_UI;		// Es werden beide Simulations-Tools (Bandmodell.exe und User_Interface.exe) verwendet
	INIT_REGISTER_UI_WITHOUT_BM		// Es wird nur das User-Interface zur Registerdarstellung (User_Interface.exe) verwendet.




	// Initialisierung gemaess Unterpunkt b)
	temp = (1 << 5) | (1 << 4); // temp mit dem Bitmuster 0x0030 
								// initialisieren bei dem nur Bit 5 							
								// und Bit 4 gesetzt (1) sind

	temp = ~temp;				// Alle Bits von temp negieren 								
								// temp enthält nun das
								// Bitmuster 0xFFCF

	io_out16 (DIR1, ( io_in16(DIR1) & temp) );	// Nur Bit 5 und 4 den
											// Wert 0 ( Lesen ) geben und
											// alle anderen Bits unverändert
											// lassen.

	temp = (1 << 10) | (1 << 9);	
	io_out16 (DIR1, ( io_in16(DIR1) |  temp) ); // Nur Bit 10 und 9 
											// auf 1 (Schreiben) setzen. Alle
											// anderen Bits unverändert
											// lassen.

	while(1) {

		SYNC_SIM;		

		temp = io_in16(IN1);		// Einlesen von Port 1	

		temp = temp >> 4;	// So oft nach rechts shiften
							// bis das Bit 4 an der Bitstelle 0 steht.

		T1 = temp & 0x01;	// Zur Sicherheit alle Bits, 
							// bis auf Bit0 auf 0 setzen 
							// und das Ergebnis T1 zuweisen.
		/*	Das Bit für den Taster T1 ist nun eingelesen und 
		die Variablen T1 hat genau den logischen Wert dieses
		Bits, d.h.
		T1 = 0 wenn Bit 4 = 0 , also wenn Taster T1 betätigt.
		T1 = 1 wenn Bit 4 = 1 , also wenn Taster T1 nicht betätigt.
		Für T2 machen wir nun das Gleiche.
		*/
		temp = in(IN1);		// Einlesen von Port 1	

		temp = temp >> 5;	// So oft nach rechts shiften
							// bis das Bit 5 an der Bitstelle 0 steht.

		T2 = temp & 0x01;	// Alle Bits, bis auf Bit0 auf 0 setzen 
							// und das Ergebnis T2 zuweisen.

		if(T1 == 1) {		
			temp = 1 << 9;	// Berechnung des Bitmusters 0x0200 						
							// bei dem nur das Bit 9 gesetzt ist.

			// Bit 9 an Port 1 auf '1' setzen.
			help = io_in16(OUT1); 			// Aktuellen Ausgabewert einlesen ...
			help = help |  temp;			// ... mit temp "verodern"...
			io_out16(OUT1, ( help | temp) );	 // ... und wieder ausgeben.
			
			// Dies waere die kuerzere Varianten um Bit 9 zu setzen
			// io_out16 (OUT1, ( io_in16(OUT1) |  temp) );
		}
		else {
            temp = 1 <<9;	// Berechnung des Bitmusters 0x0200

			temp = ~temp;	// Das Bitmuster wird bitweise
							// invertiert, d.h. nun ist Bit 9 das
							// einzige Bit das '0' ist.

			// Bit 9 an Port 1 wird zurueck gesetzt auf '0
			io_out16 (OUT1, ( io_in16(OUT1) & temp) );
			
		}

		if(T2 == 1) {		
            temp = 1 << 10;
			io_out16 (OUT1, ( io_in16(OUT1) |  temp) );
		}		
		else {
            temp = 1 << 10;
			temp = ~temp;
			io_out16 (OUT1, ( io_in16(OUT1) & temp) );
		}
	}		

	
	END;
}
#endif // V1_Aufgabe_2


#ifdef V1_Aufgabe_3

void emain(void* arg) 
{
	unsigned short int T1, T2;
	unsigned short int temp, help;

	// Mit den folgenden beiden Defines kann bestimmt werden welche Simulations-Tools verwendet werden.
	// Diese MUESSEN dann auch gestartet werden.
	// ######### IN DIESEM VERSUCH MUESSEN SIE OHNE DAS BANDMODELL ARBEITEN,             ##############
	// ######### da dieses sonst die Eingabe ueber das User-Interface "ueberschreibt".   ##############
	//INIT_BM_WITH_REGISTER_UI;		// Es werden beide Simulations-Tools (Bandmodell.exe und User_Interface.exe) verwendet
	INIT_REGISTER_UI_WITHOUT_BM		// Es wird nur das User-Interface zur Registerdarstellung (User_Interface.exe) verwendet.




	// Initialisierung gemaess Unterpunkt b)
	temp = (1 << 5) | (1 << 4); // temp mit dem Bitmuster 0x0030 
								// initialisieren bei dem nur Bit 5 							
								// und Bit 4 gesetzt (1) sind

	temp = ~temp;				// Alle Bits von temp negieren 								
								// temp enthält nun das
								// Bitmuster 0xFFCF

	io_out16 (DIR1, ( io_in16(DIR1) & temp) );	// Nur Bit 5 und 4 den
											// Wert 0 ( Lesen ) geben und
											// alle anderen Bits unverändert
											// lassen.

	temp = (1 << 10) | (1 << 9);	
	io_out16 (DIR1, ( io_in16(DIR1) |  temp) ); // Nur Bit 10 und 9 
											// auf 1 (Schreiben) setzen. Alle
											// anderen Bits unverändert
											// lassen.

	while(1) {

		SYNC_SIM;		

		temp = io_in16(IN1);		// Einlesen von Port 1	

		temp = temp >> 4;	// So oft nach rechts shiften
							// bis das Bit 4 an der Bitstelle 0 steht.

		T1 = temp & 0x01;	// Zur Sicherheit alle Bits, 
							// bis auf Bit0 auf 0 setzen 
							// und das Ergebnis T1 zuweisen.
		/*	Das Bit für den Taster T1 ist nun eingelesen und 
		die Variablen T1 hat genau den logischen Wert dieses
		Bits, d.h.
		T1 = 0 wenn Bit 4 = 0 , also wenn Taster T1 betätigt.
		T1 = 1 wenn Bit 4 = 1 , also wenn Taster T1 nicht betätigt.
		Für T2 machen wir nun das Gleiche.
		*/
		temp = in(IN1);		// Einlesen von Port 1	

		temp = temp >> 5;	// So oft nach rechts shiften
							// bis das Bit 5 an der Bitstelle 0 steht.

		T2 = temp & 0x01;	// Alle Bits, bis auf Bit0 auf 0 setzen 
							// und das Ergebnis T2 zuweisen.

		if(T1 == 1) {		
			temp = 1 << 9;	// Berechnung des Bitmusters 0x0200 						
							// bei dem nur das Bit 9 gesetzt ist.

			// Bit 9 an Port 1 auf '1' setzen.
			help = io_in16(OUT1); 			// Aktuellen Ausgabewert einlesen ...
			help = help |  temp;			// ... mit temp "verodern"...
			io_out16(OUT1, ( help | temp) );	 // ... und wieder ausgeben.
			
			// Dies waere die kuerzere Varianten um Bit 9 zu setzen
			// io_out16 (OUT1, ( io_in16(OUT1) |  temp) );
		}
		else {
			temp = 1 << 9;	// Berechnung des Bitmusters 0x0200 

			temp = ~temp;	// Das Bitmuster wird bitweise
							// invertiert, d.h. nun ist Bit 9 das
							// einzige Bit das '0' ist.

			// Bit 9 an Port 1 wird zurueck gesetzt auf '0
			io_out16 (OUT1, ( io_in16(OUT1) & temp) );
			
		}

		if(T2 == 1) {		
			temp = 1 << 10;
			io_out16 (OUT1, ( io_in16(OUT1) |  temp) );
		}		
		else {
			temp = 1 << 10;
			temp = ~temp;
			io_out16 (OUT1, ( io_in16(OUT1) & temp) );
		}
	}		

	
	END;
}
#endif // V1_Aufgabe_3

