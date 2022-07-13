#include <iostream>
#include <string>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

string getFreeAtsign(const string &apiKey, const string &registrarUrl);

void registerAtsign(const string &apiKey, const string &atsign);

string getCramKey(const string &apiKey, const string &atsign, const string &email, const string &otp);

int main() {
    string email = "email";
    string registrarUrl = "https://my.atsign.wtf/api/app/v2/get-free-atsign";
    string apiKey = "477b-876u-bcez-c42z-6a3d";
    string otp;
    string newAtsign;
    string rootHost = "root.atsign.wtf";
    string port = "64";

    // Get free atSign
    string atsign = getFreeAtsign(apiKey, registrarUrl);

    // Register atSign
    registerAtsign(apiKey, atsign);

    cout << "Enter OTP received on" + email + ": " << endl;
    cin >> otp;

    // get cram key
    string cram = getCramKey(apiKey, atsign, email, otp);
    cout << "cram key: " << cram << endl;

    // cram contains @sign:secret, parse out the secret
    string secret = cram.substr(cram.find_first_of(":") + 1);
    cout << "cram secret: " << secret << endl;

    return 0;
}


string getCramKey(const string &apiKey, const string &atsign, const string &email, const string &otp) {
    cpr::Response r1 = cpr::Post(cpr::Url{"https://my.atsign.wtf/api/app/v2/validate-person"},
                                 cpr::Body{"{ \"atsign\": \"" + atsign +
                                           "\", \"email\": \"f20200387@hyderabad.bits-pilani.ac.in\", \"otp\": \"" +
                                           otp + "\", \"confirmation\": true }"},
                                 cpr::Header{{"Authorization", apiKey},
                                             {"Content-Type",  "application/json"}});
    cout << r1.text << endl;
    json j1 = json::parse(r1.text);
    string cramkey = j1["cramkey"].get<string>();
    cout << "cramkey is :" << cramkey << endl;
    return cramkey;
}

void registerAtsign(const string &apiKey, const string &atsign) {
    cpr::Response r1 = cpr::Post(cpr::Url{"https://my.atsign.wtf/api/app/v2/register-person"},
                                 cpr::Body{"{ \"atsign\": \"" + atsign +
                                           "\", \"email\": \"f20200387@hyderabad.bits-pilani.ac.in\" }"},
                                 cpr::Header{{"Authorization", apiKey},
                                             {"Content-Type",  "application/json"}});
    cout << r1.text << endl;
}

string getFreeAtsign(const string &apiKey, const string &registrarUrl) {
    cpr::Response r = cpr::Get(cpr::Url{registrarUrl},
                               cpr::Header{{"Authorization", apiKey}});
    cout << r.url << endl;
    cout << r.status_code << endl;
    cout << r.header["content-type"] << endl;
    cout << r.text << endl;
    json j = json::parse(r.text);
    auto atsign_string = j["data"]["atsign"].get<string>();
    cout << "Your free atsign is : " << atsign_string << endl;
    return atsign_string;
}
