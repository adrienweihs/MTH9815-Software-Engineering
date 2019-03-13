/**
 * test program for our ProductServices
 */

#include <iostream>
#include "products.hpp"
#include "productservice.hpp"


using namespace std;

int main() {
	// Create the 10Y treasury note
	date maturityDate(2025, Nov, 16);
	string cusip = "912828M56";
	Bond treasuryBond(cusip, CUSIP, "T", 2.25, maturityDate);

	// Create the 2Y treasury note
	date maturityDate2(2017, Nov, 5);
	string cusip2 = "912828TW0";
	Bond treasuryBond2(cusip2, CUSIP, "T", 0.75, maturityDate2);

	// Create a BondProductService
	BondProductService *bondProductService = new BondProductService();

	// Add the 10Y note to the BondProductService and retrieve it from the service
	bondProductService->Add(treasuryBond);
	Bond bond = bondProductService->GetData(cusip);
	cout << "CUSIP: " << bond.GetProductId() << " ==> " << bond << endl;

	// Add the 2Y note to the BondProductService and retrieve it from the service
	bondProductService->Add(treasuryBond2);
	bond = bondProductService->GetData(cusip2);
	cout << "CUSIP: " << bond.GetProductId() << " ==> " << bond << endl;
	
	// test GetBonds
	cout<<endl<<"GetBonds(\"T\")"<<endl;
	string s="T";
	auto bonds=bondProductService->GetBonds(s);
	for(auto& item:bonds){
		cout<<item<<endl;
	}
	cout<<endl;





	// Create the Spot 10Y Outright Swap
	date effectiveDate(2015, Nov, 16);
	date terminationDate(2025, Nov, 16);
	string outright10Y = "Spot-Outright-10Y";
	IRSwap outright10YSwap(outright10Y, THIRTY_THREE_SIXTY, THIRTY_THREE_SIXTY, SEMI_ANNUAL, LIBOR, TENOR_3M, effectiveDate, terminationDate, USD, 10, SPOT, OUTRIGHT);

	// Create the IMM 2Y Outright Swap
	date effectiveDate2(2015, Dec, 20);
	date terminationDate2(2017, Dec, 20);
	string imm2Y = "IMM-Outright-2Y";
	IRSwap imm2YSwap(imm2Y, THIRTY_THREE_SIXTY, THIRTY_THREE_SIXTY, SEMI_ANNUAL, LIBOR, TENOR_3M, effectiveDate2, terminationDate2, USD, 2, IMM, OUTRIGHT);

	// Create a IRSwapProductService
	IRSwapProductService *swapProductService = new IRSwapProductService();

	// Add the Spot 10Y Outright Swap to the IRSwapProductService and retrieve it from the service
	swapProductService->Add(outright10YSwap);
	IRSwap swap = swapProductService->GetData(outright10Y);
	cout << "Swap: " << swap.GetProductId() << " == > " << swap << endl;

	// Add the IMM 2Y Outright Swap to the IRSwapProductService and retrieve it from the service
	swapProductService->Add(imm2YSwap);
	swap = swapProductService->GetData(imm2Y);
	cout << "Swap: " << swap.GetProductId() << " == > " << swap << endl;


	
	// test GetSwaps
	cout<<endl<<"GetSwaps(THIRTY_THREE_SIXTY)"<<endl;
	auto swaps=swapProductService->GetSwaps(THIRTY_THREE_SIXTY);
	for(auto& item:swaps){
		cout<<item<<endl;
	}
	cout<<endl;
	
	cout<<endl<<"GetSwaps(SEMI_ANNUAL)"<<endl;
	swaps=swapProductService->GetSwaps(SEMI_ANNUAL);
	for(auto& item:swaps){
		cout<<item<<endl;
	}
	cout<<endl;
	
	cout<<endl<<"GetSwaps(LIBOR)"<<endl;
	swaps=swapProductService->GetSwaps(LIBOR);
	for(auto& item:swaps){
		cout<<item<<endl;
	}
	cout<<endl;
	
	cout<<endl<<"GetSwapsGreaterThan(1)"<<endl;
	swaps=swapProductService->GetSwapsGreaterThan(1);
	for(auto& item:swaps){
		cout<<item<<endl;
	}
	cout<<endl;

	return 0;
}
