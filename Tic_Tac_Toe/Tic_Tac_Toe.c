#include <stdio.h>
#include <windows.h>
#include <stdlib.h>

char square[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

int checkRow()
{
    for (int i = 1; i <= 7; i += 3)
    {
        if ((square[i] == square[i + 1]) && (square[i + 1] == square[i + 2]))
        {
            return 1;
        }
    }
    return 0;
}

int checkColumn()
{
    for (int i = 1; i <= 3; i++)
    {
        if ((square[i] == square[i + 3]) && (square[i + 3] == square[i + 6]))
        {
            return 1;
        }
    }
    return 0;
}

int checkDiag()
{
    if ((square[1] == square[5]) && (square[5] == square[9]))
    {
        return 1;
    }
    else if ((square[3] == square[5]) && (square[5] == square[7]))
    {
        return 1;
    }
    return 0;
}

int checkWin()
{
    int i = checkRow();
    int j = checkColumn();
    int k = checkDiag();
    if (i || j || k)
    {
        return 1;
    }
    return 0;
}

void putMark(int player, int choice)
{
    square[choice] = (player == 1) ? 'X' : 'O';
}

void drawBoard()
{
    printf("       TIC TAC TOE\n");
    printf("Player 1(X)\tPlayer 2(O)\n\n");
    printf("    %c  |   %c  |   %c\n", square[1], square[2], square[3]);
    printf("-----------------------\n");
    printf("    %c  |   %c  |   %c\n", square[4], square[5], square[6]);
    printf("-----------------------\n");
    printf("    %c  |   %c  |   %c\n", square[7], square[8], square[9]);
}

int main()
{
    //system("color 4a");
    int choice, player = 1, win = 0, moves = 0;
    ;
    while (1)
    {
        system("cls");
        drawBoard();
        printf("\n\nPlayer %d choice: ", player);
        scanf("%d", &choice);
        if (choice > 9 || choice < 1 || square[choice] == 'X' || square[choice] == 'O')
        {
            printf("Invalid choice!!!\n");
            continue;
        }
        putMark(player, choice);
        moves++;
        system("cls");
        drawBoard();
        win = checkWin();
        if (win)
        {
            printf("\n\nPlayer %d Wins!!!\n", player);
            break;
        }
        if (moves == 9)
        {
            printf("DRAW!!!\n");
            break;
        }
        player = (player == 1) ? 2 : 1;
    }

    return 0;
}
