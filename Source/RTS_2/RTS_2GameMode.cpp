// Fill out your copyright notice in the Description page of Project Settings.

#include "RTS_2.h"
#include "RTS_2GameMode.h"
#include "CamPlayerController.h"

ARTS_2GameMode::ARTS_2GameMode()
{
	PlayerControllerClass = ACamPlayerController::StaticClass();
}


