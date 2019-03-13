/**
 * BondRiskService.hpp
 * receive data from BondPositionService 
 * and pass to BondHistoricalDataService
 */
#pragma once

#ifndef BONDRISKSERVICE_HPP
#define BONDRISKSERVICE_HPP

using namespace std;

#include "BondPositionService.hpp"
#include "riskservice.hpp"
#include "BondInformation.h"

class BondRiskService: public RiskService<Bond> {
private:
	map<string, PV01<Bond> > pv01Map;   
	vector<ServiceListener<PV01<Bond> >*> listenerList;    
public:
	// ctor
	BondRiskService();

	// override pure virtual functions in base class
	// get PV01 given id
	virtual PV01<Bond> & GetData(string id) override;              
	
	// no connector in this case, no use
	virtual void OnMessage(PV01<Bond> & pv01) override{return;}
	
	// add a listener, in this case, BondHistoricalDataService
	virtual void AddListener(ServiceListener<PV01<Bond> > *listener) override; 
	
	// get listeners, in this case, BondHistoricalDataService
	virtual const vector<ServiceListener<PV01<Bond> > *>& GetListeners() const override; 
	
	// add positions to map
	virtual void AddPosition(Position<Bond> &position) override;    
	
	// get total risk
	virtual double GetBucketedRisk(const BucketedSector<Bond> &sector) const override;  

};


BondRiskService::BondRiskService(){
	pv01Map=map<string, PV01<Bond> >();
}

PV01<Bond> & BondRiskService::GetData(string id){
	return pv01Map.at(id);
}             

void BondRiskService::AddListener(ServiceListener<PV01<Bond> > *listener){
	listenerList.push_back(listener);
	return;
}

const vector<ServiceListener<PV01<Bond> > *>& BondRiskService::GetListeners() const{
	return listenerList;
}
	

void BondRiskService::AddPosition(Position<Bond> &position){
	auto bond=position.GetProduct();
	auto id=bond.GetProductId();
	auto it=pv01Map.find(id);
	
	long quantity=position.GetAggregatePosition();
	
	if(it!=pv01Map.end()){
		(it->second).AddQuantity(quantity);
	}
	else{
		pv01Map.insert(pair<string,PV01<Bond> >(id,PV01<Bond>(bond,bondRisk[id],quantity)));
	}
	it=pv01Map.find(id);
	
	for(auto& listener:listenerList){
		listener->ProcessAdd(it->second);
	}
	
	return;
} 
	

double BondRiskService::GetBucketedRisk(const BucketedSector<Bond> &sector) const{
	double res = 0;
	for(auto& product : sector.GetProducts()) {
		res+=pv01Map.at(product.GetProductId()).GetPV01();
	}
	return res;
}  


#endif