#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 100
#define FILE_NAME "users.txt"

// Function declarations
void registerUser();
void loginUser();
void clearInputBuffer();

int main() {
    int choice;

    while (1) {
        printf("\n============================\n");
        printf("  Terminal Website System\n");
        printf("============================\n");
        printf("1. Register\n");
        printf("2. Login\n");
        printf("3. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);
        clearInputBuffer();

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                loginUser();
                break;
            case 3:
                printf("Thanks for visiting. Goodbye!\n");
                return 0;
            default:
                printf("Invalid option. Try again.\n");
        }
    }

    return 0;
}

void registerUser() {
    char *name = (char*) malloc(MAX_LEN);
    char *email = (char*) malloc(MAX_LEN);
    char *password = (char*) malloc(MAX_LEN);

    if (!name || !email || !password) {
        printf("Memory allocation failed!\n");
        return;
    }

    printf("\n--- Register New User ---\n");
    printf("Name: ");
    fgets(name, MAX_LEN, stdin);
    name[strcspn(name, "\n")] = 0;

    printf("Email: ");
    fgets(email, MAX_LEN, stdin);
    email[strcspn(email, "\n")] = 0;

    printf("Password: ");
    fgets(password, MAX_LEN, stdin);
    password[strcspn(password, "\n")] = 0;

    // Save to file
    FILE *file = fopen(FILE_NAME, "a");
    if (file == NULL) {
        printf("Error opening file!\n");
    } else {
        fprintf(file, "%s|%s|%s\n", email, password, name);  // Format: email|password|name
        fclose(file);
        printf("Registration successful!\n");
    }

    free(name);
    free(email);
    free(password);
}

void loginUser() {
    char *email = (char*) malloc(MAX_LEN);
    char *password = (char*) malloc(MAX_LEN);
    char line[300];
    int found = 0;

    if (!email || !password) {
        printf("Memory allocation failed!\n");
        return;
    }

    printf("\n--- Login ---\n");
    printf("Email: ");
    fgets(email, MAX_LEN, stdin);
    email[strcspn(email, "\n")] = 0;

    printf("Password: ");
    fgets(password, MAX_LEN, stdin);
    password[strcspn(password, "\n")] = 0;

    FILE *file = fopen(FILE_NAME, "r");
    if (file == NULL) {
        printf("No users registered yet!\n");
        return;
    }

    while (fgets(line, sizeof(line), file)) {
        char *file_email = strtok(line, "|");
        char *file_password = strtok(NULL, "|");
        char *file_name = strtok(NULL, "\n");

        if (file_email && file_password && strcmp(email, file_email) == 0 && strcmp(password, file_password) == 0) {
            printf("Welcome back, %s!\n", file_name);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Login failed! Invalid email or password.\n");
    }

    fclose(file);
    free(email);
    free(password);
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

