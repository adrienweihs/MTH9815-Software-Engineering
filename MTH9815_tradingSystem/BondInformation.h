/**
 * BondInformation.h
 * defines base informations about bond
 */
#pragma once

#include <vector>
#include <string>

#include "boost/date_time/gregorian/gregorian.hpp"

using namespace std;
using namespace boost::gregorian;


vector<string> bondCusip={"9128285Q9", // 2Years
"9128285L0", // 3Years
"9128285P1", // 5Years
"9128285N6", // 7Years
"9128285M8", // 10Years
"912810SE9"}; // 30Years

vector<float> bondCoupon={0.02836, // 2Years
0.02983, // 3Years
0.02880, // 5Years
0.02974, // 7Years
0.03209, // 10Years
0.03418}; // 30Years

vector<date> bondMaturity={date(2020,Nov,30), // 2Years
date(2021,Nov,15), // 3Years
date(2023,Nov,30), // 5Years
date(2025,Nov,30), // 7Years
date(2028,Nov,15), // 10Years
date(2048,Nov,15)}; // 30Years

map<string,float> bondRisk={{"9128285Q9",0.02}, // 2Years
{"9128285L0",0.03}, // 3Years
{"9128285P1",0.05}, // 5Years
{"9128285N6",0.06}, // 7Years
{"9128285M8",0.09}, // 10Years
{"912810SE9",0.2}}; // 30Years