// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    PrintLine(TEXT("Welcome to the BullCow game!"));
    SetupGame();
}


void UBullCowCartridge::OnInput(const FString& Input) //When the player hits enter
{
    if(bGameOver)
    {
        ClearScreen();
        SetupGame();
    }
    else
    {
        ProcessGuess(Input);
    }
}


void UBullCowCartridge::SetupGame()
{
    this->HiddenWord = TEXT("wonderful");
    this->Lives = 5;
    bGameOver = false;
    PrintLine(TEXT("Guess the %i letter isogram"), HiddenWord.Len());
    PrintLine(TEXT("You have %i lives"), Lives);
}


void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("Press enter to play again:"));
}


void UBullCowCartridge::ProcessGuess(FString Guess)
{
    //If they won
    if (Guess == this->HiddenWord)
    {
        PrintLine(TEXT("Thats correct, well done!"));
        EndGame();
        return;
    }
    //If its not the right length
    if (Guess.Len() != this->HiddenWord.Len())
    {
        PrintLine(TEXT("The isogram is %i letters long!"), HiddenWord.Len());
        PrintLine(TEXT("You have %i lives left"), Lives);
        return;
    }
    //Remove a life
    --this->Lives;
    //If theyre out of lives
    if (this->Lives == 0)
    {
        PrintLine(TEXT("Out of lives, you lost!"));
        PrintLine(TEXT("The isogram was '%s'"), *HiddenWord);
        EndGame();
        return;
    }
    //If its not an isogram
    if (!IsIsogram(Guess))
    {
       PrintLine(TEXT("An isogram has no repeating letters!"));
       PrintLine(TEXT("You have %i lives left"), Lives);
       return;
    }
    //Try again
    PrintLine(TEXT("Nope, thats not right!"));
    PrintLine(TEXT("You have %i lives left"), Lives);
    PrintLine(TEXT("Try again!"));
    PrintBullCow(Guess);
}


bool UBullCowCartridge::IsIsogram(FString Word) const
{
    for (size_t i = 0; i < Word.Len()-1; i++)
    {
        for (size_t j = i+1; j < Word.Len(); j++)
        {
            if (Word[i] == Word[j])
            {
                return false;
            }
            
        }
    }
    return true;
}


void UBullCowCartridge::PrintBullCow(FString Comparison) const
{
    FString Hint;
    for (size_t i = 0; i < Comparison.Len(); i++)
    {
        for (size_t j = 0; j < Comparison.Len(); j++)
        {
            if (Comparison[i] == HiddenWord[j])
            {
                if (i == j) //right letter, right place
                {
                    Hint.Append("*");
                    break;
                }
                else        //right letter, wrong place
                {
                    Hint.Append("#");
                    break;
                }
            }
            if (j == Comparison.Len()-1)
            {
                Hint.Append("-");
            }
        }
    }
    Hint.Append("\0");
    PrintLine(TEXT("Guess: %s"), *Comparison);
    PrintLine(TEXT("Hint:  %s"), *Hint); 
}