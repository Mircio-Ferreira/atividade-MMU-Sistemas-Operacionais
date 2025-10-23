#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>  // for system()

#define LENGTH 4

// helps me know which one to use on the clear function
#ifdef _WIN32
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif

struct process {
    char key;
    int n_appears;
    int pos_enter;
};
typedef struct process process;

bool is_full(process pros[]);
bool check_occur(process new_process, process pros[], int **pIndex);
int remove_item(process pros[]);
int index_free(process pros[]);
void print_processes(process pros[]);;
process new(char key);
void clear_console();
void wait_enter();

// global variable (i know it's bad practice but sorry)
int curr_pos = 0;

int main() {
    process pros[LENGTH] = {0};
    bool is_running = true;

    while (is_running) {
        clear_console();  // clear before showing the menu
        printf("LFU Visualizer\n");
        printf("\n1 - Add new process\n");
        printf("2 - Quit\n");
        printf("3 - Print Table\n");

        int menu_input;
        scanf("%d", &menu_input);

        switch (menu_input) {
            case 1: {
                clear_console();
                printf("\nSelected Add new process\n");
                printf("Please populate the new process with key\n");

                char new_key;
                scanf(" %c", &new_key); 

                process new_process = new(new_key); // constructor
                int index = 0;
                int *pIndex = &index;

                if (is_full(pros)) {
                    if (check_occur(new_process, pros, &pIndex)) {
                        pros[index].n_appears++;
                    } else {
                        new_process.n_appears = 1;
                        pros[remove_item(pros)] = new_process; // LFU eviction
                    }
                } else {
                    if (check_occur(new_process, pros, &pIndex)) {
                        pros[index].n_appears++;
                    } else {
                        new_process.n_appears = 1;
                        pros[index_free(pros)] = new_process;
                    }
                }

                printf("\nUpdated table:\n");
                print_processes(pros);
                wait_enter();
                break;
            }
            case 2: { 
                clear_console();
                printf("\nSelected Quit\n");
                printf("Farewell! 👋\n");
                is_running = false;
                break; 
            }
            case 3: {
                clear_console();
                printf("Current table:\n");
                print_processes(pros);
                wait_enter();
                break;
            }
            default: {
                printf("Please select one of the options above\n");
                wait_enter();
            }
        }
    }   
}

bool is_full(process pros[]) {
    for (int i = 0; i < LENGTH; i++) {
        if (pros[i].key == '\0') return false;
    }
    return true;
}

bool check_occur(process new_process, process pros[], int **pIndex) {
    for (int i = 0; i < LENGTH; i++) {
        if (pros[i].key == new_process.key) { **pIndex = i; return true; }
    }
    return false;
}

// return index to remove on main
int remove_item(process pros[]) {
    int victim = 0;
    int min_freq = pros[0].n_appears;
    int oldest_pos = pros[0].pos_enter;

    for (int i = 1; i < LENGTH; ++i) {
        if (pros[i].n_appears < min_freq ||
           (pros[i].n_appears == min_freq && pros[i].pos_enter < oldest_pos)) {
            victim = i;
            min_freq = pros[i].n_appears;
            oldest_pos = pros[i].pos_enter;
        }
    }
    return victim;
}

// return index free from pros array 
int index_free(process pros[]) {
    int index = 0;

    for (int i = 0; i < LENGTH; i++) {
        if (pros[i].key == '\0') return index;
        index++;
    }
    return index;
}

void print_processes(process pros[]) {
    printf("\n=== Current Processes ===\n");
    printf("%-10s %-12s %-10s\n", "Key", "n_appears", "pos_enter");
    printf("-------------------------------\n");

    for (int i = 0; i < LENGTH; i++) {
        if (pros[i].key == '\0')
            printf("%-10s %-12s %-10s\n", "-", "-", "-");
        else
            printf("%-10c %-12d %-10d\n", pros[i].key, pros[i].n_appears, pros[i].pos_enter);
    }
}

process new(char key) {
    process new_process;
    new_process.key = key;
    new_process.n_appears = 0; // initial value
    new_process.pos_enter = curr_pos;
    curr_pos++;
    return new_process;
}

void clear_console() {
    system(CLEAR);
}

void wait_enter() {
    printf("\nPress Enter to return to menu...");
    // consume leftover newline from previous scanf
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
    // wait for user Enter
    getchar();
}

