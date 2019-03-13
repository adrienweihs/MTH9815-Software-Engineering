/**
 * BondInquiryService.hpp
 * receive data from connector and pass to BondHistoricalDataService
 */ 
#pragma once 

#ifndef BONDINQUIRYSERVICE_HPP
#define BONDINQUIRYSERVICE_HPP

using namespace std;

#include "BondInquiryServiceConnector.hpp"
#include <string>
#include <map>
#include <vector>

class BondInquiryService: public InquiryService<Bond>{
private:
    map<string, Inquiry<Bond> > inquiryMap;  
	vector<ServiceListener<Inquiry<Bond> >*> listenerList;

public:
    // ctor
    BondInquiryService();

    // override virtual functions
	// get inquiry given id
    virtual Inquiry<Bond> & GetData(string id) override;   

	// called by connector
    virtual void OnMessage(Inquiry<Bond> &inquiry) override;        

	// add a listener, in this case, BondHistoricalDataServiceListener
    virtual void AddListener(ServiceListener<Inquiry<Bond> > *listener) override;  
	
	// get listeners, in this case, BondHistoricalDataServiceListener
    virtual const vector<ServiceListener<Inquiry<Bond> > *>& GetListeners() const override;  
	
	// send quote back to client. Here client is a txt file. no use here
    virtual void SendQuote(const string& inquiryId, double price) override{} 
	
	// reject quote. Here client is a txt file. no use here
    virtual void RejectInquiry(const string &inquiryId) override{}
	
};

BondInquiryService::BondInquiryService(){
	inquiryMap=map<string, Inquiry<Bond> >();
}

Inquiry<Bond> & BondInquiryService::GetData(string id){
	return inquiryMap.at(id);
}

void BondInquiryService::OnMessage(Inquiry<Bond> &inquiry){
	inquiry.SetState(inquiry.GetPrice(), DONE);
    inquiryMap.insert(pair<string,Inquiry<Bond> >(inquiry.GetInquiryId(),inquiry));
    for(auto& listener : listenerList) {
        listener->ProcessAdd(inquiry); 
	}
	
	return;
}

void BondInquiryService::AddListener(ServiceListener<Inquiry<Bond> > *listener){
	listenerList.push_back(listener);
	return;
}

const vector<ServiceListener<Inquiry<Bond> > *>& BondInquiryService::GetListeners() const{
	return listenerList;
}


void BondInquiryServiceConnector::Subscribe(){
	ifstream input;
	input.open("inquiries.txt");
	string row;
	
	while (getline(input, row)) {
		stringstream line(row);
		string temp;
		
		getline(line, temp, ',');   
		string inquiry_ID = temp;
		
		getline(line, temp, ',');
		auto bond = bondProductService->GetData(temp);
		
		getline(line, temp, ',');
		Side side = (temp=="BUY" ? BUY:SELL);
            
		getline(line, temp, ',');
		long quantity = stol(temp);
		
		getline(line, temp, ',');
		double quote = TransformStringToPrice(temp);
            
		getline(line, temp, ',');
		InquiryState state_ = RECEIVED;
		
		Inquiry<Bond> inquiry(inquiry_ID, bond, side, quantity, quote, state_);
		bondInquiryService -> OnMessage(inquiry);
	}
	return;
}

#endif