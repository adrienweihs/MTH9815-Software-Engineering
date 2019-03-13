/**
 * GUIServiceConnector.hpp
 */ 
#pragma once

#ifndef GUISERVICECONNECTOR_HPP
#define GUISERVICECONNECTOR_HPP

using namespace std;

#include "soa.hpp"
#include "GUIService.hpp"
#include "products.hpp"
#include <string>
#include <iostream>

class GUIServiceConnector: public Connector<PriceWithTimeStamp >{
public:
    // ctor
    GUIServiceConnector(){};

    // do nothing, publish only
	virtual void Subscribe() override{}
	
	// print price with time stamp
	virtual void Publish(PriceWithTimeStamp& data) override;
};


void GUIServiceConnector::Publish(PriceWithTimeStamp& data) {
	auto timeStamp=data.GetTimeStamp();
	auto bond=data.GetProduct();
	auto mid=data.GetMid();
	auto spread=data.GetBidOfferSpread();
	
    ofstream out;
    out.open("gui.txt",ios::app);
	out<<timeStamp<<","<<bond.GetProductId()<<","<<mid<<","<<spread<<endl;

    return;
}


void GUIService::SendToThrottle(Price<Bond>& data){
	ptime timeNow = microsec_clock::local_time();
	time_duration diff=timeNow-lastSendTime;

	if(diff < throtteTime){
		//c not enought for 3 millisecond
		return;
	}
	lastSendTime=timeNow;
	auto pts=PriceWithTimeStamp(timeNow,data);
	gUIServiceConnector->Publish(pts);

	return;
}

#endif