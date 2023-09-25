#include <microhttpd.h>
#include <stdio.h>
#include <string.h>

#define JSON "{\"message\": \"Hello, World!\"}";
#define PORT_NUM 22212

static int answer_to_connection(void *cls,
								struct MHD_Connection *connection,
								const char *url,
								const char *method,
								const char *version,
								const char *upload_data,
								size_t *upload_data_size,
								void **con_cls) 
{
    const char *response = JSON;
    struct MHD_Response *http_response;

    http_response = MHD_create_response_from_buffer(
        strlen(response),
        (void *)response,
        MHD_RESPMEM_PERSISTENT
    );

    MHD_add_response_header(http_response, "Content-Type", "application/json");

    int ret = MHD_queue_response(connection, MHD_HTTP_OK, http_response);
    MHD_destroy_response(http_response);

    return ret;
}

int main() {
    const int PORT = PORT_NUM;
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(
        MHD_USE_SELECT_INTERNALLY,
        PORT,
        NULL,
        NULL,
        &answer_to_connection,
        NULL,
        MHD_OPTION_END
    );

    if (daemon == NULL) {
        return 1;
    }

    printf("Server is running on port %d...\n", PORT);
    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}
