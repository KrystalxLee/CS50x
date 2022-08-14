#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    bool voteValue = false;

    for (int i =0; i<candidate_count; i++)
    {
        //if invalid entry
        if(strlen(name)==0)
        {
            voteValue = false;
            return voteValue;
        }
        else if (strcmp(candidates[i], name)==0)
        {
            ranks[rank] = i;
            voteValue = true;
        }
    }
    return voteValue;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    //number of voters who prefer candidate i over candidate j
    for(int i=0; i<candidate_count; i++)
    {
        for(int j=i+1; j<candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]] +=1;
        }
    }

}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i=0; i<pair_count; i++)
    {
        for (int j=i+1; j<pair_count; j++)
        {
            if (preferences[i][j] > preferences[j][i]) //more voters prefer candidate i
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count += 1;
            }
            else if (preferences[i][j] < preferences[j][i]) //more voters prefer candidate j
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count += 1;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    //use bubble sort to sort the array
    //sort by biggest numbers first
    for (int i = pair_count-1; i>=0; i--)
    {
        for(int j=0; j<=i; j++)
        {
            if((preferences[pairs[j].winner][pairs[j].loser])<(preferences[pairs[j+1].winner][pairs[j+1].loser]))
            {
                pair temp = pairs[j];
                pairs[j] = pairs[j+1];
                pairs[j+1] = temp;
            }
        }
    }


}


bool cycle(int end, int cycle_start)
{
    // Return True if there is a cycle created (recursion base case)
    if (end == cycle_start)
    {
        return true;
    }
    // Loop through candidates
    for (int i = 0; i < candidate_count; i++)
    {
        if(locked[end][i])
        {
            if(cycle(i, cycle_start))
            {
                return true;
            }
        }
    }
    return false;
}


// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    //loop through the pairs
    for(int i=0; i<pair_count; i++)
    {
        //if cycle returns false, lock the pair
        if(!cycle(pairs[i].loser, pairs[i].winner))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    int count;
    int winner; //index of the winning candidate

    for (int i=0; i<candidate_count; i++)
    {
        count =0;
        for (int j=0; j<candidate_count; j++)
        {
            if(locked[j][i] == false)
            {
                count +=1;
                winner = i; //the nested for loop will go through to check all of the pairs, and represent the index of the winning candidate index 
            }
        }
    }

    if (count == candidate_count)
    {
        printf("%s\n", candidates[winner]);
    }

}
