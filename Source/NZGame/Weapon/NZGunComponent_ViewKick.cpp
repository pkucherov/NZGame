// Fill out your copyright notice in the Description page of Project Settings.

#include "NZGame.h"
#include "NZGunComponent_ViewKick.h"
#include "NZGun.h"


const double RadToDeg = 57.295779513082321600;

// Sets default values for this component's properties
UNZGunComponent_ViewKick::UNZGunComponent_ViewKick()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = false;
    
    
    //
    AdjustDeltaYawDirection = 1;
    //
    SideReactDirectSectionNum = 9;
    SideReactDirectOneSectionNum = 3;
    SideReactDirectSection.Add(0);
    SideReactDirectSection.Add(1);
    SideReactDirectSection.Add(2);
    SideReactDirectSection.Add(3);
    SideReactDirectSection.Add(7);
    SideReactDirectSection.Add(13);
    SideReactDirectSection.Add(18);
    SideReactDirectSection.Add(24);
    SideReactDirectSection.Add(30);
    SideReactDirect.Add(50);
    SideReactDirect.Add(0);
    SideReactDirect.Add(50);
    SideReactDirect.Add(0);
    SideReactDirect.Add(100);
    SideReactDirect.Add(0);
    SideReactDirect.Add(0);
    SideReactDirect.Add(100);
    SideReactDirect.Add(0);
    SideReactDirect.Add(0);
    SideReactDirect.Add(0);
    SideReactDirect.Add(100);
    SideReactDirect.Add(0);
    SideReactDirect.Add(0);
    SideReactDirect.Add(100);
    SideReactDirect.Add(0);
    SideReactDirect.Add(0);
    SideReactDirect.Add(100);
    SideReactDirect.Add(70);
    SideReactDirect.Add(0);
    SideReactDirect.Add(30);
    SideReactDirect.Add(70);
    SideReactDirect.Add(0);
    SideReactDirect.Add(30);
    SideReactDirect.Add(50);
    SideReactDirect.Add(0);
    SideReactDirect.Add(50);
    
    ShotReactYawSectionNum = 3;
    ShotReactYawOneSectionNum = 2;
    ShotReactYawSection.Add(3);
    ShotReactYawSection.Add(13);
    ShotReactYawSection.Add(30);
    ShotReactYaw.Add(0.0015);
    ShotReactYaw.Add(0.0063);
    ShotReactYaw.Add(0.0015);
    ShotReactYaw.Add(0.0063);
    ShotReactYaw.Add(0.0008);
    ShotReactYaw.Add(0.0308);
    
    ShotReactPitchSectionNum = 4;
    ShotReactPitchOneSectionNum = 2;
    ShotReactPitchSection.Add(1);
    ShotReactPitchSection.Add(3);
    ShotReactPitchSection.Add(8);
    ShotReactPitchSection.Add(30);
    ShotReactPitch.Add(0.0026);
    ShotReactPitch.Add(0.0263);
    ShotReactPitch.Add(0.0016);
    ShotReactPitch.Add(0.0523);
    ShotReactPitch.Add(0.0022);
    ShotReactPitch.Add(0.0443);
    ShotReactPitch.Add(0.0);
    ShotReactPitch.Add(0.03);
    
    CameraYawAndPitchSectionNum = 4;
    CameraYawAndPitchOneSectionNum = 2;
    CameraYawAndPitchSection.Add(3);
    CameraYawAndPitchSection.Add(6);
    CameraYawAndPitchSection.Add(13);
    CameraYawAndPitchSection.Add(30);
    CameraYawAndPitch.Add(0.85);
    CameraYawAndPitch.Add(0.85);
    CameraYawAndPitch.Add(0.75);
    CameraYawAndPitch.Add(0.85);
    CameraYawAndPitch.Add(0.55);
    CameraYawAndPitch.Add(0.55);
    CameraYawAndPitch.Add(0.7);
    CameraYawAndPitch.Add(0.55);
    
    PerturbMax.Add(0.150);
    PerturbMax.Add(0.150);
    PerturbMax.Add(0.195);
    PerturbMax.Add(0.155);
    PerturbMax.Add(0.205);
    
    PerturbMin.Add(0.0043);
    PerturbMin.Add(0.004);
    PerturbMin.Add(0.0053);
    PerturbMin.Add(0.0048);
    PerturbMin.Add(0.0063);
    
    CrosshairRatioPerRealSize.Add(1.25);
    CrosshairRatioPerRealSize.Add(1.1);
    CrosshairRatioPerRealSize.Add(1.0);
    CrosshairRatioPerRealSize.Add(1.0);
    CrosshairRatioPerRealSize.Add(1.0);
    
    FullReactYawCoefficient.Add(-0.0265);
    FullReactYawCoefficient.Add(-0.0265);
    FullReactYawCoefficient.Add(-0.0305);
    FullReactYawCoefficient.Add(-0.0265);
    FullReactYawCoefficient.Add(-0.033);
    
    FullReactPitchCoefficient.Add(-0.125);
    FullReactPitchCoefficient.Add(-0.132);
    FullReactPitchCoefficient.Add(-0.15);
    FullReactPitchCoefficient.Add(-0.135);
    FullReactPitchCoefficient.Add(-0.17);
    
    ReactParamCoefficient.Add(0.968);
    ReactParamCoefficient.Add(0.97);
    ReactParamCoefficient.Add(0.92);
    ReactParamCoefficient.Add(0.96);
    ReactParamCoefficient.Add(0.85);
    
    DetailReactYawShot.Add(0.0623);
    DetailReactYawShot.Add(0.072);
    DetailReactYawShot.Add(0.13);
    DetailReactYawShot.Add(0.073);
    DetailReactYawShot.Add(0.20);
    
    DetailReactPitchShot.Add(0.18);
    DetailReactPitchShot.Add(0.17);
    DetailReactPitchShot.Add(0.29);
    DetailReactPitchShot.Add(0.19);
    DetailReactPitchShot.Add(0.35);
    
    ChangeMovingRealSize.Add(0.27);
    ChangeMovingRealSize.Add(0.00065);
    ChangeMovingRealSize.Add(0.0063);
    ChangeMovingRealSize.Add(0.0245);
    ChangeMovingRealSize.Add(0.14);
    
    FireCounterInterval.Add(50);
    FireCounterInterval.Add(500);
    FireCounterInterval.Add(7);
}

