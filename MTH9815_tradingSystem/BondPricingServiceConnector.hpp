/**
 * BondPricingConnector.hpp
 * Defines a connector to read data from price.txt then pass to BondPricingService
 *
 */

#pragma once

#ifndef BONDPRICINGSERVICECONNECTOR_HPP
#define BONDPRICINGSERVICECONNECTOR_HPP

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include "soa.hpp"
#include "pricingservice.hpp"
#include "BondProductService.hpp"

using namespace std;

class BondPricingService;

class BondPricingServiceConnector: public Connector<Price<Bond> > {
private:
	BondPricingService* bondPricingService;
	BondProductService* bondProductService;

	// transform a string to price
	float TransformStringToPrice(string& s);
public:
	// ctor
	BondPricingServiceConnector(BondPricingService* _bondPricingService,BondProductService* _bondProductService);

	// read data from .txt file
	virtual void Subscribe() override;

	// do nothing, subscribe only
	virtual void Publish(Price<Bond>& data) override;
};


float BondPricingServiceConnector::TransformStringToPrice(string& s) {
	int n=s.size();
	if(s[n-1]=='+')s[n-1]='4';
	return stoi(s.substr(0, n-4))+stoi(s.substr(n-3,2))/32.0+stoi(s.substr(n-1,1))/256.0;
}


BondPricingServiceConnector::BondPricingServiceConnector(BondPricingService* _bondPricingService,BondProductService* _bondProductService) {
	bondPricingService=_bondPricingService;
	bondProductService=_bondProductService;
}


//void BondPricingServiceConnector::Subscribe() defined in BondPricingServce.hpp


void BondPricingServiceConnector::Publish(Price<Bond>& data) {
	return;
}
#endif
