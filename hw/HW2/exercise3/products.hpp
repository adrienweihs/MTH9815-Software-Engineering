/**
 * products.hpp mdeosl Bond and Interest Rate Swap products
 * for use in a ProductServices for these product types
 */

#ifndef PRODUCTS_HPP
#define PRODUCTS_HPP

#include <iostream>
#include <string>

#include "boost/date_time/gregorian/gregorian.hpp"

using namespace std;
using namespace boost::gregorian;

// Product Types
enum ProductType { IRSWAP, BOND, FUTURE };

/**
 * Definition of a base Product class
 */
class Product
{

public:
  // Product ctor
  Product(string _productId, ProductType _productType);

  // Retrurn the product identifier
  string GetProductId() const;

  // Return the Product Type for this Product
  ProductType GetProductType() const;

private:
  string productId; // product id variab;e
  ProductType productType; // product type variable
};

// Types of bond identifiers: ISIN (used primarily in Europe) and CUSIP (for US)
enum BondIdType { CUSIP, ISIN };

/**
 * Modeling of a Bond Product
 */
class Bond : public Product
{
public:
  // Bond ctor
  Bond(string _productId, BondIdType _bondIdType, string _ticker, float _coupon, date _maturityDate);
  Bond();

  // Return the ticker of the bond
  string GetTicker() const;

  // Return the coupon of the bond
  float GetCoupon() const;

  // Return the maturity date of the bond
  date GetMaturityDate() const;

  // Return the bond identifier type
  BondIdType GetBondIdType() const;

  // Overload the << operator to print out the bond
  friend ostream& operator<<(ostream &output, const Bond &bond);

private:
  string productId; // product identifier variable
  BondIdType bondIdType; // bond id type variable
  string ticker; // ticker variable
  float coupon; // coupon variable
  date maturityDate; // maturity date variable
};

// Day Count convention values
enum DayCountConvention { THIRTY_THREE_SIXTY, ACT_THREE_SIXTY, ACT_THREE_SIXTY_FIVE};

// Payment Frequency values
enum PaymentFrequency { QUARTERLY, SEMI_ANNUAL, ANNUAL };

// Index on the floating leg of an IR Swap
enum FloatingIndex { LIBOR, EURIBOR };

// Tenor on the floating leg of an IR Swap
enum FloatingIndexTenor { TENOR_1M, TENOR_3M, TENOR_6M, TENOR_12M };

// Currency for the IR Swap
enum Currency { USD, EUR, GBP };

// IR Swap type
enum SwapType { SPOT, FORWARD, IMM, MAC, BASIS };

// IR Swap leg type (i.e. outright is one leg, curve is two legs, fly is three legs
enum SwapLegType { OUTRIGHT, CURVE, FLY };

/**
 * Modeling of an Interest Rate Swap Product
 */
class IRSwap : public Product
{
public:
  // IRSwap ctor
  IRSwap(string productId, DayCountConvention _fixedLegDayCountConvention, DayCountConvention _floatingLegDayCountConvention, PaymentFrequency _fixedLegPaymentFrequency, FloatingIndex _floatingIndex, FloatingIndexTenor _floatingIndexTenor, date _effectiveDate, date _terminationDate, Currency _currency, int termYears, SwapType _swapType, SwapLegType _swapLegType);
  IRSwap();

  // Return the day count convention on the fixed leg of the IR Swap
  DayCountConvention GetFixedLegDayCountConvention() const;

  // Return the day count convention on the floating leg of the IR Swap
  DayCountConvention GetFloatingLegDayCountConvention() const;

  // Return the payment frequency on the fixed leg of the IR Swap
  PaymentFrequency GetFixedLegPaymentFrequency() const;

  // Return the index on the floating leg of the IR Swap
  FloatingIndex GetFloatingIndex() const;

  // Return the tenor on the floating leg of the IR Swap
  FloatingIndexTenor GetFloatingIndexTenor() const;