void UNZGunComponent_ViewKick::SetPunchAngle(FRotator Angle)
{
    ANZCharacter* Character = Cast<ANZCharacter>(GetOwner() ? GetOwner()->Instigator : NULL);
    if (Character != NULL)
    {
        Character->SetPunchAngle(Angle);
    }
}

FRotator UNZGunComponent_ViewKick::GetPunchAngle()
{
    ANZCharacter* Character = NULL;
    FRotator ZeroRotator = FRotator::ZeroRotator;
    FRotator PunchRotator = FRotator::ZeroRotator;
    
    Character = Cast<ANZCharacter>(GetOwner() ? GetOwner()->Instigator : NULL);
    if (Character != NULL)
    {
        PunchRotator.Pitch = -Character->PitchParam * RadToDeg;
        PunchRotator.Yaw = Character->YawParam * RadToDeg;
        return PunchRotator;
    }
    else
    {
        return ZeroRotator;
    }
}

void UNZGunComponent_ViewKick::Reset()
{
    FireCount = 0;
    FireCountDelayFrameCount = 0;
}

void UNZGunComponent_ViewKick::BeginFiringSequence(uint8 FireModeNum, bool bClientFired)
{
    
}

void UNZGunComponent_ViewKick::EndFiringSequence(uint8 FireModeNum)
{
    ANZGun* Gun = Cast<ANZGun>(GetOwner());
    if (Gun != NULL)
    {
        if (Gun->bIsContinousFire)
        {
            DelayFrameCount = 0;
            RecordEndFireReactParam = ChangeMovingRealSize[2] * FireCount + ReactParam;
            if (RecordEndFireReactParam > ChangeMovingRealSize[4])
            {
                RecordEndFireReactParam = ChangeMovingRealSize[4];
            }
        }
        
        FireCountDelayFrameCount = 0;
    }
}

void UNZGunComponent_ViewKick::FireShot()
{
    ANZGun* Gun = Cast<ANZGun>(GetOwner());
    if (Gun != NULL)
    {
        FireCount++;
        if (FireCount >= Gun->GetClass()->GetDefaultObject<ANZGun>()->ClipAmmoCount)
        {
            FireCount = Gun->GetClass()->GetDefaultObject<ANZGun>()->ClipAmmoCount;
        }
        
        if (FireCount <= FireCounterInterval[2])
        {
            if (Gun->bIsContinousFire)
            {
                ReactParam = ChangeMovingRealSize[1] + RecordReactParam + RecordReactParam;
            }
            else
            {
                ReactParam = ChangeMovingRealSize[2] * FireCount + RecordReactParam;
            }
        }
        else
        {
            ReactParam = ChangeMovingRealSize[3] * FireCount + RecordReactParam + RecordReactParam;
        }
        
        if (ReactParam > ChangeMovingRealSize[4])
        {
            ReactParam = ChangeMovingRealSize[4];
        }
        
        //ReactParam *= ShotSpreadScale;
    }
}

