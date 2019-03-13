#pragma once

#ifndef BONDRISKSERVICELISTENER_HPP
#define BONDRISKSERVICELISTENER_HPP

using namespace std;

#include "BondRiskService.hpp"
#include "soa.hpp"

class BondRiskServiceListener : public ServiceListener<Position<Bond> > {
private:
    BondRiskService* bondRiskService;
public:
    //ctor
    BondRiskServiceListener(BondRiskService* _bondRiskService);

    // override pure virtual functions in base class
	// call bondRiskService AddPosition method
    virtual void ProcessAdd(Position<Bond> &data) override; 
	
	// no use in this case
    virtual void ProcessRemove(Position<Bond> &data) override{};  
	
	// no use in this case
    virtual void ProcessUpdate(Position<Bond> &data) override{}; 
};

BondRiskServiceListener::BondRiskServiceListener(BondRiskService* _bondRiskService) {
	bondRiskService=_bondRiskService;
}

void BondRiskServiceListener::ProcessAdd(Position<Bond> &data) {
	bondRiskService -> AddPosition(data);
	return;
}



#endif