/**
 * Future.h define Future product
 * for use in a ProductServices for this product type
 */

#ifndef FUTURE_H
#define FUTURE_H

#include "products.hpp"

using namespace std;
using namespace boost::gregorian;


// Future type
enum FutureType { EuroDollarFuture, BondFuture };

/**
 * Modeling of a Future Product
 */
class Future : public Product {
public:
	// Future ctor
	Future(string _productId, FutureType _futureType, string _underlyingAssetTicker,
	       float _strike, date _maturityDate);
	Future();

	// Return the future type
	FutureType GetFutureType() const;

	// Return the underlying asset ticker of the Future
	string GetUnderlyingAssetTicker() const;

	// Return the strike of the Future
	float GetStrike() const;

	// Return the maturity date of the Future
	date GetMaturityDate() const;

	// Overload the << operator to print out the Future
	friend ostream& operator<<(ostream &output, const Future &future);

private:
	string productId; // product identifier variable
	FutureType futureType; // future type variable
	string underlyingAssetTicker; // underlying asset ticker variable
	float strike; // strike variable
	date maturityDate; // maturity date variable
};

Future::Future(string _productId, FutureType _futureType, string _underlyingAssetTicker,
               float _strike, date _maturityDate): Product(_productId, FUTURE) {
	futureType=_futureType;
	underlyingAssetTicker=_underlyingAssetTicker;
	strike=_strike;
	maturityDate=_maturityDate;
}

Future::Future():Product(0,FUTURE) {

}

FutureType Future::GetFutureType() const {
	return futureType;
}

string Future::GetUnderlyingAssetTicker() const {
	return underlyingAssetTicker;
}

float Future::GetStrike() const {
	return strike;
}

date Future::GetMaturityDate() const {
	return maturityDate;
}

ostream& operator<<(ostream &output, const Future &future) {
	output << future.underlyingAssetTicker << " "
	       << future.strike << " " << future.maturityDate;
	return output;
}

#endif
