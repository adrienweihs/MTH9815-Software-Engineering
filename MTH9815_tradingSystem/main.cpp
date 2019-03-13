#include <iostream>
#include "AlgoStream.hpp"
#include "BondAlgoStreamingService.hpp"
#include "BondPricingService.hpp"
#include "BondProductService.hpp"
#include "BondStreamingService.hpp"
#include "BondPricingServiceConnector.hpp"
#include "BondStreamingServiceConnector.hpp"
#include "BondAlgoStreamingServiceListener.hpp"
#include "BondStreamingServiceListener.hpp"
#include "AlgoExecution.hpp"
#include "BondAlgoExecutionService.hpp"
#include "BondExecutionService.hpp"
#include "BondMarketDataService.hpp"
#include "BondAlgoExecutionServiceListener.hpp"
#include "BondExecutionServiceListener.hpp"
#include "BondExecutionServiceConnector.hpp"
#include "BondMarketDataServiceConnector.hpp"
#include "MarketdataGenerator.hpp"
#include "PricesGenerator.hpp"
#include "BondPositionService.hpp"
#include "BondRiskService.hpp"
#include "BondTradeBookingService.hpp"
#include "BondPositionServiceListener.hpp"
#include "BondRiskServiceListener.hpp"
#include "BondTradingBookingServiceConnector.hpp"
#include "TradesGenerator.hpp"
#include "GUIService.hpp"
#include "GUIServiceConnector.hpp"
#include "GUIServiceListener.hpp"
#include "BondInquiryService.hpp"
#include "BondInquiryServiceConnector.hpp"
#include "BondTradeBookingServiceListener.hpp"
#include "HistoricalAllInquiriesConnector.hpp"
#include "HistoricalAllInquriesListener.hpp"
#include "HistoricalExecutionConnector.hpp"
#include "HistoricalExecutionListener.hpp"
#include "HistoricalPositionConnector.hpp"
#include "HistoricalPositionListener.hpp"
#include "HistoricalRiskConnector.hpp"
#include "HistoricalRiskListener.hpp"
#include "HistoricalStreamingConnector.hpp"
#include "HistoricalSteamingListener.hpp"
#include "BondHistoricalDataService.hpp"
#include "InquriesGenerator.hpp"

