#include <systemc.h>

#ifndef User_H_
#define User_H_

SC_MODULE(User){
	
	//zur Kontolleinheit
	sc_out<int> B_start, B_stop, p_gas, p_bremse, B_set, B_vm, B_vp;
	
	//von der Kontrolleinheit
	sc_in<int> tempomatstatus;	

	//vom FrontCar
	sc_in<double> dist;

	//zum Frontcar
	sc_out<double> v_car;
	sc_out<bool>  car_sighted;
	//Variablen
	int i,random, random_old, randomzeit;

	//Prozesse
	SC_CTOR(User){
		B_start.initialize(0);
		p_gas.initialize(0);
		p_bremse.initialize(0);
		B_set.initialize(0);
		car_sighted.initialize(false); 
		SC_THREAD(starten);
	}

	void starten()
	{
		i=0,		
		B_start=1;	//Auto wird angeschalten
		cout << "starte den Motor" << endl;

	//Anzahl der Nutzereingaben
	while(i<20){				
		//zufallszahlen generieren
		srand(time(NULL)); 
		randomzeit = rand() %16;
		do{
			random = rand() %11;
		}while(random == random_old);
		random_old = random;

		//Auto anschalten
		if(random==0 && B_stop ==1){		
		cout << " Nutzer schaltet das Auto an und bereitet sich vor" << endl;				
		B_stop=0, B_start=1;				
		wait(2,SC_SEC);
				}
		//Pedalaenderung
		//Gas geben
		if(random==1 && randomzeit > 9 && B_stop ==0){
			wait(randomzeit, SC_SEC);
			cout << "Gas geben" << endl;
			p_bremse=0;p_gas=1+rand() %100;
			}
		//Bremsen
		if(random==2 && randomzeit > 9 && B_stop ==0){
			wait(randomzeit, SC_SEC);
			cout << "Bremsen" << endl;
			p_gas=0;p_bremse=1+rand() %100;
			}
		//Rollen
		if(random==3 && randomzeit > 9 && B_stop ==0){
			wait(randomzeit, SC_SEC);
			cout << "Rollen" << endl;
			p_gas=0,p_bremse=0;
			}
		
		//Tempomat anschalten
		if(random==4 && tempomatstatus ==0 && p_bremse==0 && randomzeit > 1){
				wait(randomzeit, SC_SEC);
				cout << "Tempomat wird angeschalten" << endl;
				B_set=1;wait(1, SC_SEC);
				B_set=0; //Er lässt den Knop wieder los
				}
		//v_d erhöhen
		if(random==5 && tempomatstatus == 1 && randomzeit > 4){
				wait(randomzeit, SC_SEC);				
				cout << "Wunschgeschwindigkeit wird um 1 erhöht" << endl;
				B_vp=1;
				//B_vp wieder Null setzen
				wait(1, SC_SEC); B_vp=0;
				}
		//v_d verringern
		if(random==6 && tempomatstatus == 1 && randomzeit > 4){
				wait(randomzeit, SC_SEC);				
				cout << "Wunschgeschwindigkeit wird um 1 verringert" << endl;
				B_vm=1;
				//B_vm wieder Null setzen
				wait(1, SC_SEC); B_vm=0;			
				}
		//Auto ausschalten
		if(random==7 && B_stop ==0){				//Auto ausschalten
				cout << "Nutzer schaltet das Auto aus" << endl;				
				p_gas=0,p_bremse=0;
				B_stop=1, B_start=0;
				wait(2,SC_SEC);			//Auto bleibt 2 Sekunden aus			
					}
		//Sensor sichtet ein Auto
		if(random==8 && tempomatstatus == 1 && dist>300){
				car_sighted=true; 			
				v_car=rand() %50;
				cout << "Es wurde ein Auto mit der Geschwindigkeit " << v_car << " gesichtet" << endl;		
				wait(1,SC_SEC);		
				}
		//FrontCar beschleunigt um 1 m/s
		if(random==9 && dist<300 && v_car<50){ 			
				v_car=v_car+1;
				cout << "FrontCar beschleunigt v_car um 1 m/s "  << endl;				
				wait(1,SC_SEC);				
				}
		//FrontCar bremst um 1 m/s
		if(random==10 && dist<300 && v_car>5){ 			
				v_car=v_car-1;
				cout << "FrontCar verringert v_car um 1 m/s "  << endl;				
				wait(1,SC_SEC);				
				}	
		//Wenn es keine Möglichkeit gibt	
		else i--; 			
		i++;
			}

	}

};

#endif

 