void UNZGunComponent_ViewKick::KickBackTheView()
{
    ANZCharacter* Character = NULL;
    float CurrentDetailReactYawShot = 0.f;
    float CurrentDetailReactPitchShot = 0.f;
    TArray<float> CurrentSideReactDirect;
    float FireCountRefer = 0.f;
    
    Character = Cast<ANZCharacter>(GetOwner() ? GetOwner()->Instigator : NULL);
    if (Character == NULL)
    {
        return;
    }
    
    if (Character->GetCharacterMovement()->MovementMode == MOVE_Falling)
    {
        CurrentDetailReactPitchShot = DetailReactPitchShot[4];
        CurrentDetailReactYawShot = DetailReactYawShot[4];
    }
    //else if (Character->bSnake && Character->Acceleration.Size() > 0)
    //{
    //    CurrentDetailReactPitchShot = DetailReactPitchShot[3];
    //    CurrentDetailReactYawShot = DetailReactYawShot[3];
    //}
    else if (Character->bIsCrouched)
    {
        if (Character->GetCharacterMovement()->Velocity.Size() > 0)
        {
            CurrentDetailReactPitchShot = DetailReactPitchShot[3];
            CurrentDetailReactYawShot = DetailReactYawShot[3];
        }
        else
        {
            CurrentDetailReactPitchShot = DetailReactPitchShot[1];
            CurrentDetailReactYawShot = DetailReactYawShot[1];
        }
    }
    else if (Character->GetCharacterMovement()->Velocity.Size() > 200)
    {
        CurrentDetailReactPitchShot = DetailReactPitchShot[2];
        CurrentDetailReactYawShot = DetailReactYawShot[2];
    }
    else
    {
        CurrentDetailReactPitchShot = DetailReactPitchShot[0];
        CurrentDetailReactYawShot = DetailReactYawShot[0];
    }
    
    DeltaPitchParam = CurrentDetailReactPitchShot * (RecordReactParam + 0.1500000059604645) * -1.0f;
    DeltaYawParam = CurrentDetailReactYawShot * (RecordReactParam + 0.1500000059604645) * -1.0f * AdjustDeltaYawDirection;
    
    if (FireCount - 1 > SideReactDirectSection[SideReactDirectSectionNum - 1])
    {
        for (int j = 0; j < SideReactDirectOneSectionNum; j++)
        {
            CurrentSideReactDirect.Add(SideReactDirect[(SideReactDirectSectionNum - 1) * SideReactDirectOneSectionNum + j]);
        }
    }
    else
    {
        for (int i = 1; i < SideReactDirectSectionNum; i++)
        {
            if (FireCount - 1 <= SideReactDirectSection[i])
            {
                for (int j = 0; j < SideReactDirectOneSectionNum; j++)
                {
                    CurrentSideReactDirect.Add(SideReactDirect[i * SideReactDirectOneSectionNum + j]);
                }
                break;
            }
        }
    }

    if (SideReactDirect[SideReactDirectOneSectionNum + 1] == 0)
    {
        DeltaYawParam = DeltaYawParam * (2 * int32(FMath::FRand() * 2.f) - 1);
    }
    else
    {
        if (FireCount == 1)
        {
            bChangeDirectionFlag1 = (int32(FMath::FRand() * 100.f) < SideReactDirect[0]);
        }
        
        if (FireCount == 1)
        {
            ChangeDirectionFlag3 = int32(FMath::FRand() * 100.f);
        }
        else
        {
            for (int i = 1; i < SideReactDirectSectionNum; i++)
            {
                if (FireCount == SideReactDirectSection[i] + 2)
                {
                    ChangeDirectionFlag3 = int32(FMath::FRand() * 100.f);
                    break;
                }
            }
        }
        
        if (bChangeDirectionFlag1)
        {
            FireCountRefer = CurrentSideReactDirect[0];
        }
        else
        {
            FireCountRefer = CurrentSideReactDirect[2];
        }
        
        if (FireCountRefer < ChangeDirectionFlag3)
        {
            if (CurrentSideReactDirect[1] + FireCountRefer < ChangeDirectionFlag3)
            {
                ShotSpreadFlag = 2;
                DeltaYawParam = DeltaYawParam * -1.0f;
                AdjustDeltaYawDirection = 1;
                bReachYawMax = false;
            }
            else
            {
                DeltaYawParam = 0.0f;
                ShotSpreadFlag = 1;
            }
        }
        else
        {
            ShotSpreadFlag = 0;
        }
    }
    
    if (ShotsFired > GunTurnRedStartShots)
    {
        if (bIsNoTarget == false)
        {
            StartNoTargetTime = float(ShotsFired);
            bIsNoTarget = true;
        }
    }
    else
    {
        bIsNoTarget = false;
        StartNoTargetTime = 0;
    }
    
    DeltaPitchParam = DeltaPitchParam + Character->PitchParam;
    DeltaYawParam = DeltaYawParam + Character->YawParam;
    
    bDelayOneFrameForCamera = true;
}

