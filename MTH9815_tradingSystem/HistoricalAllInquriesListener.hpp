#pragma once 

#ifndef HISTORICALINQUIRYLISTENER_HPP
#define HISTORICALINQUIRYLISTENER_HPP

class HistoricalAllInquriesListener : public ServiceListener<Inquiry<Bond> > {
private:
	BondHistoricalAllInquiriesService* service;

public:
	// ctor
	HistoricalAllInquriesListener(BondHistoricalAllInquiriesService * p):service(p){}

	virtual void ProcessAdd(Inquiry<Bond> &data) override{
		service->PersistData(data.GetInquiryId(),data);
		return;
	} 
	virtual void ProcessRemove(Inquiry<Bond> &data) override{} 
	virtual void ProcessUpdate(Inquiry<Bond>  &data) override{}

};

#endif 