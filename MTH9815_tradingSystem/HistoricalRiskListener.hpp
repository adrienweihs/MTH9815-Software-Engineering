#pragma once 

#ifndef HISTORICALRISKLISTENER_HPP
#define HISTORICALRISKLISTENER_HPP

class HistoricalRiskListener : public ServiceListener<PV01<Bond> > {
private:
	BondHistoricalRiskService* service;

public:
	// ctor
	HistoricalRiskListener(BondHistoricalRiskService * p):service(p){}

	virtual void ProcessAdd(PV01<Bond> &data) override{
		service->PersistData(data.GetProduct().GetProductId(),data);
		return;
	} 
	virtual void ProcessRemove(PV01<Bond> &data) override{} 
	virtual void ProcessUpdate(PV01<Bond> &data) override{}

};

#endif 