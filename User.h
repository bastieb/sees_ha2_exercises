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
	int i,random, randomzeit;

	//Prozesse
	SC_CTOR(User){
		B_start.initialize(0);
		p_gas.initialize(0);
		p_bremse.initialize(0);
		B_set.initialize(0);
		car_sighted.initialize(false); 
		SC_THREAD(starten);
	}
	//Abfolge des Nutzers Szenrio 1 von b)
	void starten()
	{
		
		B_start=1;	
		cout << "Nutzer startet den Motor" << endl;
		wait(SC_ZERO_TIME); 
		
		cout << "TEMPOMATMODUSTEST" << endl;

		B_set=1;
		wait(1,SC_SEC);	
		cout << "Tempomat wird angeschalten" << endl;
		B_set=0;

		//bis Minute 1 warten
		wait(46,SC_SEC);
		cout << "Wunschgeschwindigkeit wird auf 30 erhöht" << endl;
		i=0;
		while(i<30){
			B_vp=1;
			wait(1,SC_SEC);
			i++;
		}	
		B_vp=0;

		//bis Minute 3 warten
		wait(50,SC_SEC);

		cout << "Wunschgeschwindigkeit wird auf 10 gesenkt" << endl;
		i = 0;
		while(i < 20){
			B_vm = 1;
			wait(1,SC_SEC);
			i++;
		}	
		B_vm = 0;

		//bis Minute 3 warten
		wait(30,SC_SEC);
	
		cout << "PEDALVORRANGSTEST" << endl;
	
		//Nutzer beschleunigt auf 40 m/s
		cout << "Er beschleunigt auf 19 m/s " << endl;
		p_gas=20;
		wait(7,SC_SEC);
		p_gas=0;
		wait(1,SC_SEC);//sonst kommt cout zu früh
		cout << "29 m/s erreicht. Nutzer geht vom Gas" << endl;
	
		//bis Minute 5 warten
		wait(30,SC_SEC);

		//Bremsen auf 15m/s
		cout << "Nutzer bremst auf 1 m/s" << endl;
		p_bremse=29;
		wait(5,SC_SEC);
		p_bremse=0;

		//bis Minute 5 warten
		wait(100,SC_SEC);
		
/*
		wait(1,SC_SEC);//sonst kommt cout zu früh
		cout << "15 m/s erreicht. Nutzer geht von der Bremse" << endl;
		//2 min warten
		wait(120,SC_SEC);

		//Bremsen bis Stillstand
		cout << "Der Nutzer bremst bis zum Stillstand" << endl;
		p_bremse=20;
		wait(11,SC_SEC);
		p_bremse=0;

		//Auto steht
		wait(1,SC_SEC);//sonst kommt cout zu früh
		cout << "Auto steht" << endl;
		wait(1,SC_SEC);
	
		//Nutzer schaltet Auto aus
		cout << "Nutzer schlatet Motor aus" << endl;
 		B_start=0;
		wait(SC_ZERO_TIME);
*/
		
		//simulation ist zuende
		sc_stop();	
	}

};

#endif

 

