/*
 * Copyright (C) 2018 by Rodrigo Antonio de Araujo
 *
 */

#include <cstdio>
#include <memory>
#include <boost/thread.hpp>
#include <boost/date_time.hpp>
#include <apiclient/apiclient.h>


int main(int argc, char** argv) {
    auto api_builder = apiclient::builder(4);

    auto api_client = api_builder->client("https://httpbin.org");

    bool finished = false;

    printf("Invoking get method\n");
    api_client->get("/get?test=134", [&finished] (
        const apiclient::Response& r
    ) {
        printf("Parsing the response\n");
        if (r.has_error()) {
            printf("Has error! %d\n", r.get_error());
        } else {
            Json::StyledWriter jw;
            auto s = jw.write(r.get_body());
            printf("Status code: %d\n", r.get_status());
            printf("Raw: %s\n", r.get_data().c_str());
            printf("Json: %s\n", s.c_str());
            printf("response headers: \n");
            for (auto it = r.get_headers().begin();
                    it != r.get_headers().end(); it++) {
                printf("%s: %s\n", it->first.c_str(), it->second.c_str());
            }
        }
        finished = true;
    });

    printf("[main thread] Waiting\n");

    while (!finished) {
        boost::this_thread::sleep(boost::posix_time::milliseconds(1));
    }

    return 0;
}
