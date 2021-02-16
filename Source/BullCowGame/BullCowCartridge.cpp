// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    PrintLine(TEXT("Welcome to the BullCow game!"));
    InitGame();
}

void UBullCowCartridge::OnInput(const FString& Input) //When the player hits enter
{
    ClearScreen();
    PrintLine(Input);

    if (Input == this->HiddenWord)  //Won
    {
        PrintLine(TEXT("Thats correct, well done!"));
        //ask to play again
    }
    else                            //Incorrect
    {
        PrintLine(TEXT("Nope, thats not right!"));
        this->Lives --;
        if (this->Lives == 0)       //Lost (No lives)
        {
            PrintLine(TEXT("Out of lives, you lost!"));
            PrintLine(TEXT("The isogram was" + HiddenWord));
        }
        else                        //Lives left
        {
            PrintLine(TEXT("You have " + FString::FromInt(Lives) + " lives left"));
            PrintLine(TEXT("Try again!"));
        }
    }
    
}

void UBullCowCartridge::InitGame()
{
    this->HiddenWord = TEXT("wonderful");
    this->Lives = 5;
    PrintLine(TEXT("Guess the " + FString::FromInt(HiddenWord.Len()) + " letter isogram"));
    PrintLine(TEXT("You have " + FString::FromInt(Lives) + " lives"));
}