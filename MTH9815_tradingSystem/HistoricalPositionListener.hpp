#pragma once 

#ifndef HISTORICALPOSITIONLISTENER_HPP
#define HISTORICALPOSITIONLISTENER_HPP

class HistoricalPositionListener : public ServiceListener<Position<Bond> > {
private:
	BondHistoricalPositionService* service;

public:
	// ctor
	HistoricalPositionListener(BondHistoricalPositionService * p):service(p){}

	virtual void ProcessAdd(Position<Bond> &data) override{
		service->PersistData(data.GetProduct().GetProductId(),data);
		return;
	} 
	virtual void ProcessRemove(Position<Bond> &data) override{} 
	virtual void ProcessUpdate(Position<Bond>&data) override{}

};

#endif 