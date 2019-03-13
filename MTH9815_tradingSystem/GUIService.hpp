#pragma once

#ifndef GUISERVICE_HPP
#define GUISERVICE_HPP

#include "boost/date_time/posix_time/posix_time.hpp"
using namespace std;
using namespace boost::posix_time;

#include <boost/date_time.hpp>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include "pricingservice.hpp"
#include "soa.hpp"

class GUIServiceConnector;

class PriceWithTimeStamp: public Price<Bond>{
private:
	ptime timeStamp;
public:
	PriceWithTimeStamp(ptime _timeStamp,Price<Bond> _price)
	:Price<Bond>(_price){
		timeStamp=_timeStamp;
	}
	
	ptime GetTimeStamp(){
		return timeStamp;
	}
};

class GUIService:public PricingService<Bond> {
private:
	GUIServiceConnector* gUIServiceConnector;
	ptime lastSendTime;
	time_duration throtteTime;
public:
	// ctor
	GUIService(GUIServiceConnector* _gUIServiceConnector);
	
	// called by listener
	void SendToThrottle(Price<Bond>& data);
	
	// override pure virtual functions in Service class
	// no use in this case
	virtual Price<Bond>& GetData(string id) override{}
	
	// called by connector, no use in this case
	virtual void OnMessage(Price<Bond> &data) override{}
	
	// add a listener, in this case, no use
	virtual void AddListener(ServiceListener<Price<Bond> > *listener) override{}
	
	// get listeners, in this case, no use
	virtual const vector< ServiceListener<Price<Bond> >* >& GetListeners() const override{}
};

GUIService::GUIService(GUIServiceConnector* _gUIServiceConnector){
	gUIServiceConnector=_gUIServiceConnector;
	throtteTime=millisec(3);
	lastSendTime=microsec_clock::local_time();
}

// define void GUIService::SendToThrottle(Price<Bond>& data) in GUIServiceCOnnector.hpp



#endif