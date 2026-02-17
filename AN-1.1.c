#include <stdio.h>

int main() {
    int grades[3];  // 3 notas
    int average;
    float frequency;
    int absences, total_classes = 60;
    
    printf("=== Evaluation System ===\n\n");
    
    // Coletar notas
    for (int i = 0; i < 3; i++) {
        printf("Enter Grade %d: ", i + 1);
        scanf("%d", &grades[i]);
        
        while (grades[i] < 0 || grades[i] > 100) {
            printf("Invalid grade! Please enter a grade between 0 and 100: ");
            scanf("%d", &grades[i]);
        }
    }
    
    // Coletar faltas
    printf("\nEnter the number of absences: ");
    scanf("%d", &absences);
    
    // Mostrar notas
    printf("\n=== GRADES ===\n");
    for (int i = 0; i < 3; i++) {
        printf("Grade %d: %d\n", i + 1, grades[i]);
    }
    
    // Calcular média
    average = (grades[0] + grades[1] + grades[2]) / 3;
    frequency = ((float)(total_classes - absences) / total_classes) * 100;
    
    // Mostrar resultados
    printf("\n=== RESULTS ===\n");
    printf("Average: %d\n", average);
    printf("Frequency: %.1f%%\n", frequency);
    printf("Absences: %d\n", absences);
    
    // Verificar aprovação
    if (frequency < 75) {
        printf("\nSituation: FAILED DUE TO LOW FREQUENCY\n");
    } else if (average >= 70) {
        printf("\nSituation: APPROVED\n");
    } else if (average >= 50) {
        printf("\nSituation: IN RECOVERY\n");
    } else {
        printf("\nSituation: FAILED DUE TO LOW GRADE\n");
    }
    
    return 0;
}