  // Return the effective date of the IR Swap (i.e. when the IR Swap starts)
  date GetEffectiveDate() const;

  // Return the termination date of the IR Swap (i.e. when the IR Swap ends)
  date GetTerminationDate() const;

  // Return the currency of the IR Swap
  Currency GetCurrency() const;

  // Return the term in years of the IR Swap
  int GetTermYears() const;

  // Return the swap type of the IR Swap
  SwapType GetSwapType() const;

  // Return the swap leg type of the IR Swap
  SwapLegType GetSwapLegType() const;

  // Overload the << operator to print the IR Swap
  friend ostream& operator<<(ostream &output, const IRSwap &swap);

private:
  DayCountConvention fixedLegDayCountConvention; // fixed leg daycount convention variable
  DayCountConvention floatingLegDayCountConvention; // floating leg daycount convention variable
  PaymentFrequency fixedLegPaymentFrequency; // fixed leg payment freq
  FloatingIndex floatingIndex; // floating leg index
  FloatingIndexTenor floatingIndexTenor; // floating leg tenor
  date effectiveDate; // effective date
  date terminationDate; // termination date
  Currency currency; // currency
  int termYears; // term in years
  SwapType swapType; // swap type
  SwapLegType swapLegType; // swap leg type

  // return a string represenation for the day count convention
  string ToString(DayCountConvention dayCountConvention) const;

  // return a string represenation for the payment frequency
  string ToString(PaymentFrequency paymentFrequency) const;

  // return a string representation for the floating index
  string ToString(FloatingIndex floatingIndex) const;

  // return a string representation of the flaoting index tenor
  string ToString(FloatingIndexTenor floatingIndexTenor) const;

  // return a string representation of the currency
  string ToString(Currency currency) const;

  // return a string representation of the swap type
  string ToString(SwapType swapType) const;

  // return a string representation of the swap leg type
  string ToString(SwapLegType swapLegType) const;
};

Product::Product(string _productId, ProductType _productType)
{
  productId = _productId;
  productType = _productType;
}

string Product::GetProductId() const
{
  return productId;
}

ProductType Product::GetProductType() const
{
  return productType;
}

Bond::Bond(string _productId, BondIdType _bondIdType, string _ticker, float _coupon, date _maturityDate) : Product(_productId, BOND)
{
  bondIdType = _bondIdType;
  ticker = _ticker;
  coupon = _coupon;
  maturityDate = _maturityDate;
}

Bond::Bond() : Product(0, BOND)
{
}

string Bond::GetTicker() const
{
  return ticker;
}

float Bond::GetCoupon() const
{
  return coupon;
}

date Bond::GetMaturityDate() const
{
  return maturityDate;
}

BondIdType Bond::GetBondIdType() const
{
  return bondIdType;
}

ostream& operator<<(ostream &output, const Bond &bond)
{
  output << bond.ticker << " " << bond.coupon << " " << bond.GetMaturityDate();
  return output;
}

IRSwap::IRSwap(string _productId, DayCountConvention _fixedLegDayCountConvention, DayCountConvention _floatingLegDayCountConvention, PaymentFrequency _fixedLegPaymentFrequency, FloatingIndex _floatingIndex, FloatingIndexTenor _floatingIndexTenor, date _effectiveDate, date _terminationDate, Currency _currency, int _termYears, SwapType _swapType, SwapLegType _swapLegType)  : Product(_productId, IRSWAP)
{
  fixedLegDayCountConvention =_fixedLegDayCountConvention;
  floatingLegDayCountConvention =_floatingLegDayCountConvention;
  fixedLegPaymentFrequency =_fixedLegPaymentFrequency;
  floatingIndex =_floatingIndex;
  floatingIndexTenor =_floatingIndexTenor;
  effectiveDate =_effectiveDate;
  terminationDate =_terminationDate;
  currency =_currency;
  termYears = _termYears;
  swapType =_swapType;
  swapLegType = _swapLegType;
}

