/**
 * FutureProductSrvice.h defines Future ProductService
 */
#include "Future.h"
#include "productservice.hpp"

/**
 * Future Product Service to own reference data over a set of future securities.
 * Key is the productId string, value is a Future.
 */
class FutureProductService : public Service<string,Future> {

public:
	// FutureProductService ctor
	FutureProductService();

	// Return the Future data for a particular Future product identifier
	Future& GetData(string productId);

	// Add a Future to the service (convenience method)
	void Add(Future &future);

private:
	map<string,Future> futureMap; // cache of future products

};

FutureProductService::FutureProductService() {
	futureMap=map<string,Future>();
}

Future& FutureProductService::GetData(string productId) {
	return futureMap[productId];
}

void FutureProductService::Add(Future& future) {
	futureMap.insert(pair<string,Future>(future.GetProductId(), future));
}