int main(int argc, char **argv) {
	// Generate txt data
	PricesGenerator PG;
	MarketdataGenerator MG;
	TradesGenerator TG;
	InquriesGenerator IG;
	 
	// you can change the generated data's size here 
	TG(100);
	PG(100);
	MG(100);
	IG(100);
	
	// connect and build the whole system
	vector<Bond> bondsType;
	for(int i=0; i<6; i++)
		bondsType.push_back(Bond(bondCusip[i],CUSIP,"T",bondCoupon[i],bondMaturity[i]));

	BondProductService* bondProductService = new BondProductService();
	for(int i=0; i<6; i++)
		bondProductService->Add(bondsType[i]);

	// **************left**********
	BondPricingService* bondPricingService=new BondPricingService();
	BondPricingServiceConnector* bondPricingServiceConnector
	    =new BondPricingServiceConnector(bondPricingService,bondProductService);

	BondAlgoStreamingService* bondAlgoStreamingService=new BondAlgoStreamingService();
	BondAlgoStreamingServiceListener* bondAlgoStreamingServiceListener
	    =new BondAlgoStreamingServiceListener(bondAlgoStreamingService);
		
	bondPricingService->AddListener(bondAlgoStreamingServiceListener);

	BondStreamingServiceConnector* bondStreamingServiceConnector=new BondStreamingServiceConnector();
	BondStreamingService* bondStreamingService=new BondStreamingService(bondStreamingServiceConnector);
	BondStreamingServiceListener* bondStreamingServiceListener=new BondStreamingServiceListener(bondStreamingService);

	bondAlgoStreamingService->AddListener(bondStreamingServiceListener);

	
	// **************right**********
	BondMarketDataService* bondMarketDataService=new BondMarketDataService(); 
	BondMarketDataServiceConnector* bondMarketDataServiceConnector
		=new BondMarketDataServiceConnector(bondMarketDataService,bondProductService);
	
	BondAlgoExecutionService* bondAlgoExecutionService=new BondAlgoExecutionService();
	BondAlgoExecutionServiceListener* bondAlgoExecutionServiceListener
		=new BondAlgoExecutionServiceListener(bondAlgoExecutionService);
	
	bondMarketDataService->AddListener(bondAlgoExecutionServiceListener);
	
	BondExecutionServiceConnector* bondExecutionServiceConnector=new BondExecutionServiceConnector();
	BondExecutionService* bondExecutionService=new BondExecutionService(bondExecutionServiceConnector);
	BondExecutionServiceListener* bondExecutionServiceListener=new BondExecutionServiceListener(bondExecutionService);
	
	bondAlgoExecutionService->AddListener(bondExecutionServiceListener);

	
	// **************middle**********
	BondTradeBookingService* bondTradeBookingService=new BondTradeBookingService();
	BondTradingBookingServiceConnector* bondTradingBookingServiceConnector
		=new BondTradingBookingServiceConnector(bondTradeBookingService,bondProductService);
	
	BondPositionService* bondPositionService=new BondPositionService();
	BondPositionServiceListener* bondPositionServiceListener=new BondPositionServiceListener(bondPositionService);
	
	bondTradeBookingService->AddListener(bondPositionServiceListener);
	
	BondRiskService* bondRiskService=new BondRiskService();
	BondRiskServiceListener* bondRiskServiceListener=new BondRiskServiceListener(bondRiskService);
	
	bondPositionService->AddListener(bondRiskServiceListener);
	
	BondTradeBookingServiceListener* bondTradeBookingServiceListener
		=new BondTradeBookingServiceListener(bondTradeBookingService);
	bondExecutionService->AddListener(bondTradeBookingServiceListener);
	
	
	// **************GUI & Inquiry**********
	GUIServiceConnector* gUIServiceConnector=new GUIServiceConnector();
	GUIService* gUIService=new GUIService(gUIServiceConnector);
	GUIServiceListener* gUIServiceListener=new GUIServiceListener(gUIService);
	
	bondPricingService->AddListener(gUIServiceListener);
	
	
	BondInquiryService* bondInquiryService=new BondInquiryService();
	BondInquiryServiceConnector* bondInquiryServiceConnector
		=new BondInquiryServiceConnector(bondInquiryService,bondProductService);
	
	
	// **************Historical**********
	HistoricalPositionConnector* historicalPositionConnector=new HistoricalPositionConnector();
	BondHistoricalPositionService* bondHistoricalPositionService=new BondHistoricalPositionService(historicalPositionConnector);
	HistoricalPositionListener* historicalPositionListener=new HistoricalPositionListener(bondHistoricalPositionService);
	bondPositionService->AddListener(historicalPositionListener);
	
	HistoricalRiskConnector* historicalRiskConnector=new HistoricalRiskConnector();
	BondHistoricalRiskService* bondHistoricalRiskService=new BondHistoricalRiskService(historicalRiskConnector);
	HistoricalRiskListener* historicalRiskListener=new HistoricalRiskListener(bondHistoricalRiskService);
	bondRiskService->AddListener( historicalRiskListener);
	
	HistoricalExecutionConnector* historicalExecutionConnector=new HistoricalExecutionConnector();
	BondHistoricalExecutionService* bondHistoricalExecutionService=new BondHistoricalExecutionService(historicalExecutionConnector);
	HistoricalExecutionListener* historicalExecutionListener=new HistoricalExecutionListener(bondHistoricalExecutionService);
	bondExecutionService->AddListener(historicalExecutionListener);
	
	HistoricalStreamingConnector* historicalStreamingConnector=new HistoricalStreamingConnector();
	BondHistoricalStreamingService* bondHistoricalStreamingService=new BondHistoricalStreamingService(historicalStreamingConnector);
	HistoricalStreamingListener* historicalStreamingListener=new HistoricalStreamingListener(bondHistoricalStreamingService);
	bondStreamingService->AddListener(historicalStreamingListener);
	
	HistoricalAllInquiriesConnector* historicalAllInquiriesConnector=new HistoricalAllInquiriesConnector();
	BondHistoricalAllInquiriesService* bondHistoricalAllInquiriesService=new BondHistoricalAllInquiriesService(historicalAllInquiriesConnector);
	HistoricalAllInquriesListener* historicalAllInquriesListener=new HistoricalAllInquriesListener(bondHistoricalAllInquiriesService);
	bondInquiryService->AddListener(historicalAllInquriesListener);

	// Run the system
	bondPricingServiceConnector->Subscribe();
	bondMarketDataServiceConnector->Subscribe();
	bondTradingBookingServiceConnector->Subscribe();
	bondInquiryServiceConnector->Subscribe();
	
	return 0;
}
