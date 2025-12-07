#include <stdio.h>

int main() {
    FILE *fp;
    char buff[200];

    fp = fopen("catatan.txt", "w");
    fputs("Data awal disimpan.\n", fp);
    fclose(fp);

    fp = fopen("catatan.txt", "a");
    fputs("Data ini ditambahkan.\n", fp);
    fclose(fp);

    fp = fopen("catatan.txt", "r");
    while (fgets(buff, 200, fp)) {
        printf("%s", buff);
    }
    fclose(fp);

    return 0;
}