void UNZGunComponent_ViewKick::ModifyAdjustedAim(FRotator& BaseAim)
{
    ANZCharacter* Character = Cast<ANZCharacter>(GetOwner() ? GetOwner()->Instigator : NULL);
    if (Character != NULL)
    {
        BaseAim.Pitch += (-Character->PitchParam * RadToDeg);
        BaseAim.Yaw += (Character->YawParam * RadToDeg);
    }
}

FVector UNZGunComponent_ViewKick::ModifyForwardDirection(FRotator AimAngle)
{
    float CurrentPerturbMin = 0.f;
    float CurrentPerturbMax = 0.f;
    
    ANZCharacter* Character = Cast<ANZCharacter>(GetOwner() ? GetOwner()->Instigator : NULL);
    if (Character == NULL || Character->GetCharacterMovement() == NULL)
    {
        return AimAngle.Vector();
    }
    
    if (Character->GetCharacterMovement()->MovementMode == MOVE_Falling)
    {
        CurrentPerturbMin = PerturbMin[4];
        CurrentPerturbMax = PerturbMax[4];
    }
    else if (Character->bIsCrouched)
    {
        if (Character->GetCharacterMovement()->Velocity.Size() > 0)
        {
            CurrentPerturbMin = PerturbMin[3];
            CurrentPerturbMax = PerturbMax[3];
        }
        else
        {
            CurrentPerturbMin = PerturbMin[1];
            CurrentPerturbMax = PerturbMax[1];
        }
    }
    else if (Character->GetCharacterMovement()->Velocity.Size() > 200)
    {
        CurrentPerturbMin = PerturbMin[2];
        CurrentPerturbMax = PerturbMax[2];
    }
    else
    {
        CurrentPerturbMin = PerturbMin[0];
        CurrentPerturbMax = PerturbMax[0];
    }
    
    float RSead2 = CurrentPerturbMin + (CurrentPerturbMax - CurrentPerturbMin) * RecordReactParam;
    float RSead1 = -(CurrentPerturbMin + (CurrentPerturbMax - CurrentPerturbMin) * RecordReactParam);
    float RandX = FMath::RandRange(RSead1, RSead2);
    float RandY = FMath::RandRange(RSead1, RSead2);
    
    if (ShotSpreadFlag == 0)
    {
        if (RandX <= 0.0)
        {
            RandY = 0.5 * RandX;
        }
        else
        {
            RandY = 0.5 * RandY;
            RandX = -RandX;
        }
    }
    else if (ShotSpreadFlag == 1)
    {
        RandY = 0.0;
        RandX = RandX * 0.300000011920929;
    }
    else if (ShotSpreadFlag == 2)
    {
        if (RandX < 0.0)
        {
            RandY = 0.5 * RandY;
            RandX = -RandX;
        }
        else
        {
            RandY = 0.5 * RandY;
        }
    }
    
    AimAngle.Yaw += RandX * RadToDeg;
    AimAngle.Pitch += RandY * RadToDeg;

    FRotationMatrix Mat(AimAngle);
    FVector X, Y, Z;
    Mat.GetScaledAxes(X, Y, Z);
    
    return X;
}

