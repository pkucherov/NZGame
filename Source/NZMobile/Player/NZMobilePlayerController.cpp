// Fill out your copyright notice in the Description page of Project Settings.

#include "NZMobile.h"
#include "NZMobilePlayerController.h"
#include "NZMobilePlayerInput.h"


ANZMobilePlayerController::ANZMobilePlayerController()
{
#if !PLATFORM_ANDROID && !PLATFORM_IOS
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
#endif
}

void ANZMobilePlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (MobilePlayerInput)
	{
		MobilePlayerInput->UpdatePlayerInput(DeltaSeconds);
	}
}

void ANZMobilePlayerController::InitInputSystem()
{
	if (PlayerInput == NULL)
	{
		PlayerInput = NewObject<UNZMobilePlayerInput>(this, UNZMobilePlayerInput::StaticClass());
	}

	Super::InitInputSystem();

	// todo:
}

void ANZMobilePlayerController::SetupInputComponent()
{
	APlayerController::SetupInputComponent();

	if (FPlatformMisc::GetUseVirtualJoysticks() || GetDefault<UInputSettings>()->bUseMouseForTouch)
	{
		MobilePlayerInput = Cast<UNZMobilePlayerInput>(PlayerInput);
		if (MobilePlayerInput)
		{
			MobilePlayerInput->Initialize();
		}
		InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &ANZMobilePlayerController::BeginTouch);
		InputComponent->BindTouch(EInputEvent::IE_Released, this, &ANZMobilePlayerController::EndTouch);
		InputComponent->BindTouch(EInputEvent::IE_Repeat, this, &ANZMobilePlayerController::TouchUpdate);
	}
}

void ANZMobilePlayerController::BeginTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if (MobilePlayerInput)
	{
		MobilePlayerInput->BeginTouch(FingerIndex, Location);
	}
}

void ANZMobilePlayerController::EndTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if (MobilePlayerInput)
	{
		MobilePlayerInput->EndTouch(FingerIndex, Location);
	}
}

void ANZMobilePlayerController::TouchUpdate(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if (MobilePlayerInput)
	{
		MobilePlayerInput->TouchUpdate(FingerIndex, Location);
	}
}