IRSwap::IRSwap() : Product(0, IRSWAP)
{
}

DayCountConvention IRSwap::GetFixedLegDayCountConvention() const
{
  return fixedLegDayCountConvention;
}

DayCountConvention IRSwap::GetFloatingLegDayCountConvention() const
{
  return floatingLegDayCountConvention;
}

PaymentFrequency IRSwap::GetFixedLegPaymentFrequency() const
{
  return fixedLegPaymentFrequency;
}

FloatingIndex IRSwap::GetFloatingIndex() const
{
  return floatingIndex;
}

FloatingIndexTenor IRSwap::GetFloatingIndexTenor() const
{
  return floatingIndexTenor;
}

date IRSwap::GetEffectiveDate() const
{
  return effectiveDate;
}

date IRSwap::GetTerminationDate() const
{
  return terminationDate;
}

Currency IRSwap::GetCurrency() const
{
  return currency;
}

int IRSwap::GetTermYears() const
{
  return termYears;
}

SwapType IRSwap::GetSwapType() const
{
  return swapType;
}

SwapLegType IRSwap::GetSwapLegType() const
{
  return swapLegType;
}


ostream& operator<<(ostream &output, const IRSwap &swap)
{
  output << "fixedDayCount:" << swap.ToString(swap.GetFixedLegDayCountConvention()) << " floatingDayCount:" << swap.ToString(swap.GetFloatingLegDayCountConvention()) << " paymentFreq:" << swap.ToString(swap.GetFixedLegPaymentFrequency()) << " " << swap.ToString(swap.GetFloatingIndexTenor()) << swap.ToString(swap.GetFloatingIndex()) << " effective:" << swap.GetEffectiveDate() << " termination:" << swap.GetTerminationDate() << " " << swap.ToString(swap.GetCurrency()) << " " << swap.GetTermYears() << "yrs " << swap.ToString(swap.GetSwapType()) << " " << swap.ToString(swap.GetSwapLegType());
  return output;
}

string IRSwap::ToString(DayCountConvention dayCountConvention) const
{
  switch (dayCountConvention) {
  case THIRTY_THREE_SIXTY: return "30/360";
  case ACT_THREE_SIXTY: return "Act/360";
  default: return "";
  }
}

string IRSwap::ToString(PaymentFrequency paymentFrequency) const
{
  switch (paymentFrequency) {
  case QUARTERLY: return "Quarterly";
  case SEMI_ANNUAL: return "Semi-Annual";
  case ANNUAL: return "Annual";
  default: return "";
  }
}

string IRSwap::ToString(FloatingIndex floatingIndex) const
{
  switch (floatingIndex) {
  case LIBOR: return "LIBOR";
  case EURIBOR: return "EURIBOR";
  default: return "";
  }
}

string IRSwap::ToString(FloatingIndexTenor floatingIndexTenor) const
{ 
  switch(floatingIndexTenor) {
  case TENOR_1M: return "1m";
  case TENOR_3M: return "3m";
  case TENOR_6M: return "6m";
  case TENOR_12M: return "12m";
  default: return "";
  }
}

string IRSwap::ToString(Currency currency) const
{ 
  switch(currency) {
  case USD: return "USD";
  case EUR: return "EUR";
  case GBP: return "GBP";
  default: return "";
  }
}

string IRSwap::ToString(SwapType swapType) const
{ 
  switch(swapType) {
  case SPOT: return "Standard";
  case FORWARD: return "Forward";
  case IMM: return "IMM";
  case MAC: return "MAC";
  case BASIS: return "Basis";
  default: return "";
  }
}

string IRSwap::ToString(SwapLegType swapLegType) const
{ 
  switch(swapLegType) {
  case OUTRIGHT: return "Outright";
  case CURVE: return "Curve";
  case FLY: return "Fly";
  default: return "";
  }
}

#endif
