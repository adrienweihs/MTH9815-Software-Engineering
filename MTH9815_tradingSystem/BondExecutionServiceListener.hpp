/**
 * BondExecutionServiceListener.hpp
 * defines listener to pass data from BondAlgoExecutionService
 * to BondExecutionService
 */ 
#pragma once 

#ifndef BONDEXECUTIONSERVICELISTENER_HPP
#define BONDEXECUTIONSERVICELISTENER_HPP

using namespace std;

#include "BondAlgoExecutionService.hpp"
#include "soa.hpp"
 
class BondExecutionServiceListener: public ServiceListener<AlgoExecution>{
private:
    BondExecutionService* bondExecutionService;

public:
    // ctor
    BondExecutionServiceListener(BondExecutionService* _bondExecutionService);

    // override pure virtual functions in base class
	// called by BondAlgoExecutionService and call BondExecutionService::AddAlgoExecution
	// and BondExecutionService::ExecuteOrder
    virtual void ProcessAdd(AlgoExecution &data) override; 
	
	// no use in this case
    virtual void ProcessRemove(AlgoExecution &data) override{};
	
	// no use in this case
    virtual void ProcessUpdate(AlgoExecution &data) override{}; 
	
};

BondExecutionServiceListener::BondExecutionServiceListener(BondExecutionService* _bondExecutionService){
	bondExecutionService=_bondExecutionService;
}

void BondExecutionServiceListener::ProcessAdd(AlgoExecution &data){
	auto order=data.GetExecutionOrder();
	bondExecutionService->AddAlgoExecution(data);
	bondExecutionService->ExecuteOrder(order,BROKERTEC);
	return;
}


#endif