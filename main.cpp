#include <iostream>


#include <string>

#include <cpprest/http_client.h>
#include <cpprest/filestream.h>

using namespace utility;                    // Common utilities like string conversions
using namespace web;                        // Common features like URIs.
using namespace web::http;                  // Common HTTP functionality
using namespace web::http::client;          // HTTP client features
using namespace concurrency::streams;       // Asynchronous streams
using namespace std;

int main() {
    cout << "Hello, World!" << endl;
    string email = "email";
    string registrarUrl = "https://my.atsign.wtf/api/app/v2/get-free-atsign";
    string apiKey = "apikey";
    //Get free atSign

    web::http::client::http_client client(U("https://my.atsign.wtf/api/app/v2/get-free-atsign"));

    http_request getFreeAtSign(methods::GET);
    getFreeAtSign.headers().add(L"Authorization", L"apikey");

    pplx::task<web::http::http_response> resp = client.request(getFreeAtSign);

    // Handle response headers arriving.
            resp.then([=](http_response response)
                  {
                      printf("Received response status code:%u\n", response.status_code());

                      stringstreambuf buffer;
                      response.body().read_to_end(buffer).get();

                      //show content in console
                      printf("Response body: \n %s", buffer.collection().c_str());

                      //parse content into a JSON object:
                      json::value jsonvalue = json::value::parse(buffer.collection());

                      //write content to file

                  })
                  .wait();

    return 0;
}
