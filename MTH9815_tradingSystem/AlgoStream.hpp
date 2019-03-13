/**
 * AlgoStream.hpp
 * Defines AlgoStream class, to be used as key of BondAlgoStreamingService
 * 
 */
#pragma once

#ifndef ALGOSTREAM_HPP
#define ALGOSTREAM_HPP

#include "streamingservice.hpp"
#include "pricingservice.hpp"
#include "products.hpp"
#include <iostream>

using namespace std;

class AlgoStream{
private:
	PriceStream<Bond> priceStream;
public:
	// ctor
	AlgoStream(const PriceStream<Bond>& _priceStream);
	
	// run algo to update priceStream according to bond price
	void RunAlgo(Price<Bond> price);
	
	// return *priceStream
	PriceStream<Bond> GetPriceStream() const;
};


AlgoStream::AlgoStream(const PriceStream<Bond>& _priceStream):priceStream(_priceStream){
}

void AlgoStream::RunAlgo( Price<Bond> price){
	auto bond = price.GetProduct();
	// not this PriceStream to update
	if(bond.GetProductId() != priceStream.GetProduct().GetProductId()) return;
    
	float mid=price.GetMid();
	float spread=price.GetBidOfferSpread();
	float bid=mid-spread/2.0;
	float offer=mid+spread/2.0;
	
	// if spread is tight
	if(spread<2.5/256.0){
		PriceStreamOrder order_bid(bid, 1000000, 2000000, BID);
		PriceStreamOrder order_ask(offer, 1000000, 2000000, OFFER);
		priceStream = PriceStream<Bond>(bond, order_bid, order_ask);
	}
	// if spread is not tight 
    else{
		PriceStreamOrder order_bid(bid, 0, 0, BID);
		PriceStreamOrder order_ask(offer, 0, 0, OFFER);
		priceStream = PriceStream<Bond>(bond, order_bid, order_ask);
	}
	
	return;
}


PriceStream<Bond> AlgoStream::GetPriceStream() const{
	return priceStream;
}
#endif 