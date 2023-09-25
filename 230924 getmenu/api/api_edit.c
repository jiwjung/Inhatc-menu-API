#include <microhttpd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PORT_NUM 22212

char *JSON;

int readFile() {
    FILE *file;
    long fileSize;
    
    // 파일 열기
    file = fopen("inhatc_menu.json", "rb");
    if (!file) {
        printf("파일을 열 수 없습니다.\n");
        return 1;
    }

    // 파일 크기 구하기
    fseek(file, 0, SEEK_END);
    fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    // 파일 내용 읽기
    JSON = (char *)malloc(fileSize + 1); // 문자열 끝을 나타내는 NULL 문자를 위해 +1 할당
    if (!JSON) {
        fclose(file);
        printf("메모리를 할당할 수 없습니다.\n");
        return 1;
    }

    fread(JSON, 1, fileSize, file);
    JSON[fileSize] = '\0'; // 문자열 끝에 NULL 문자 추가

    // 파일 닫기
    fclose(file);

    // 할당된 메모리 해제
    free(JSON);

    return 0;
}

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
	
	readFile();

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

    printf("\n[ INFO ] 인하공전 학식 API 서버가 시작되었습니다. (PORT : %d)\n\n[ INFO ] 서버를 종료하시려면, 'exit'를 입력하세요.\n", PORT);
    char temp[16];
	while(1) {
		scanf("%s", temp);
		if(strcmp(temp, "exit") == 0) {
			printf("[ INFO ] 인하공전 학식 API 서버를 종료합니다.\n\n");
			break;
		}
		else printf("[ ! ] 서버를 종료하시려면, 'exit'를 입력하세요.\n");
	}

    MHD_stop_daemon(daemon);
    return 0;
}
