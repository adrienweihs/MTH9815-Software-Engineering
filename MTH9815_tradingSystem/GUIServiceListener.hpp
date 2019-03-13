/*
 * GUIServiceListener.hpp
 */
#pragma once

#ifndef GUISERVICELISTENER_HPP
#define GUISERVICELISTENER_HPP

#include "soa.hpp"
#include "GUIService.hpp"

using namespace std;

class GUIServiceListener: public ServiceListener<Price<Bond> >{
private:
	GUIService* gUIService;
public:
	// ctor
	GUIServiceListener(GUIService* _gUIService);
	
	// override the pure virtual functions in ServiceListener
	// when BondPricingService pass a new price, call AddPrice method in
	// BondAlgoStreamingService
	virtual void ProcessAdd(Price<Bond>& price) override; 
	
	// in this case, do not need this method
	virtual void ProcessRemove(Price<Bond>&) override{};  
	
	// in this case, do not need this method
	virtual void ProcessUpdate(Price<Bond>&) override{};  
};

GUIServiceListener::GUIServiceListener(GUIService* _gUIService){
	gUIService=_gUIService;
}

void GUIServiceListener::ProcessAdd(Price<Bond>& price){
	gUIService->SendToThrottle(price);
	return;
}






#endif