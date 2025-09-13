#include <stdio.h>

#define SIZE 9

int sudoku[SIZE][SIZE];

// Vérifie si un chiffre peut être placé
int estValide(int ligne, int colonne, int val) {
    for(int i = 0; i < SIZE; i++) {
        if(sudoku[ligne][i] == val) return 0; // même ligne
        if(sudoku[i][colonne] == val) return 0; // même colonne
    }
    int startL = (ligne/3)*3;
    int startC = (colonne/3)*3;
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            if(sudoku[startL+i][startC+j] == val) return 0; // même carré
    return 1;
}

// Backtracking pour résoudre le Sudoku
int resoudreSudoku() {
    for(int ligne = 0; ligne < SIZE; ligne++) {
        for(int colonne = 0; colonne < SIZE; colonne++) {
            if(sudoku[ligne][colonne] == 0) {
                for(int val = 1; val <= 9; val++) {
                    if(estValide(ligne, colonne, val)) {
                        sudoku[ligne][colonne] = val;
                        if(resoudreSudoku()) return 1;
                        sudoku[ligne][colonne] = 0;
                    }
                }
                return 0; // aucun chiffre ne fonctionne
            }
        }
    }
    return 1; // Sudoku complet
}

// Affichage amélioré de la grille
void afficherSudoku() {
    for(int i = 0; i < SIZE; i++) {
        if(i % 3 == 0 && i != 0)
            printf("------+-------+------\n"); // ligne horizontale
        for(int j = 0; j < SIZE; j++) {
            if(j % 3 == 0 && j != 0)
                printf("| "); // ligne verticale
            printf("%d ", sudoku[i][j]);
        }
        printf("\n");
    }
}

int main() {
    char ligne[20];

    printf("Entrez votre grille de Sudoku ligne par ligne (9 chiffres par ligne, 0 pour vide) :\n");

    for(int i = 0; i < SIZE; i++) {
        printf("Ligne %d : ", i+1);
        scanf("%s", ligne); // lire une ligne entière

        for(int j = 0; j < SIZE; j++) {
            if(ligne[j] >= '0' && ligne[j] <= '9') {
                sudoku[i][j] = ligne[j] - '0';
            } else {
                printf("Caractère invalide, mettez 0 pour vide.\n");
                sudoku[i][j] = 0;
            }
        }
    }

    printf("\nSudoku incomplet saisi :\n");
    afficherSudoku();

    if(resoudreSudoku()) {
        printf("\nSudoku résolu :\n");
        afficherSudoku();
    } else {
        printf("\nAucune solution possible pour cette grille !\n");
    }

    return 0;
}
