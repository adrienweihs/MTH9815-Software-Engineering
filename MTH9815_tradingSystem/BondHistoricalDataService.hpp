#pragma once

#ifndef BONDHISTORICALDATASERVICE_HPP
#define BONDHISTORICALDATASERVICE_HPP

#include <iostream>
#include "historicaldataservice.hpp"
#include "GUIServiceConnector.hpp"
#include "BondStreamingService.hpp"
#include "BondRiskService.hpp"
#include "BondPositionService.hpp"
#include "BondExecutionService.hpp"
#include "BondInquiryService.hpp"

using namespace std;

class HistoricalPositionConnector;
class HistoricalRiskConnector;
class HistoricalExecutionConnector;
class HistoricalStreamingConnector;
class HistoricalAllInquiriesConnector;


class BondHistoricalPositionService: public HistoricalDataService<Position<Bond> > {
private:
	HistoricalPositionConnector* connector;
	map<string, Position<Bond> > dataMap;
public:
	// ctor
	BondHistoricalPositionService(HistoricalPositionConnector* _p):connector(_p){}

	// override pure virtual functions in base class
	// get data given id
	virtual Position<Bond>  & GetData(string id) override {return dataMap.at(id);}

	// no use
	virtual void OnMessage(Position<Bond>  & bond) override {}

	// no use
	virtual void AddListener(ServiceListener<Position<Bond>  > *listener) override {}

	// no use
	virtual const vector<ServiceListener<Position<Bond>  > *>& GetListeners() const override {}

	// called by listeners, call correspoding connector to publish
	virtual void PersistData(string persistKey, Position<Bond>& data) override;
};


class BondHistoricalRiskService: public HistoricalDataService<PV01<Bond> > {
private:
	HistoricalRiskConnector* connector;
	map<string, PV01<Bond> > dataMap;
public:
	// ctor
	BondHistoricalRiskService(HistoricalRiskConnector* _p):connector(_p){}

	// override pure virtual functions in base class
	// get data given id
	virtual PV01<Bond>  & GetData(string id) override {return dataMap.at(id);}

	// no use
	virtual void OnMessage(PV01<Bond>  & bond) override {}

	// no use
	virtual void AddListener(ServiceListener<PV01<Bond>  > *listener) override {}

	// no use
	virtual const vector<ServiceListener<PV01<Bond>  > *>& GetListeners() const override {}

	// called by listeners, call correspoding connector to publish
	virtual void PersistData(string persistKey, PV01<Bond>& data) override;
};


class BondHistoricalExecutionService: public HistoricalDataService<ExecutionOrder<Bond> > {
private:
	HistoricalExecutionConnector* connector;
	map<string, ExecutionOrder<Bond> > dataMap;
public:
	// ctor
	BondHistoricalExecutionService(HistoricalExecutionConnector* _p):connector(_p){}

	// override pure virtual functions in base class
	// get data given id
	virtual ExecutionOrder<Bond> & GetData(string id) override {return dataMap.at(id);}

	// no use
	virtual void OnMessage(ExecutionOrder<Bond> & bond) override {}

	// no use
	virtual void AddListener(ServiceListener<ExecutionOrder<Bond>  > *listener) override {}

	// no use
	virtual const vector<ServiceListener<ExecutionOrder<Bond>  > *>& GetListeners() const override {}

	// called by listeners, call correspoding connector to publish
	virtual void PersistData(string persistKey, ExecutionOrder<Bond>& data) override;
};


class BondHistoricalStreamingService: public HistoricalDataService<PriceStream<Bond> > {
private:
	HistoricalStreamingConnector* connector;
	map<string, PriceStream<Bond> > dataMap;
public:
	// ctor
	BondHistoricalStreamingService(HistoricalStreamingConnector* _p):connector(_p){}

	// override pure virtual functions in base class
	// get data given id
	virtual PriceStream<Bond> & GetData(string id) override {return dataMap.at(id);}

	// no use
	virtual void OnMessage(PriceStream<Bond> & bond) override {}

	// no use
	virtual void AddListener(ServiceListener<PriceStream<Bond>  > *listener) override {}

	// no use
	virtual const vector<ServiceListener<PriceStream<Bond>  > *>& GetListeners() const override {}

	// called by listeners, call correspoding connector to publish
	virtual void PersistData(string persistKey, PriceStream<Bond>& data) override;
};


class BondHistoricalAllInquiriesService: public HistoricalDataService<Inquiry<Bond> > {
private:
	HistoricalAllInquiriesConnector* connector;
	map<string, Inquiry<Bond> > dataMap;
public:
	// ctor
	BondHistoricalAllInquiriesService(HistoricalAllInquiriesConnector* _p):connector(_p){}

	// override pure virtual functions in base class
	// get data given id
	virtual Inquiry<Bond> & GetData(string id) override {return dataMap.at(id);}

	// no use
	virtual void OnMessage(Inquiry<Bond> & bond) override {}

	// no use
	virtual void AddListener(ServiceListener<Inquiry<Bond>  > *listener) override {}

	// no use
	virtual const vector<ServiceListener<Inquiry<Bond> > *>& GetListeners() const override {}

	// called by listeners, call correspoding connector to publish
	virtual void PersistData(string persistKey, Inquiry<Bond>& data) override;
};


#endif
