#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file;
    char *JSON;
    long fileSize;
    
    // 파일 열기
    file = fopen("20230925-20230929_menu.json", "rb");
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

    // JSON 내용 출력
    printf("JSON 파일 내용:\n%s\n", JSON);

    // 할당된 메모리 해제
    free(JSON);

    return 0;
}
