/************************************************************************/
/* ����������                                                                     */
/************************************************************************/
#include "NZVR.h"
#include "NZVestComponent.h"
#include "NZCharacter.h"

UNZVestComponent::UNZVestComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	VestSockets.AddZeroed(8);
	VestSockets[0].pos = EVP_RUp;
	VestSockets[1].pos = EVP_LUp;
	VestSockets[2].pos = EVP_RMid;
	VestSockets[3].pos = EVP_LMid;
	VestSockets[4].pos = EVP_RDown;
	VestSockets[5].pos = EVP_LDown;
	VestSockets[6].pos = EVP_RBack;
	VestSockets[7].pos = EVP_LBack;
}


int32 UNZVestComponent::GetConfigSerialPort()
{
	return ConfigSerialPort;
}

void UNZVestComponent::OnTakePointDamage(float Damage, FVector& HitLocation, AActor* DamageCauser)
{
	const ANZCharacter* OwnerPawn = Cast<ANZCharacter>(GetOwner());

	if (OwnerPawn == NULL)
	{
		//ȫ����
		Virbration(EVP_Default, EVM_AllPoint);
		return;
	}

	USkeletalMeshComponent* SkelMeshComp = OwnerPawn->GetMesh();
	if (SkelMeshComp == NULL)
	{
		//ȫ����
		Virbration(int(EVP_Default), int(EVM_AllPoint));
		return;
	}

	float MinDistSquared = -1.0f;
	float NewDistSquared;
	int32 MinIdx = INDEX_NONE;
	FVector SocketLoc;
	FQuat SocketRot;

	//�ҵ�����ĵ㲢��
	for (int32 i = 0; i < VestSockets.Num(); i++)
	{
		SkelMeshComp->GetSocketWorldLocationAndRotation(VestSockets[i].SocketName, SocketLoc, SocketRot);
		NewDistSquared = (SocketLoc - HitLocation).SizeSquared();

		if ((MinIdx == INDEX_NONE) || (NewDistSquared < MinDistSquared))
		{
			MinIdx = i;
			MinDistSquared = NewDistSquared;
		}
	}

	if ((MinIdx >= 0) && (MinIdx < VestSockets.Num()))
	{
		Virbration(VestSockets[MinIdx].pos, int(EVM_SinglePoint));
	}
}