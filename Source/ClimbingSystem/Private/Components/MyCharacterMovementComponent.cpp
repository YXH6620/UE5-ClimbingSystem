// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/MyCharacterMovementComponent.h"

bool UMyCharacterMovementComponent::IsClimbing() const
{
	if(MovementMode == MOVE_Custom && CustomMovementMode == ECustomMovementMode::ECMM_Climbing)
	{
		return true;
	}
	return false;
}
