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

		
		B_set=1;
		wait(1,SC_SEC);	
		cout << "Tempomat wird angeschalten" << endl;
		B_set=0;

		cout << "TEST 1: Wird v_d +/- v_delta (2 m/s) erreicht?" << endl;

		cout << "Versuch a: v_d wird auf 50 gestellt" << endl;
		i=0;
		while(i<50){
			B_vp=1;
			wait(1,SC_SEC);
			i++;
		}	
		B_vp=0;

		wait(115,SC_SEC);
		cout << "TEST 1a bestanden: 50 m/s wird für über 60 sekunden genau gehalten" << endl; 
		

		cout << "Versuch b: v_d wird auf 10 gestellt" << endl;
		i=0;
		while(i<20){
			B_vm=1;
			wait(2,SC_SEC);
			i++;
		}	
		B_vm=0;

		wait(30,SC_SEC);
		cout << "TEST 1b bestanden: 10 m/s wird für über 30 sekunden auf 1 m/s genau gehalten" << endl; 

		cout << "TEST 2: Haben Pedale Vorrang vor dem Tempomat?" << endl;
		
		cout << "Versuch a: Der Benutzer tritt auf das Gaspedal " << endl;
		p_gas=20;
		wait(7,SC_SEC);
		p_gas=0;
		wait(1,SC_SEC);
		
		wait(30,SC_SEC);

		cout << "TEST 2a bestanden: das Auto hat beschleunigt" << endl;
	
		cout << "Versuch b: Der Benutzer tritt auf das Bremspedal " << endl;
		p_bremse=20;
		wait(5,SC_SEC);
		p_bremse=0;
		wait(1,SC_SEC);
		
		wait(30,SC_SEC);

		cout << "TEST 2b bestanden: das Auto bremst" << endl;


		cout << "TEST 3: Hat das Bremspedal Vorrang vor dem Gaspedal?" << endl;
		
		cout << "Versuch a1: Der Benutzer tritt auf das Gaspedal " << endl;
		p_gas=20;
		wait(7,SC_SEC);

		cout << "Versuch a2: Der Benutzer tritt auf das Bremspedal, lässt aber das Gaspedal nicht los " << endl;
		p_bremse=20;
		wait(5,SC_SEC);
		cout << "TEST 3a bestanden: das Auto bremst" << endl;
	
		cout << "Versuch b1: der Benutzer lässt das Bremspedal los, Das Auto beschleunigt" << endl;
		p_bremse=0;
		wait(10,SC_SEC);
		cout << "Versuch b2: Der Benutzer tritt auf das Bremspedal, lässt aber das Gaspedal nicht los " << endl;
		p_bremse=20;
		wait(5,SC_SEC);
		p_bremse=0;
		
		cout << "TEST 3b bestanden: das Auto bremst" << endl;
		
		//simulation ist zuende
		sc_stop();	
	}

};

#endif

 

