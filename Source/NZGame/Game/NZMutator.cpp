// Fill out your copyright notice in the Description page of Project Settings.

#include "NZGame.h"
#include "NZMutator.h"




void ANZMutator::ModifyPlayer_Implementation(APawn* Other, bool bIsNewSpawn)
{
    
}

void ANZMutator::ModifyInventory_Implementation(ANZInventory* Inv, ANZCharacter* NewOwner)
{

}

void ANZMutator::AddDefaultInventory(TSubclassOf<ANZInventory> InventoryClass)
{
    
}

bool ANZMutator::ModifyDamage_Implementation(UPARAM(ref) int32& Damage, UPARAM(ref) FVector& Momentum, APawn* Injured, AController* InstigatedBy, const FHitResult& HitInfo, AActor* DamageCauser, TSubclassOf<UDamageType> DamageType)
{
	if (NextMutator != NULL)
	{
		NextMutator->ModifyDamage(Damage, Momentum, Injured, InstigatedBy, HitInfo, DamageCauser, DamageType);
	}
	return true;
}

bool ANZMutator::PreventDeath_Implementation(APawn* KilledPawn, AController* Killer, TSubclassOf<UDamageType> DamageType, const FHitResult& HitInfo)
{
    return (NextMutator != NULL && NextMutator->PreventDeath(KilledPawn, Killer, DamageType, HitInfo));
}