void UNZGunComponent_ViewKick::CalcCamera(float DeltaTime, FVector& OutCamLoc, FRotator& OutCamRot)
{
    FRotator InitPunchAngle = FRotator::ZeroRotator;
    FRotator DeltaPunchAngle2 = FRotator::ZeroRotator;
    ANZCharacter* Character = NULL;
    float CurrentYawAndPitchPitchFactor = 0.f;
    float CurrentYawAndPitchYawFactor = 0.f;
    float CurrentReactParamCoefficient = 0.f;
    float CurrentFullReactYawCoefficient = 0.f;
    float CurrentFullReactPitchCoefficient = 0.f;
    TArray<float> CurrentShotReactYaw;
    TArray<float> CurrentShotReactPitch;
    float YawSign = 0.f;
    float RemainDeltaTime = 0.f;
    float TimeTick = 0.f;
    DeltaTime = 0.1;
    
    Character = Cast<ANZCharacter>(GetOwner() ? GetOwner()->Instigator : NULL);
    if (Character == NULL || Character->GetCharacterMovement() == NULL)
    {
        return;
    }
    
    InitPunchAngle = GetPunchAngle();
    DeltaPunchAngle2 = InitPunchAngle;
    
    if (DeltaTime != 0.f)
    {
        if (true)
        {
            if (DelayFrameCount == 1)
            {
                ReactParam = RecordEndFireReactParam;
                FireCount = 0;
            }
            if (DelayFrameCount != 1 && FireCountDelayFrameCount == 1)
            {
                FireCount = 0;
            }
            DelayFrameCount++;
            FireCountDelayFrameCount++;
            
            if (Character->GetCharacterMovement()->MovementMode == MOVE_Falling)
            {
                CurrentReactParamCoefficient = ReactParamCoefficient[4];
                CurrentFullReactYawCoefficient = FullReactYawCoefficient[4];
                CurrentFullReactPitchCoefficient = FullReactPitchCoefficient[4];
            }
            else if (Character->bIsCrouched)
            {
                if (Character->GetCharacterMovement()->Velocity.Size() > 0)
                {
                    CurrentReactParamCoefficient = ReactParamCoefficient[3];
                    CurrentFullReactYawCoefficient = FullReactYawCoefficient[3];
                    CurrentFullReactPitchCoefficient = FullReactPitchCoefficient[3];
                }
                else
                {
                    CurrentReactParamCoefficient = ReactParamCoefficient[1];
                    CurrentFullReactYawCoefficient = FullReactYawCoefficient[1];
                    CurrentFullReactPitchCoefficient = FullReactPitchCoefficient[1];
                }
            }
            else if (Character->GetCharacterMovement()->Velocity.Size() > 200)
            {
                CurrentReactParamCoefficient = ReactParamCoefficient[2];
                CurrentFullReactYawCoefficient = FullReactYawCoefficient[2];
                CurrentFullReactPitchCoefficient = FullReactPitchCoefficient[2];
            }
            else
            {
                CurrentReactParamCoefficient = ReactParamCoefficient[0];
                CurrentFullReactYawCoefficient = FullReactYawCoefficient[0];
                CurrentFullReactPitchCoefficient = FullReactPitchCoefficient[0];
            }
        }
        
        if (FireCount > ShotReactYawSection[ShotReactYawSectionNum - 1])
        {
            for (int j = 0; j < ShotReactYawOneSectionNum; j++)
            {
                CurrentShotReactYaw.Add(ShotReactYaw[(ShotReactYawSectionNum - 1) * ShotReactYawOneSectionNum + j]);
            }
        }
        else
        {
            for (int i = 0; i < ShotReactYawSectionNum; i++)
            {
                if (FireCount <= ShotReactYawSection[i])
                {
                    for (int j = 0; j < ShotReactYawOneSectionNum; j++)
                    {
                        CurrentShotReactYaw.Add(ShotReactYaw[i * ShotReactYawOneSectionNum + j]);
                    }
                    break;
                }
            }
        }
        
        if (FireCount > ShotReactPitchSection[ShotReactPitchSectionNum - 1])
        {
            for (int j = 0; j < ShotReactPitchOneSectionNum; j++)
            {
                CurrentShotReactPitch.Add(ShotReactPitch[(ShotReactPitchSectionNum - 1) * ShotReactPitchOneSectionNum + j]);
            }
        }
        else
        {
            for (int i = 0; i < ShotReactPitchSectionNum; i++)
            {
                if (FireCount <= ShotReactPitchSection[i])
                {
                    for (int j = 0; j < ShotReactPitchOneSectionNum; j++)
                    {
                        CurrentShotReactPitch.Add(ShotReactPitch[i * ShotReactPitchOneSectionNum + j]);
                    }
                    break;
                }
            }
        }
        
        if (CurrentReactParamCoefficient == 0.0f)
        {
            check(false);
        }
        
        RecordReactParam = ReactParam;
        
        RemainDeltaTime = DeltaTime;
        while (RemainDeltaTime > 0)
        {
            TimeTick = (RemainDeltaTime > 0.005) ? 0.005 : RemainDeltaTime;
            RemainDeltaTime -= TimeTick;
            ReactParam = ReactParam - ChangeMovingRealSize[0] * TimeTick;
            
            if (Character->YawParam != 0 || DeltaYawParam != 0)
            {
                if (DeltaYawParam > 0)
                {
                    if (Character->YawParam > 0)
                    {
                        if (FMath::Abs(Character->YawParam) < FMath::Abs(CurrentFullReactYawCoefficient))
                        {
                            if (Character->YawParam > DeltaYawParam)
                            {
                                Character->YawParam = Character->YawParam - CurrentShotReactYaw[1] * TimeTick * 1000 * 0.001000000047497451 * 100.0;
                                if (Character->YawParam <= DeltaYawParam)
                                {
                                    Character->YawParam = DeltaYawParam;
                                    DeltaYawParam = 0.0f;
                                }
                            }
                            else if (Character->YawParam < DeltaYawParam)
                            {
                                Character->YawParam = Character->YawParam + CurrentShotReactYaw[1] * TimeTick * 1000 * 0.001000000047497451 * 100.0;
                                if (Character->YawParam >= DeltaYawParam)
                                {
                                    Character->YawParam = DeltaYawParam;
                                    DeltaYawParam = 0.0f;
                                }
                            }
                            else
                            {
                                Character->YawParam = DeltaYawParam;
                                DeltaYawParam = 0.0f;
                            }
                        }
                        else
                        {
                            if (FMath::Abs(Character->YawParam) < FMath::Abs(DeltaYawParam) && FMath::Abs(Character->YawParam) >= FMath::Abs(CurrentFullReactYawCoefficient))
                            {
                                DeltaYawParam = 0.0f;
                            }
                            
                            Character->YawParam = Character->YawParam - CurrentShotReactYaw[0] * TimeTick * 1000 * 0.001000000047497451 * 100.0;
                            if (FireCount == 0)
                            {
                                if (Character->YawParam < 0.0f)
                                {
                                    Character->YawParam = 0.0f;
                                }
                            }
                        }
                    }
                    else
                    {
                        Character->YawParam = Character->YawParam + CurrentShotReactYaw[1] * TimeTick * 1000 * 0.001000000047497451 * 100.0;
                        if (Character->YawParam > DeltaYawParam)
                        {
                            Character->YawParam = DeltaYawParam;
                        }
                    }
                }
                else if (DeltaYawParam < 0)
                {
                    if (Character->YawParam < 0)
                    {
                        if (FMath::Abs(Character->YawParam) < FMath::Abs(CurrentFullReactYawCoefficient))
                        {
                            if (Character->YawParam > DeltaYawParam)
                            {
                                Character->YawParam = Character->YawParam - CurrentShotReactYaw[1] * TimeTick * 1000 * 0.001000000047497451 * 100.0;
                                if (Character->YawParam <= DeltaYawParam)
                                {
                                    Character->YawParam = DeltaYawParam;
                                    DeltaYawParam = 0.0f;
                                }
                            }
                            else if (Character->YawParam < DeltaYawParam)
                            {
                                Character->YawParam = Character->YawParam + CurrentShotReactYaw[1] * TimeTick * 1000 * 0.001000000047497451 * 100.0;
                                if (Character->YawParam >= DeltaYawParam)
                                {
                                    Character->YawParam = DeltaYawParam;
                                    DeltaYawParam = 0.0f;
                                }
                            }
                            else
                            {
                                Character->YawParam = DeltaYawParam;
                                DeltaYawParam = 0.0f;
                            }
                        }
                        else
                        {
                            if (FMath::Abs(Character->YawParam) < FMath::Abs(DeltaYawParam) && FMath::Abs(Character->YawParam) >= FMath::Abs(CurrentFullReactYawCoefficient))
                            {
                                DeltaYawParam = 0.0f;
                            }
                            
                            Character->YawParam = Character->YawParam + CurrentShotReactYaw[0] * TimeTick * 1000 * 0.001000000047497451 * 100.0;
                            if (FireCount == 0)
                            {
                                if (Character->YawParam > 0.0f)
                                {
                                    Character->YawParam = 0.0f;
                                }
                            }
                        }
                    }
                    else
                    {
                        Character->YawParam = Character->YawParam - CurrentShotReactYaw[1] * TimeTick * 1000 * 0.001000000047497451 * 100.0;
                        if (Character->YawParam < DeltaYawParam)
                        {
                            Character->YawParam = DeltaYawParam;
                        }
                    }
                }
                else
                {
                    if (Character->YawParam != 0)
                    {
                        YawSign = FMath::Abs(Character->YawParam) / Character->YawParam;
                        Character->YawParam = YawSign * (FMath::Abs(Character->YawParam) - CurrentShotReactYaw[0] * TimeTick * 1000 * 0.001000000047497451 * 100.0);
                        if (Character->YawParam * YawSign < 0)
                        {
                            Character->YawParam = 0.0f;
                        }
                    }
                }
            }
            
            if (FireCount != 0 || Character->PitchParam != 0)
            {
                if (FMath::Abs(Character->PitchParam) < FMath::Abs(DeltaPitchParam) && FMath::Abs(Character->PitchParam) < FMath::Abs(CurrentFullReactPitchCoefficient))
                {
                    Character->PitchParam = Character->PitchParam - CurrentShotReactPitch[1] * TimeTick * 1000 * 0.001000000047497451 * 100.0;
                    if (DeltaPitchParam >= Character->PitchParam)
                    {
                        Character->PitchParam = DeltaPitchParam;
                        DeltaPitchParam = 0.0f;
                    }
                }
                else
                {
                    if (FMath::Abs(Character->PitchParam) <= FMath::Abs(DeltaPitchParam) || FMath::Abs(Character->PitchParam) > FMath::Abs(CurrentFullReactPitchCoefficient))
                    {
                        DeltaPitchParam = 0.0f;
                    }
                    Character->PitchParam = Character->PitchParam + CurrentShotReactPitch[0] * TimeTick * 1000 * 0.001000000047497451 * 100.0;
                }
                
                if (Character->PitchParam > 0)
                {
                    Character->PitchParam = 0;
                }
            }
            
            if (ReactParam < 1 - CurrentReactParamCoefficient)
            {
                ReactParam = 1 - CurrentReactParamCoefficient;
            }
        }
    }
    
    if (FireCount > CameraYawAndPitchSection[CameraYawAndPitchSectionNum - 1])
    {
        CurrentYawAndPitchPitchFactor = CameraYawAndPitch[(CameraYawAndPitchSectionNum - 1) * CameraYawAndPitchOneSectionNum + 1];
        CurrentYawAndPitchYawFactor = CameraYawAndPitch[(CameraYawAndPitchSectionNum - 1) * CameraYawAndPitchOneSectionNum];
    }
    else
    {
        for (int i = 0; i < CameraYawAndPitchSectionNum; i++)
        {
            if (FireCount <= CameraYawAndPitchSection[i])
            {
                //for (int j = 0; j < CameraYawAndPitchOneSectionNum; j++)
                //{
                    CurrentYawAndPitchPitchFactor = CameraYawAndPitch[i * CameraYawAndPitchOneSectionNum + 1];
                    CurrentYawAndPitchYawFactor = CameraYawAndPitch[i * CameraYawAndPitchOneSectionNum];
                //}
                break;
            }
        }
    }
    
    Character->LastPitchAngle = CurrentYawAndPitchPitchFactor * InitPunchAngle.Pitch;
    Character->LastYawAngle = CurrentYawAndPitchYawFactor * InitPunchAngle.Yaw;
    
    DeltaPunchAngle2.Pitch = CurrentYawAndPitchPitchFactor * InitPunchAngle.Pitch;
    DeltaPunchAngle2.Yaw = CurrentYawAndPitchYawFactor * InitPunchAngle.Yaw;
    
    SetPunchAngle(DeltaPunchAngle2);
    
    OutCamRot.Pitch += CurrentYawAndPitchPitchFactor * InitPunchAngle.Pitch;
    OutCamRot.Yaw += CurrentYawAndPitchYawFactor * InitPunchAngle.Yaw;
}

