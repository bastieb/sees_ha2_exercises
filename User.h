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
	int i,random, random2, randomzeit, random_old, B_stop_lok, p_gas_lok, p_bremse_lok, v_car_lok;

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
		B_start.write(1);	//Auto wird angeschalten
		cout << "starte den Motor" << endl;

		//Anzahl der Nutzereingaben
		while(i<20){				
			//zufallszahlen generieren
			randomzeit = rand() %16;
			random = rand() %9;

			//Auto anschalten
			if(random==0 && B_stop_lok ==1){		
				cout << " Nutzer schaltet das Auto an und bereitet sich vor" << endl;				
				B_stop_lok=0;
				B_stop.write(B_stop_lok);
				B_start.write(1);			
				wait(2,SC_SEC);
			}
			//Pedalaenderung		
			if(random==1 && randomzeit > 9 && B_stop_lok ==0){
				cout << "Pedaländerung" << endl;	
				wait(randomzeit,SC_SEC);
				p_gas_lok = 20;
				p_gas.write(p_gas_lok);
				p_bremse_lok=0;
				p_bremse.write(p_bremse_lok);
				//neuer Zufall für Pedalaktionen
				//while (random !=2){
					random2 = rand()%2;

					//Gas geben			
					if(random2==1 && p_gas_lok<100)
						p_gas.write(p_gas_lok + 10);   
					//Bremsen			
					if(random2==0 && p_bremse_lok<100){
						p_bremse.write(p_bremse_lok + 10);
						B_set.write(0); }

					cout << "Bremse ist " << p_bremse_lok << ", Gas ist " << p_gas_lok << endl;
				//}
			}
		
			//Tempomat anschalten
			if(random==2 && tempomatstatus.read() ==0 && p_bremse_lok==0 && B_stop_lok ==0 && randomzeit > 1){
					wait(2, SC_SEC);
					cout << "Tempomat wird angeschalten" << endl;
					B_set.write(1);
					wait(1, SC_SEC);
					B_set.write(0); //Er lässt den Knop wieder los
					}
			//v_d erhöhen
			if(random==3 && tempomatstatus.read() == 1 && randomzeit > 4){
					wait(5, SC_SEC);				
					cout << "Wunschgeschwindigkeit wird um 1 erhöht" << endl;
					B_vp.write(1);
					//B_vp wieder Null setzen
					wait(1, SC_SEC); B_vp.write(0);
					}
			//v_d verringern
			if(random==4 && tempomatstatus.read() == 1 && randomzeit > 4){
					wait(5, SC_SEC);				
					cout << "Wunschgeschwindigkeit wird um 1 verringert" << endl;
					B_vm.write(1);
					//B_vm wieder Null setzen
					wait(1, SC_SEC); B_vm.write(0);			
					}
			//Auto ausschalten
			if(random==5 && B_stop_lok ==0){				//Auto ausschalten
					cout << "Nutzer schaltet das Auto aus" << endl;				
					p_gas_lok=0;
					p_gas.write(p_gas_lok);
					p_bremse_lok=0;
					p_bremse.write(p_bremse_lok);
					B_stop_lok=1;
					B_stop.write(B_stop_lok);
					B_start.write(0);
					wait(2,SC_SEC);			//Auto bleibt 2 Sekunden aus			
						}
			//Sensor sichtet ein Auto
			if(random==6 && tempomatstatus.read() == 1 && dist.read()>300){
					car_sighted.write(true); 			
					v_car_lok=rand() %50;
					v_car.write(v_car_lok);
					cout << "Es wurde ein Auto mit der Geschwindigkeit " << v_car_lok << " gesichtet" << endl;		
					wait(1,SC_SEC);		
					}
			//FrontCar beschleunigt um 1 m/s
			if(random==7 && dist.read()<300 && v_car_lok<50){ 			
					v_car_lok=v_car_lok+1;
					v_car.write(v_car_lok);
					cout << "FrontCar beschleunigt v_car um 1 m/s "  << endl;				
					wait(1,SC_SEC);				
					}
			//FrontCar bremst um 1 m/s
			if(random==8 && dist.read()<300 && v_car_lok>5){ 			
					v_car_lok=v_car_lok-1;
					v_car.write(v_car_lok);
					cout << "FrontCar verringtert v_car um 1 m/s "  << endl;				
					wait(1,SC_SEC);				
					}	
			//Wenn es keine Möglichkeit gibt	
			else i--; 			
			i++;
			random_old = random;
				}

	}

};

#endif

 

