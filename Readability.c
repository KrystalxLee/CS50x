#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int main(void)
{
    float level;
    float letters= 0;
    float sentences = 0;
    float words = 1;
    float L;
    float S;

    string text = get_string("Text: ");
    int length = strlen(text);

    for (int i=0; i<length; i++){
        //Count the number of letters
        if ((text[i]>='a' && text[i] <= 'z') || (text[i] >= 'A' && text[i] <= 'Z')){
            letters = letters + 1;
        }
        //Count the number of sentences (. ! ?)
        else if (text[i] =='.' || text[i] == '!' || text[i] == '?'){
            sentences = sentences + 1;
        }
        //Count the number of words
        else if (text[i] == ' ') {
            words = words + 1;
        }
    }

    L = letters / words * 100;
    S = sentences / words * 100;

    level = 0.0588 * L - 0.296 * S - 15.8;
    //Check to make sure calculations are working correctly 
    //printf("%f, %f, %f\n", letters, sentences, words);
    //printf("%f, %f\n", L, S);
    //printf("%f\n", level);

    if (level < 0){
        printf("Before Grade 1\n");
    }
    else if (level > 0 && level < 16) {
        printf("Grade %.0f\n", round(level));
    }
    else {
        printf("Grade 16+\n");
    }

}
