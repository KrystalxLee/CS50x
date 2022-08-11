#include <cs50.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{

    bool value = false;

    for (int i=0; i<candidate_count; i++)
    {
        if(strlen(name) == 0){
            return value;
        }
        else if(strcmp(candidates[i].name, name)== 0)
        {
            //update global preferences array to indicate the voter has that candidate as their rank preference
            //preferences[i][j] stores the index of the candidate who is jth ranked preference for ith voter
            preferences[voter][rank] = i;
            value = true;
        }
    }
    return value;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{

    for (int i=0; i<voter_count; i++)
    {
        for (int j=0; j<candidate_count; j++)
        {
            //check if candidate has been eliminated
            //preferences[i][0] is 1st choice, preferences[i][1] is 2nd choice

            if (candidates[preferences[i][j]].eliminated == false)
            {
                //update candidates[i].votes for each preferred candidate
                candidates[preferences[i][j]].votes += 1;
                break;
            }
        }
    }
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    bool value = false;
    string winner;
    float halfVote = voter_count/2;

    //voter_count = total number of votes
    //need more than (voter_count)/2 to win the election

    for (int i=0; i<candidate_count; i++)
    {
        if(candidates[i].votes > halfVote)
        {
            winner = candidates[i].name;
            printf("%s\n", winner);
            value = true;
        }
    }

    return value;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    int smallestVotes = voter_count;

    for (int i=0; i<candidate_count; i++)
    {
        if (candidates[i].eliminated == false && candidates[i].votes <= smallestVotes)
        {
            smallestVotes = candidates[i].votes;
        }
    }

    return smallestVotes;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    bool tie = false;

    for(int i=0; i<candidate_count-2; i++)
    {
        if (candidates[i].votes == min && candidates[i+1].votes == min){
            tie = true;
            return tie;
        }
    }
    return tie;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    for (int i=0; i<candidate_count; i++)
    {
        if(candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
        }
    }

}
