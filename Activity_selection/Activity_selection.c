#include <stdio.h>

struct Activity {
    int start;
    int finish;
};

void sortActivities(struct Activity arr[], int n) {
    int i, j;
    struct Activity temp;
    
    for (i = 0; i < n-1; i++) {
        for (j = i+1; j < n; j++) {
            if (arr[j].finish < arr[i].finish) {
                temp = arr[j];
                arr[j] = arr[i];
                arr[i] = temp;
            }
        }
    }
}

void activitySelection(int start[], int finish[], int n) {
    struct Activity activities[n];
    
    // Initialize activities array
    for (int i = 0; i < n; i++) {
        activities[i].start = start[i];
        activities[i].finish = finish[i];
    }
    
    // Sort activities by finish time
    sortActivities(activities, n);
    
    printf("\nSelected Activities:\n");
    
    // Select first activity
    int i = 0;
    printf("Activity with start time: %d, finish time: %d\n", 
           activities[i].start, activities[i].finish);
    
    // Consider rest of the activities
    for (int j = 1; j < n; j++) {
        if (activities[j].start >= activities[i].finish) {
            printf("Activity with start time: %d, finish time: %d\n", 
                   activities[j].start, activities[j].finish);
            i = j;
        }
    }
}

int main() {
    int start[] = {5, 1, 3, 0, 5, 8};
    int finish[] = {9, 2, 4, 6, 7, 9};
    int n = sizeof(start)/sizeof(start[0]);
    
    printf("Activities:\n");
    printf("Start times: ");
    for(int i = 0; i < n; i++) printf("%d ", start[i]);
    printf("\nFinish times: ");
    for(int i = 0; i < n; i++) printf("%d ", finish[i]);
    printf("\n");
    
    activitySelection(start, finish, n);
    
    return 0;
}
