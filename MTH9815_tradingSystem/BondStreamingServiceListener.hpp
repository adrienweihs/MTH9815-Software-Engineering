/**
 * BondStreamingServiceListener.hpp
 * defines BondStreamingServiceListener class to pass data from 
 * BondAlgoStreamingService to BondStreamingService
 */ 
#pragma once

#ifndef BONDSTREAMINGSERVICELISTENER_HPP
#define BONDSTREAMINGSERVICELISTENER_HPP

#include "BondStreamingService.hpp"
#include "soa.hpp"

using namespace std;

class BondStreamingServiceListener: public ServiceListener<AlgoStream>{
private:
    BondStreamingService* bondStreamingService;

public:
    // ctor
    BondStreamingServiceListener(BondStreamingService* _bondStreamingService);

    // override pure virtual functions in ServiceListener class
	// pass AlgoStream from BondAlgoStreamingService to BondStreamingService
	// call addAlgo and also PublishPrice in BondStreamingService 
    virtual void ProcessAdd(AlgoStream& algoStream) override; 
	
	// in this case, do not need this method
    virtual void ProcessRemove(AlgoStream &) override;  
	
	// in this case, do not need this method
    virtual void ProcessUpdate(AlgoStream &) override;  
};

BondStreamingServiceListener::BondStreamingServiceListener(BondStreamingService* _bondStreamingService){
	bondStreamingService=_bondStreamingService;
}

void BondStreamingServiceListener::ProcessAdd(AlgoStream& algoStream){
	bondStreamingService->AddAlgo(algoStream);
	auto priceStream=algoStream.GetPriceStream();
    bondStreamingService->PublishPrice(priceStream);
	return;
}

void BondStreamingServiceListener::ProcessRemove(AlgoStream& data){
	return;
}

void BondStreamingServiceListener::ProcessUpdate(AlgoStream& data){
	return;
}
#endif