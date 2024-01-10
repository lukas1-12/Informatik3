#include <stdio.h>
#include <curl/curl.h>
#include "nlohmann/json.hpp"
#include <iostream>

using json = nlohmann::json;

//function to save the response of the http request
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp) {
    userp->append((char*)contents, size * nmemb);
    return size * nmemb;
}

int main(void)
{
    CURL *curl;
    CURLcode result; //variable for return value of a libcurl function  (Fehlercode)
    std::string readBuffer; //Buffer for the received data

    curl = curl_easy_init();
    //test if curl_easy_init worked
    if (curl == NULL) {
        fprintf(stderr, "HTTP request failed\n");
        return -11;
    }
    //Set URL for http request
    curl_easy_setopt(curl, CURLOPT_URL, "https://api.open-meteo.com/v1/forecast?latitude=47.6569&longitude=9.4755&hourly=temperature_2m,wind_speed_10m&timezone=Europe%2FBerlin");
    
    //Set Callback function and saves the data in readBuffer
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);

    //Pointer to readBuffer
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

    //run http request
    result = curl_easy_perform(curl);
    
    if( result != CURLE_OK) {
        fprintf(stderr, "Error: %s\n", curl_easy_strerror(result));
        return -1;
    }

    //end of http request -> cleans the ressources
    curl_easy_cleanup(curl);


    json j = json::parse(readBuffer);


      std::string jsonStr = readBuffer;

    try {
        // parse JSON string in a JSOn object
        json jsonData = json::parse(jsonStr);

        //extract all tempretures
        std::vector<double> temperature = jsonData["hourly"]["temperature_2m"];
        //extract all times
        std::vector<std::string> time = jsonData["hourly"]["time"];

        
        for (size_t i = 0; i < time.size(); ++i) {
            std::cout << "Uhrzeit: " << time[i] << ", Temperatur: " << temperature[i] << " °C" << std::endl;
        
        }
    } catch (const std::exception& e) {
        //in case of failure
        std::cerr << "Fault while parsing JSON: " << e.what() << std::endl;
        return -1;
    }

    return 0;
}