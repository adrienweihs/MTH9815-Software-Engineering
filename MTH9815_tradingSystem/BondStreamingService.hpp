/**
 * BondStreamingService_hpp
 * Defines BondStreamingService to receive data from BondAlgoSteamingService
 * and pass data to another connector which can publish streams
 */ 
#pragma once

#ifndef BONDSTREAMINGSERVICE_HPP
#define BONDSTREAMINGSERVICE_HPP

#include "streamingservice.hpp"
#include "BondAlgoStreamingService.hpp"


using namespace std;

class BondStreamingServiceConnector;

class BondStreamingService: public StreamingService<Bond>{
private:
	map<string, PriceStream<Bond> > streamMap;
	vector<ServiceListener<PriceStream<Bond> >*> listenerList;
	BondStreamingServiceConnector* bondStreamingServiceConnector;
public:
	// ctor
    BondStreamingService(BondStreamingServiceConnector* _bondStreamingServiceConnector);

    // override pure virtual functions in base class
	// given id, return PriceStream from streamMap
    virtual PriceStream<Bond>& GetData(string id) override;   

	// no subscribe connector to call this method
    virtual void OnMessage(PriceStream<Bond>&) override;  
	
	// add a listener. in this case, should be BondHistoricalDataServiceListener
    virtual void AddListener(ServiceListener<PriceStream<Bond> > *listener) override;  
	
	// get listeners. in this case, should be BondHistoricalDataServiceListener
    virtual const vector<ServiceListener<PriceStream<Bond> > *>& GetListeners() const override;  
	
	// call connector's Publish method to print stream
    virtual void PublishPrice(PriceStream<Bond>& priceStream) override;  
	
	// called by BondStreamingServiceListener, pass AlgoStream from BondAlgoStreamingService
    void AddAlgo(const AlgoStream& algo);          
};

BondStreamingService::BondStreamingService(BondStreamingServiceConnector*_bondStreamingServiceConnector){
	bondStreamingServiceConnector=_bondStreamingServiceConnector;
	streamMap=map<string, PriceStream<Bond> >();
}

PriceStream<Bond>& BondStreamingService::GetData(string id){
	return streamMap.at(id);
}

void BondStreamingService::OnMessage(PriceStream<Bond>& stream){
	return;
}

void BondStreamingService::AddListener(ServiceListener<PriceStream<Bond> > *listener){
	listenerList.push_back(listener);
	return;
}

const vector<ServiceListener<PriceStream<Bond> > *>& BondStreamingService::GetListeners() const{
	return listenerList;
}

// void BondStreamingService::PublishPrice(PriceStream<Bond>&) defined in BondStreamingServiceConnector.hpp

void BondStreamingService::AddAlgo(const AlgoStream& algo){
	// priceStream
	auto stream=algo.GetPriceStream();
	auto id =stream.GetProduct().GetProductId();
	if(streamMap.find(id)!=streamMap.end())
		streamMap.erase(id);
	streamMap.insert(pair<string,PriceStream<Bond> >(id,stream));
	for(auto& listener:listenerList){
		listener->ProcessAdd(stream);
	}

	return;
}
#endif 