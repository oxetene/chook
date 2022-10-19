#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#define NAME	""
#define AVATAR	""
#define TOKEN	""

struct curl_slist* list = NULL;

void post(CURL* curl, char *data) {
	curl_easy_setopt(curl, CURLOPT_URL, TOKEN);
	curl_easy_setopt(curl, CURLOPT_PROXY, "socks5://127.0.0.1:9050");
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);
	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, list);
	
	curl_easy_perform(curl);
}

int main(void) {
	CURL* curl = curl_easy_init();
	list = curl_slist_append(list, "content-type: application/json");
	char buffer[2000], *message;

    if (curl) {
		while (1) {	
			printf("> ");
			fgets(buffer, 2000, stdin);
			buffer[strlen(buffer) - 1] = '\0';
			asprintf(&message, "{\"content\": \"%s\", \"username\": \""NAME"\", \"avatar_url\": \""AVATAR"\"}", buffer);
			post(curl, message);
		}
	}
    curl_easy_cleanup(curl);
    curl_slist_free_all(list);
	free(message);

    return 0;
}
