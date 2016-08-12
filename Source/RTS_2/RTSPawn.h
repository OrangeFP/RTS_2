// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "RTSPawn.generated.h"

UCLASS()
class RTS_2_API ARTSPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ARTSPawn();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;


	void MouseYaw(float axis);
	void MousePitch(float axis);
	void MoveForward(float axis);
	void MoveRight(float axis);
	void ZoomIn(void);
	void ZoomOut(void);
	void InView();
	void OutView();
	void SetMousePosition();


	float zoomMin = 10;
	float zoomMax = 1000;
	float mouseLockPositionX;
	float mouseLockPositionY;
	
	bool inView;

	

	//Vector
	FVector2D mouseInput;
	FVector2D movementInput;
	FVector2D mousePosition;
	

	UPROPERTY(EditAnywhere)
		USpringArmComponent* springArm;
	UCameraComponent* camera;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* mesh;

};
