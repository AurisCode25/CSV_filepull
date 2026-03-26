#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_CSV_FILE 260
#define MAX_LINE_SIZE 1024

int main(void) {
    char csv_file[MAX_CSV_FILE]; //Since I want this to be able to open any csv file I havent given it a specific name 
    char line_size[MAX_LINE_SIZE];
    FILE *explorer_exe;
    FILE *file;

    explorer_exe = popen( //Wanted to use a way to use file explorer to select the csv file, to make the program feel more professional
        "powershell -Command \"Add-Type -AssemblyName System.Windows.Forms; " 
        "$dialog = New-Object System.Windows.Forms.OpenFileDialog; "
        "$dialog.Filter = 'CSV files (*.csv)|*.csv|All files (*.*)|*.*'; "
        "if ($dialog.ShowDialog() -eq 'OK') { $dialog.csv_file }\"",
        "r"
    );
    if (!explorer_exe) {
        perror("Couldn't open powershell.");
        return 1;
    }
     if (!fgets(csv_file, sizeof(csv_file), explorer_exe)) {
        printf("No file selected.\n");
        pclose(explorer_exe);
        return 1;
    }
     pclose(explorer_exe);

    csv_file[strcspn(csv_file, "\n")] = '\0';

    if (strlen(csv_file) == 0) {
        printf("No file selected.\n");
        return 1;
    }
    file = fopen(csv_file, "r");
    if (!file) {
        perror("Couldn't open File");
        return 1;
    }
    printf("Contents of %s:\n\n", csv_file);
    while (fgets(line_size, sizeof(line_size), file)) {
        fputs(line_size, stdout);
    }
    fclose(file);
    getchar();
    
    return 0;
}