// Fill out your copyright notice in the Description page of Project Settings.

#include "RTS_2.h"
#include "CamActor.h"


// Sets default values
ACamActor::ACamActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACamActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACamActor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

