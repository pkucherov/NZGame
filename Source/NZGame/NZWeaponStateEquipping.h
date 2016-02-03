// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NZWeaponState.h"
#include "NZWeaponStateEquipping.generated.h"

/**
 * 
 */
UCLASS(CustomConstructor)
class NZGAME_API UNZWeaponStateEquipping : public UNZWeaponState
{
	GENERATED_BODY()
	
public:
	UNZWeaponStateEquipping();

    /** Set to amount of equip time that elapsed when exiting early, i.e. to go back down */
    float PartialEquipTime;
    
	/** Total time to bring up the weapon */
    float EquipTime;
    
	/** Pending fire mode on server when equip completes */
    int32 PendingFireSequence;
    
    virtual void BeginState(const UNZWeaponState* PrevState) override;
    
    virtual bool BeginFiringSequence(uint8 FireModeNum, bool bClientFired) override;
    
	/** Called to start the equip timer/anim; This isn't done automatically in BeginState() because we need to pass in any overflow time from the previous weapon's PutDown() */
    virtual void StartEquip(float OverflowTime);

    virtual void EndState() override
    {
        GetOuterANZWeapon()->GetWorldTimerManager().ClearAllTimersForObject(this);
    }
    
    virtual void Tick(float DeltaTime)
    {
        if (!GetOuterANZWeapon()->GetWorldTimerManager().IsTimerActive(BringUpFinishedHandle))
        {
            //UE_LOG(NZ, Warning, TEXT("%s in state Equipping with no equip timer!"), *GetOuterAUTWeapon()->GetName());
            BringUpFinished();
        }
    }
    
    FTimerHandle BringUpFinishedHandle;
    
    virtual void BringUpFinished();
    
    virtual void PutDown() override
    {
		PartialEquipTime = FMath::Max(0.001f, GetOuterANZWeapon()->GetWorldTimerManager().GetTimerElapsed(BringUpFinishedHandle));
		GetOuterANZWeapon()->GotoState(GetOuterANZWeapon()->UnequippingState);
    }
};
