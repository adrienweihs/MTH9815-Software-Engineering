/**
 * BondPositionServiceListener.hpp
 * pass data from BondTradeBookingService 
 * to BondPositionService
 */ 
#pragma once

#ifndef BONDPOSITIONSERVICELISTENER_HPP
#define BONDPOSITIONSERVICELISTENER_HPP

#include "BondPositionService.hpp"
#include "soa.hpp"

using namespace std;

class BondPositionServiceListener : public ServiceListener<Trade<Bond> > {
private:
    BondPositionService* bondPositionService;

public:
    // ctor
    BondPositionServiceListener(BondPositionService* _bondPositionService);

    // override all pure virtual functions in base class
	// call bondPositionService AddTrade method
    virtual void ProcessAdd(Trade<Bond> &data); 
	
	// no use in this case
    virtual void ProcessRemove(Trade<Bond> &data) override{}
	
	// no use in this case
    virtual void ProcessUpdate(Trade<Bond> &data) override{}
};

BondPositionServiceListener::BondPositionServiceListener(BondPositionService* _bondPositionService) {
	 bondPositionService= _bondPositionService;
}

void BondPositionServiceListener::ProcessAdd(Trade<Bond> &data) {
    bondPositionService->AddTrade(data);
	return;
}


#endif