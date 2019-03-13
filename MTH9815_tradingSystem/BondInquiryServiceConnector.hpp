/*
 * BondInquiryServiceConnector.hpp
 * read data from inquiries.txt and pass to BondInquiryService
 */ 
#pragma once 

#ifndef BONDINQUIRYSERVICECONNECTOR_HPP		
#define BONDINQUIRYSERVICECONNECTOR_HPP

using namespace std;

#include "soa.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include "BondProductService.hpp"
#include "inquiryservice.hpp"

class BondInquiryService;

class BondInquiryServiceConnector: public Connector<Inquiry<Bond> >{
private:
	BondInquiryService* bondInquiryService;
	BondProductService* bondProductService;

	// transform a string to price
	float TransformStringToPrice(string& s);
public:
	// ctor
	BondInquiryServiceConnector(BondInquiryService* _bondInquiryService, BondProductService* _bondProductService);

	// override pure virtual functions in base class
	// Subscribe only, no use
	virtual void Publish(Inquiry<Bond>& data) override{} 
	
	// read data from inquiries.txt
	virtual void Subscribe() override;   	
	
};

float BondInquiryServiceConnector::TransformStringToPrice(string& s) {
	int n=s.size();
	if(s[n-1]=='+')s[n-1]='4';
	return stoi(s.substr(0, n-4))+stoi(s.substr(n-3,2))/32.0+stoi(s.substr(n-1,1))/256.0;
}


BondInquiryServiceConnector::BondInquiryServiceConnector(BondInquiryService* _bondInquiryService, BondProductService* _bondProductService){
	bondInquiryService=_bondInquiryService;
	bondProductService=_bondProductService;
}

// define void BondInquiryServiceConnector::Subscribe() in BondInquiryService.hpp
#endif