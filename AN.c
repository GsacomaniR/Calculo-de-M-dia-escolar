#include <stdio.h>
#include <stdlib.h>

#define MAX_GRADE 16

int main(void) {
        float grades[MAX_GRADE];
        int amount;
        float sum = 0, average;

        printf("What's you grade? (Max %d) ", MAX_GRADE);
        scanf("%d", &amount);

        if (amount < 0 || amount > MAX_GRADE) {
                printf("Invalid amount of grades! Use a value between 0 and %d.\n", MAX_GRADE);
                return 1;
        }

        for (int i = 0; i < amount; i++){
            printf("Typed grade %d: ", i + 1);
            scanf("%f", &grades[i]);

            while (grades[i] < 0 || grades[i] > 100) {
                printf("Invalid grade! Use a value between 0 and 100.\n");
                scanf("%f", &grades[i]);
            }
            sum += grades[i];
        }
    
        printf("\n=== TYPED GRADES ===\n");
        for (int i = 0; i < amount; i++) {
            printf("Grade %d: %.2f\n", i + 1, grades[i]);
        }

        average = sum / amount;
        printf("\n=== RESULTS ===\n");
        printf("average: %.2f\n", average);

        if (average >= 51) {
            printf("Status: Approved\n");
        } else if (average >= 50) {
            printf("Status: Recovery\n");
        } else {
            printf("Status: Reproved\n");
        }
        return 0;
}
