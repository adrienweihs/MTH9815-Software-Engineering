/*
 * BondAlgoStreamingServiceListener.hpp
 * defines BondAlgoStreamingServiceListener to pass data from
 * BondPricingService to BondAlgoStreamingService
 */
#pragma once

#ifndef BONDALGOSTREAMINGSERVICELISTENER_HPP
#define BONDALGOSTREAMINGSERVICELISTENER_HPP

#include "soa.hpp"
#include "BondAlgoStreamingService.hpp"

using namespace std;

class BondAlgoStreamingServiceListener: public ServiceListener<Price<Bond> >{
private:
	BondAlgoStreamingService* bondAlgoStreamingService;
public:
	// ctor
	BondAlgoStreamingServiceListener(BondAlgoStreamingService* _bondAlgoStreamingService);
	
	// override the pure virtual functions in ServiceListener
	// when BondPricingService pass a new price, call AddPrice method in
	// BondAlgoStreamingService
	virtual void ProcessAdd(Price<Bond>& price) override; 
	
	// in this case, do not need this method
	virtual void ProcessRemove(Price<Bond>&) override;  
	
	// in this case, do not need this method
	virtual void ProcessUpdate(Price<Bond>&) override;  
};

BondAlgoStreamingServiceListener::BondAlgoStreamingServiceListener(BondAlgoStreamingService* _bondAlgoStreamingService){
	bondAlgoStreamingService=_bondAlgoStreamingService;
}

void BondAlgoStreamingServiceListener::ProcessAdd(Price<Bond>& price){
	bondAlgoStreamingService->AddPrice(price);
	return;
}

void BondAlgoStreamingServiceListener::ProcessRemove(Price<Bond>& data){
	return;
}

void BondAlgoStreamingServiceListener::ProcessUpdate(Price<Bond>& data){
	return;
}




#endif