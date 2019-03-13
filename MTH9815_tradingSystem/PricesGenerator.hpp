/*
 * PricersGenerator.hpp
 * to generator "pricers.txt"
 * everyline: product price spread
 */
#pragma once

#ifndef	PRICERSGENERATOR_HPP
#define PRICERSGENERATOR_HPP

#include <fstream>
#include <random>
#include <vector>
#include <string>
#include "BondInformation.h"

using namespace std;

class PricesGenerator {
public:
	// ctor
	PricesGenerator();

	// overload parenthsis operator to generator file
	// every product generate n data
	// the file has 6*n lines of data
	void operator()(int n);
};

PricesGenerator::PricesGenerator() {
}

void PricesGenerator::operator()(int n) {
	ofstream output;
	output.open("prices.txt");
	
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
	
		int a=rand()%2+99;
		int b=rand()%32;
		int c=rand()%8;
		
		string A=to_string(a);
		string B=to_string(b);
		string C=to_string(c);
		if(b<10)B="0"+B;
		if(c==4)C="+";
		string price=A+"-"+B+C;
		
		int d=rand()%4;
		string spread;
		if(d==0)spread="0-001";
		else if(d==1)spread="0-002";
		else if(d==2)spread="0-003";
		else spread="0-00+";
		
		output << cusip << "," << price << "," << spread << endl;
	}
	output.close();
}

#endif
