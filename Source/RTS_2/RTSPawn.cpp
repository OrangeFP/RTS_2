// Fill out your copyright notice in the Description page of Project Settings.

#include "RTS_2.h"
#include "RTSPawn.h"


// Sets default values
ARTSPawn::ARTSPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = mesh;

	springArm->AttachTo(RootComponent);
	springArm->TargetArmLength = 350.f;
	springArm->SetWorldRotation(FRotator(-60.f, 0.f, 0.f));

	camera->AttachTo(springArm, USpringArmComponent::SocketName);

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	
}

// Called when the game starts or when spawned
void ARTSPawn::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ARTSPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	APlayerController* MyController = GetWorld()->GetFirstPlayerController();

	
	if (inView)
	{
		MyController->bShowMouseCursor = false;

		FViewport* v = CastChecked<ULocalPlayer>(MyController->Player)->ViewportClient->Viewport;
		v->SetMouse(mouseLockPositionX, mouseLockPositionY);

		FRotator newYaw = GetActorRotation();
		newYaw.Yaw += mouseInput.X;
		SetActorRotation(newYaw);

		FRotator newPitch = springArm->GetComponentRotation();
		newPitch.Pitch = FMath::Clamp(newPitch.Pitch + mouseInput.Y, -80.f, 0.f);
		springArm->SetWorldRotation(newPitch);
	} else {
		MyController->bShowMouseCursor = true;
		MyController->GetMousePosition(mouseLockPositionX, mouseLockPositionY);
		
	}

	if (!movementInput.IsZero())
	{
		movementInput = movementInput.SafeNormal() * 100.0f;
		FVector newLocation = GetActorLocation();
		newLocation += GetActorForwardVector() * movementInput.X * DeltaTime;
		newLocation += GetActorRightVector() * movementInput.Y * DeltaTime;
		SetActorLocation(newLocation);
	}
}

// Called to bind functionality to input
void ARTSPawn::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
	InputComponent->BindAction("InView", IE_Pressed, this, &ARTSPawn::InView);
	InputComponent->BindAction("InView", IE_Released, this, &ARTSPawn::OutView);
	InputComponent->BindAxis("MouseYaw", this, &ARTSPawn::MouseYaw);
	InputComponent->BindAxis("MousePitch", this, &ARTSPawn::MousePitch);
	InputComponent->BindAxis("MoveForward", this, &ARTSPawn::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ARTSPawn::MoveRight);
	InputComponent->BindAction("ZoomIn", IE_Pressed, this, &ARTSPawn::ZoomIn);
	InputComponent->BindAction("ZoomOut", IE_Pressed, this, &ARTSPawn::ZoomOut);

}

void ARTSPawn::MouseYaw(float axis) {
	mouseInput.X = axis;
}


void ARTSPawn::MousePitch(float axis) {
	mouseInput.Y = axis;
}

void ARTSPawn::ZoomIn()
{
	float zoom = springArm->TargetArmLength;

	if (zoom > zoomMin)
	{
		zoom -= 10;
		springArm->TargetArmLength = zoom;
	}
}

void ARTSPawn::ZoomOut()
{
	float zoom = springArm->TargetArmLength;

	if (zoom < zoomMax)
	{
		zoom += 10;
		springArm->TargetArmLength = zoom;
	}
}

void ARTSPawn::MoveForward(float axis)
{
	movementInput.X = FMath::Clamp<float>(axis, -1.0f, 1.0f);
}

void ARTSPawn::MoveRight(float axis)
{
	movementInput.Y = FMath::Clamp<float>(axis, -1.0f, 1.0f);
}

void ARTSPawn::InView()
{
	inView = true;
}

void ARTSPawn::OutView()
{
	inView = false;
}


