#include <curl/curl.h>
#include <iostream>
#include <jsoncpp/json/json.h>

size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t totalSize = size * nmemb;
    output->append((char*)contents, totalSize);
    return totalSize;
}

int main() {
    CURL* curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (!curl) {
        std::cerr << "Failed to initialize curl" << std::endl;
        return 1;
    }

    if (curl) {
        // Setze die API-URL
        std::string apiUrl = "https://api.open-meteo.com/v1/forecast?latitude=47.6569&longitude=9.4755&hourly=temperature_2m,wind_speed_10m&timezone=Europe%2FBerlin";
        curl_easy_setopt(curl, CURLOPT_URL, apiUrl.c_str());

        // HTTP-Anfrage durchführen und Antwort in 'response' speichern
        std::string response;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        res = curl_easy_perform(curl);

        if (res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

        // JSON-Daten parsen
        Json::CharReaderBuilder readerBuilder;
        Json::CharReader* reader = readerBuilder.newCharReader();
        Json::Value jsonData;

        Json::String errs;
        bool parsingSuccessful = reader->parse(response.c_str(), response.c_str() + response.size(), &jsonData, &errs);
        delete reader;

        if (!parsingSuccessful) {
            std::cerr << "Failed to parse JSON: " << errs << std::endl;
            return 1;
        }

        // Temperatur aus den JSON-Daten extrahieren
        double temperature = jsonData["hourly"]["temperature_2m"][0].asDouble();
        std::cout << "Aktuelle Temperatur: " << temperature << " Grad Celsius" << std::endl;

        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();

    return 0;
}
