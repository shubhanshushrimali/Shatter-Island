#pragma once

UENUM(BlueprintType)
enum class ECharcterState : uint8
{
	ECS_Unequipped UMETA(DisplayName = "Unequipped"),
	ECS_EquippedOneHandedWeapon UMETA(DisplayName = "Equipped-OneHanded-Weapon"),
	ECS_EquippedTwoHandedWeapon UMETA(DisplayName = "Equipped-TwoHanded-Weapon")
};