bool UNZGunComponent_ViewKick::DrawCrosshair_Normal(UNZCrosshair* Crosshair, UCanvas* Canvas, float DeltaTime, float Scale, FLinearColor Color)
{
    ANZCharacter* Character = NULL;
    float CurrentPerturbMin = 0.f;
    float CurrentPerturbMax = 0.f;
    float CurrentCrosshairRatioPerRealSize = 0.f;
    float CurrentReactParamCoefficient = 0.f;
    FLinearColor TempShadowColor;
    
    if (Crosshair == NULL || Canvas == NULL)
    {
        return false;
    }
    
    Character = Cast<ANZCharacter>(GetOwner() ? GetOwner()->Instigator : NULL);
    if (Character == NULL || Character->GetCharacterMovement() == NULL)
    {
        return false;
    }
    
    if (Character->GetCharacterMovement()->MovementMode == MOVE_Falling)
    {
        CurrentPerturbMin = PerturbMin[4];
        CurrentPerturbMax = PerturbMax[4];
        CurrentCrosshairRatioPerRealSize = CrosshairRatioPerRealSize[4];
        CurrentReactParamCoefficient = ReactParamCoefficient[4];
    }
    else if (Character->bIsCrouched)
    {
        if (Character->GetCharacterMovement()->Velocity.Size() > 0)
        {
            CurrentPerturbMin = PerturbMin[3];
            CurrentPerturbMax = PerturbMax[3];
            CurrentCrosshairRatioPerRealSize = CrosshairRatioPerRealSize[3];
            CurrentReactParamCoefficient = ReactParamCoefficient[3];
        }
        else
        {
            CurrentPerturbMin = PerturbMin[1];
            CurrentPerturbMax = PerturbMax[1];
            CurrentCrosshairRatioPerRealSize = CrosshairRatioPerRealSize[1];
            CurrentReactParamCoefficient = ReactParamCoefficient[1];
        }
    }
    else if (Character->GetCharacterMovement()->Velocity.Size() > 200)
    {
        CurrentPerturbMin = PerturbMin[2];
        CurrentPerturbMax = PerturbMax[2];
        CurrentCrosshairRatioPerRealSize = CrosshairRatioPerRealSize[2];
        CurrentReactParamCoefficient = ReactParamCoefficient[2];
    }
    else
    {
        CurrentPerturbMin = PerturbMin[0];
        CurrentPerturbMax = PerturbMax[0];
        CurrentCrosshairRatioPerRealSize = CrosshairRatioPerRealSize[0];
        CurrentReactParamCoefficient = ReactParamCoefficient[0];
    }
    
    float ScaleCrosshair = Canvas->ClipX / 1024;
    float DefaultReactParam = 1.0 - CurrentReactParamCoefficient;
    
    float TestShotCircle = (DefaultReactParam * (CurrentPerturbMax - CurrentPerturbMin) + CurrentPerturbMin) * (Canvas->ClipX * 1.330000042915344);
    float TestShotCircleMin = Canvas->ClipX * 1.330000042915344 * (CurrentPerturbMin + (CurrentPerturbMax - CurrentPerturbMin) * RecordReactParam);
    
    float Param1 = TestShotCircle * 0.5 * CurrentCrosshairRatioPerRealSize;
    float Param2 = TestShotCircleMin * 0.5 * CurrentCrosshairRatioPerRealSize;
    
    float Crosshair_LenSize = 5;
    float Crosshair_LenRatio1 = 0.800000011920929 * Param2;
    float Crosshair_LenRatio2 = Crosshair_LenSize + Crosshair_LenRatio1 + (Param2 - Param1) * 0.300000011920929;
    
    if (Crosshair_LenRatio1 < 1)
    {
        Crosshair_LenRatio1 = 1;
    }
    
    int32 CrosshairSize = int32(Crosshair_LenRatio1 - 1);
    int32 CrosshairLineLength = int32((Crosshair_LenRatio2 - Crosshair_LenRatio1) * ScaleCrosshair);
    float X = Canvas->ClipX * 0.5;
    float Y = Canvas->ClipY * 0.5;
    
    Canvas->SetLinearDrawColor(Color);
    
    // UpSide
    float ScreenX = X;
    float ScreenY = Y - CrosshairSize - CrosshairLineLength;
    Canvas->DrawTile(Crosshair->CrosshairIcon.Texture, ScreenX, ScreenY, 1, CrosshairLineLength, 395, 489, 16, 16, BLEND_Opaque);
    
    // LeftSide
    ScreenX = X - CrosshairSize - CrosshairLineLength;
    ScreenY = Y;
    Canvas->DrawTile(Crosshair->CrosshairIcon.Texture, ScreenX, ScreenY, CrosshairLineLength, 1, 395, 489, 16, 16, BLEND_Opaque);
    
    // RightSide
    ScreenX = X + CrosshairSize + 1;
    ScreenY = Y;
    Canvas->DrawTile(Crosshair->CrosshairIcon.Texture, ScreenX, ScreenY, CrosshairLineLength, 1, 395, 489, 16, 16, BLEND_Opaque);
    
    // DownSide
    ScreenX = X;
    ScreenY = Y + CrosshairSize + 1;
    Canvas->DrawTile(Crosshair->CrosshairIcon.Texture, ScreenX, ScreenY, 1, CrosshairLineLength, 395, 489, 16, 16, BLEND_Opaque);
    
    return true;
}


