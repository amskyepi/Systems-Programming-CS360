/*int main(int argc, char **argv){
    if(argc < 2){
        printf("Error -- please specify a text file\n");
        exit(0);
    }
    int c = 0, i = 0, wordCount = 0;
    char buffer[100];
    char * array[1000000];
    FILE * fp = fopen(argv[1], "r");
    while ((c = fgetc(fp)) != EOF && wordCount != 1000000) {
        switch (c) {
            case ' ': case '\n': case '.':
                if (0 == i) break;
                buffer[i] = '\0';
                array[wordCount] = malloc(strlen(buffer));
                strcpy(array[wordCount], buffer);
                i = 0;
                wordCount++;
                break;
            default:
                buffer[i] = c;
                i++;
        }
    }
    //for (int i = 0; i < wordCount; i++) printf("%s\n", array[i]);
    double startTime = 0, endTime = 0;
    setSortThreads(12);
    startTime = clock();
    sortThreaded(array, wordCount);
    endTime = clock();
    //for (int i = 0; i < wordCount; i++) printf("%s\n", array[i]);
    printf("%lfms\n", ((endTime - startTime) / CLOCKS_PER_SEC) * 1000);
    return 0;
}*/
