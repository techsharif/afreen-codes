#include<stdio.h>

int main(){

    // 1 1 1 1 1
//    printf("%d ", 1);
//    printf("%d ", 1);
//    printf("%d ", 1);
//    printf("%d ", 1);
//    printf("%d ", 1);

//    int i;
//    for( i=1; i<=5; i=i+1 ){
//        printf("*");
//    }

//    int i;
//    for( i=1; i<=5; i=i+1 ){ // repeat 5 times
//
//        int j;
//        for( j=1; j<=2; j=j+1 ){ // print 2 stars
//            printf("*");
//        }
//
//        printf("\n"); // print a new line
//
//    }


/*

 *
 * *
 * * *
 * * * *

 */
//    int repeat,stars;
//    scanf("%d", &repeat);
//
//    int i;
//    for( i=1; i<=repeat; i=i+1 ){
//
//        int j;
//        stars = i; // repeat, i
//        for( j=1; j<=stars; j=j+1 ){
//            printf("*");
//        }
//
//        printf("\n"); // print a new line
//
//    }


/*

       * // 4, 1 -> 3
     * * // 4, 2 -> 2
   * * * // 4, 3 -> 1
 * * * * // 4, 4 -> 0

 */


    int repeat,stars, space;
    scanf("%d", &repeat);

    int i;
    for( i=1; i<=repeat; i=i+1 ){

        int j;
        space = repeat - i; // repeat, i
        for( j=1; j<=space; j=j+1 ){
            printf(" ");
        }

        int k;
        stars = i; // repeat, i
        for( k=1; k<=stars; k=k+1 ){
            printf("*");
        }

        printf("\n"); // print a new line

    }


    return 0;
}
