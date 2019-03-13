/**
 * TradesGenerator.hpp
 * generate trades.txt
 */ 
#pragma once

#ifndef TRADESGENERATOR_HPP
#define TRADESGENERATOR_HPP

using namespace std;

#include <fstream>
#include <random>
#include <vector>
#include <string>
#include "BondInformation.h"

class TradesGenerator {
public:
	// ctor
	TradesGenerator();

	// overload parenthsis operator to generator file
	// every product generate n data
	// the file has 6*n lines of data
	void operator()(int n);
};

TradesGenerator::TradesGenerator() {
}

void TradesGenerator::operator()(int n) {
	ofstream output;
	output.open("trades.txt");
	
	// record every product's data number, each should equal to n at end
	vector<int> count={0,0,0,0,0,0};
	
	for(int i=0;i<6*n;i++){
		int j=rand()%6;
		// if jth bond already has n data
		while(count[j]==n){
			j=rand()%6;
		}
		string cusip=bondCusip[j];
		++count[j];
		
		j=rand()%4;
		string tradeID;
		switch(j){
			case 0:tradeID="Tom";break;
			case 1:tradeID="Mary";break;
			case 2:tradeID="John";break;
			case 3:tradeID="Brendon";break;
		}
		output<<cusip<<","<<tradeID<<",";
		
		int a=rand()%2+99;
		int b=rand()%32;
		int c=rand()%8;		
		string A=to_string(a);
		string B=to_string(b);
		string C=to_string(c);
		if(b<10)B="0"+B;
		if(c==4)C="+";
		string price=A+"-"+B+C;
		output<<price<<",";
		
		output<<"Book"<<",";
		output<<to_string((rand()%5+1)*1000000)<<",";
		output<<(rand()%2==0?"BUY":"SELL");
		
		output <<endl;
	}
	output.close();
	return;
}
#endif